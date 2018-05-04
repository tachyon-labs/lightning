from concurrent import futures
from test_lightningd import NodeFactory

import logging
import os
import pytest
import re
import tempfile
import utils


TEST_DIR = tempfile.mkdtemp(prefix='ltests-')
VALGRIND = os.getenv("NO_VALGRIND", "0") == "0"
DEVELOPER = os.getenv("DEVELOPER", "0") == "1"
TEST_DEBUG = os.getenv("TEST_DEBUG", "0") == "1"


@pytest.fixture
def directory(test_name):
    """Return a per-test specific directory
    """
    global TEST_DIR
    yield os.path.join(TEST_DIR, test_name)


@pytest.fixture
def test_name(request):
    yield request.function.__name__


@pytest.fixture
def bitcoind(directory):
    bitcoind = utils.BitcoinD(bitcoin_dir=directory, rpcport=None)
    try:
        bitcoind.start()
    except Exception:
        bitcoind.stop()
        raise

    info = bitcoind.rpc.getnetworkinfo()

    if info['version'] < 160000:
        bitcoind.rpc.stop()
        raise ValueError("bitcoind is too old. At least version 16000 (v0.16.0)"
                         " is needed, current version is {}".format(info['version']))

    info = bitcoind.rpc.getblockchaininfo()
    # Make sure we have some spendable funds
    if info['blocks'] < 101:
        bitcoind.generate_block(101 - info['blocks'])
    elif bitcoind.rpc.getwalletinfo()['balance'] < 1:
        logging.debug("Insufficient balance, generating 1 block")
        bitcoind.generate_block(1)

    yield bitcoind

    try:
        bitcoind.rpc.stop()
    except Exception:
        bitcoind.proc.kill()
    bitcoind.proc.wait()


@pytest.fixture
def node_factory(directory, test_name, bitcoind, executor):
    nf = NodeFactory(test_name, bitcoind, executor, directory=directory)
    yield nf
    err_count = 0
    ok = nf.killall([not n.may_fail for n in nf.nodes])
    if VALGRIND:
        for node in nf.nodes:
            err_count += printValgrindErrors(node)
        if err_count:
            raise ValueError("{} nodes reported valgrind errors".format(err_count))

    for node in nf.nodes:
        err_count += printCrashLog(node)
    if err_count:
        raise ValueError("{} nodes had crash.log files".format(err_count))
    for node in nf.nodes:
        err_count += checkReconnect(node)
    if err_count:
        raise ValueError("{} nodes had unexpected reconnections".format(err_count))

    if not ok:
        raise Exception("At least one lightning exited with unexpected non-zero return code")


def getValgrindErrors(node):
    for error_file in os.listdir(node.daemon.lightning_dir):
        if not re.fullmatch("valgrind-errors.\d+", error_file):
            continue
        with open(os.path.join(node.daemon.lightning_dir, error_file), 'r') as f:
            errors = f.read().strip()
            if errors:
                return errors, error_file
    return None, None


def printValgrindErrors(node):
    errors, fname = getValgrindErrors(node)
    if errors:
        print("-" * 31, "Valgrind errors", "-" * 32)
        print("Valgrind error file:", fname)
        print(errors)
        print("-" * 80)
    return 1 if errors else 0


def getCrashLog(node):
    if node.may_fail:
        return None, None
    try:
        crashlog = os.path.join(node.daemon.lightning_dir, 'crash.log')
        with open(crashlog, 'r') as f:
            return f.readlines(), crashlog
    except Exception:
        return None, None


def printCrashLog(node):
    errors, fname = getCrashLog(node)
    if errors:
        print("-" * 10, "{} (last 50 lines)".format(fname), "-" * 10)
        for l in errors[-50:]:
            print(l, end='')
        print("-" * 80)
    return 1 if errors else 0


def checkReconnect(node):
    # Without DEVELOPER, we can't suppress reconnection.
    if node.may_reconnect or not DEVELOPER:
        return 0
    if node.daemon.is_in_log('Peer has reconnected'):
        return 1
    return 0


@pytest.fixture
def executor():
    ex = futures.ThreadPoolExecutor(max_workers=20)
    yield ex
    ex.shutdown(wait=False)
