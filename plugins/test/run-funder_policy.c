#include "config.h"
#include "../funder_policy.c"
#include <ccan/array_size/array_size.h>
#include <common/setup.h>
#include <stdio.h>

/* AUTOGENERATED MOCKS START */
/* Generated stub for fromwire_bigsize */
bigsize_t fromwire_bigsize(const u8 **cursor UNNEEDED, size_t *max UNNEEDED)
{ fprintf(stderr, "fromwire_bigsize called!\n"); abort(); }
/* Generated stub for fromwire_channel_id */
bool fromwire_channel_id(const u8 **cursor UNNEEDED, size_t *max UNNEEDED,
			 struct channel_id *channel_id UNNEEDED)
{ fprintf(stderr, "fromwire_channel_id called!\n"); abort(); }
/* Generated stub for fromwire_node_id */
void fromwire_node_id(const u8 **cursor UNNEEDED, size_t *max UNNEEDED, struct node_id *id UNNEEDED)
{ fprintf(stderr, "fromwire_node_id called!\n"); abort(); }
/* Generated stub for towire_bigsize */
void towire_bigsize(u8 **pptr UNNEEDED, const bigsize_t val UNNEEDED)
{ fprintf(stderr, "towire_bigsize called!\n"); abort(); }
/* Generated stub for towire_channel_id */
void towire_channel_id(u8 **pptr UNNEEDED, const struct channel_id *channel_id UNNEEDED)
{ fprintf(stderr, "towire_channel_id called!\n"); abort(); }
/* Generated stub for towire_node_id */
void towire_node_id(u8 **pptr UNNEEDED, const struct node_id *id UNNEEDED)
{ fprintf(stderr, "towire_node_id called!\n"); abort(); }
/* AUTOGENERATED MOCKS END */

struct test_case {
	struct amount_sat their_funds;
	struct amount_sat available_funds;
	struct amount_sat *our_last_funds;
	struct amount_sat channel_max;
	struct amount_sat lease_request;

	struct funder_policy policy;

	struct amount_sat exp_our_funds;
	bool expect_err;
};

struct test_case cases[] = {
	/* Straight fixed */
	{
		.their_funds = AMOUNT_SAT(5000),
		.available_funds = AMOUNT_SAT(100000),
		.our_last_funds = NULL,
		.channel_max = AMOUNT_SAT(11000),
		.lease_request = AMOUNT_SAT(0),
		.policy = {
			.opt = FIXED,
			.mod = 1111,
			.min_their_funding = AMOUNT_SAT(0),
			.max_their_funding = AMOUNT_SAT(10000),
			.per_channel_max = AMOUNT_SAT(10000),
			.per_channel_min = AMOUNT_SAT(0),
			.fuzz_factor = 0,
			.reserve_tank = AMOUNT_SAT(0),
			.fund_probability = 100,
			.leases_only = false,
		},

		.exp_our_funds = AMOUNT_SAT(1111),
		.expect_err = false,
	},
	/* Match 0 */
	{
		.their_funds = AMOUNT_SAT(5000),
		.available_funds = AMOUNT_SAT(500),
		.our_last_funds = NULL,
		.channel_max = AMOUNT_SAT(11000),
		.lease_request = AMOUNT_SAT(0),
		.policy = {
			.opt = MATCH,
			.mod = 0,
			.min_their_funding = AMOUNT_SAT(0),
			.max_their_funding = AMOUNT_SAT(10000),
			.per_channel_max = AMOUNT_SAT(10000),
			.per_channel_min = AMOUNT_SAT(1000),
			.fuzz_factor = 0,
			.reserve_tank = AMOUNT_SAT(0),
			.fund_probability = 100,
			.leases_only = false,
		},

		.exp_our_funds = AMOUNT_SAT(0),
		.expect_err = false,
	},
	/* Match 100 */
	{
		.their_funds = AMOUNT_SAT(5000),
		.available_funds = AMOUNT_SAT(6000),
		.our_last_funds = NULL,
		.channel_max = AMOUNT_SAT(11000),
		.lease_request = AMOUNT_SAT(0),
		.policy = {
			.opt = MATCH,
			.mod = 100,
			.min_their_funding = AMOUNT_SAT(0),
			.max_their_funding = AMOUNT_SAT(10000),
			.per_channel_max = AMOUNT_SAT(10000),
			.per_channel_min = AMOUNT_SAT(1000),
			.fuzz_factor = 0,
			.reserve_tank = AMOUNT_SAT(0),
			.fund_probability = 100,
			.leases_only = false,
		},

		.exp_our_funds = AMOUNT_SAT(5000),
		.expect_err = false,
	},
	/* Match 200 */
	{
		.their_funds = AMOUNT_SAT(2500),
		.available_funds = AMOUNT_SAT(6000),
		.our_last_funds = NULL,
		.channel_max = AMOUNT_SAT(11000),
		.lease_request = AMOUNT_SAT(0),
		.policy = {
			.opt = MATCH,
			.mod = 200,
			.min_their_funding = AMOUNT_SAT(0),
			.max_their_funding = AMOUNT_SAT(10000),
			.per_channel_max = AMOUNT_SAT(10000),
			.per_channel_min = AMOUNT_SAT(1000),
			.fuzz_factor = 0,
			.reserve_tank = AMOUNT_SAT(0),
			.fund_probability = 100,
			.leases_only = false,
		},

		.exp_our_funds = AMOUNT_SAT(5000),
		.expect_err = false,
	},
	/* Available 0 */
	{
		.their_funds = AMOUNT_SAT(2500),
		.available_funds = AMOUNT_SAT(5000),
		.our_last_funds = NULL,
		.channel_max = AMOUNT_SAT(11000),
		.lease_request = AMOUNT_SAT(0),
		.policy = {
			.opt = AVAILABLE,
			.mod = 0,
			.min_their_funding = AMOUNT_SAT(0),
			.max_their_funding = AMOUNT_SAT(10000),
			.per_channel_max = AMOUNT_SAT(10000),
			.per_channel_min = AMOUNT_SAT(1000),
			.fuzz_factor = 0,
			.reserve_tank = AMOUNT_SAT(0),
			.fund_probability = 100,
			.leases_only = false,
		},

		.exp_our_funds = AMOUNT_SAT(0),
		.expect_err = false,
	},
	/* Available 50 */
	{
		.their_funds = AMOUNT_SAT(2500),
		.available_funds = AMOUNT_SAT(3000),
		.our_last_funds = NULL,
		.channel_max = AMOUNT_SAT(11000),
		.lease_request = AMOUNT_SAT(0),
		.policy = {
			.opt = AVAILABLE,
			.mod = 50,
			.min_their_funding = AMOUNT_SAT(0),
			.max_their_funding = AMOUNT_SAT(10000),
			.per_channel_max = AMOUNT_SAT(10000),
			.per_channel_min = AMOUNT_SAT(1000),
			.fuzz_factor = 0,
			.reserve_tank = AMOUNT_SAT(0),
			.fund_probability = 100,
			.leases_only = false,
		},

		.exp_our_funds = AMOUNT_SAT(1500),
		.expect_err = false,
	},
	/* Available 100+ */
	{
		.their_funds = AMOUNT_SAT(2500),
		.available_funds = AMOUNT_SAT(5000),
		.our_last_funds = NULL,
		.channel_max = AMOUNT_SAT(11000),
		.lease_request = AMOUNT_SAT(0),
		.policy = {
			.opt = AVAILABLE,
			.mod = 100,
			.min_their_funding = AMOUNT_SAT(0),
			.max_their_funding = AMOUNT_SAT(10000),
			.per_channel_max = AMOUNT_SAT(10000),
			.per_channel_min = AMOUNT_SAT(1000),
			.fuzz_factor = 0,
			.reserve_tank = AMOUNT_SAT(0),
			.fund_probability = 100,
			.leases_only = false,
		},

		.exp_our_funds = AMOUNT_SAT(5000),
		.expect_err = false,
	},
	/* Fixed above per-channel max*/
	{
		.their_funds = AMOUNT_SAT(5000),
		.available_funds = AMOUNT_SAT(5000),
		.our_last_funds = NULL,
		.channel_max = AMOUNT_SAT(11000),
		.policy = {
			.opt = FIXED,
			/* We give these weird numbering so
			 * they're easy to identify when they break */
			.mod = 1011,
			.min_their_funding = AMOUNT_SAT(0),
			.max_their_funding = AMOUNT_SAT(10000),
			.per_channel_max = AMOUNT_SAT(900),
			.per_channel_min = AMOUNT_SAT(100),
			.fuzz_factor = 0,
			.reserve_tank = AMOUNT_SAT(0),
			.fund_probability = 100,
			.leases_only = false,
		},

		.exp_our_funds = AMOUNT_SAT(900),
		.expect_err = false,
	},
	/* Fixed less than available space */
	{
		.their_funds = AMOUNT_SAT(5000),
		.available_funds = AMOUNT_SAT(5000),
		.our_last_funds = NULL,
		.channel_max = AMOUNT_SAT(5500),
		.lease_request = AMOUNT_SAT(0),
		.policy = {
			.opt = FIXED,
			.mod = 1002,
			.min_their_funding = AMOUNT_SAT(0),
			.max_their_funding = AMOUNT_SAT(10000),
			.per_channel_max = AMOUNT_SAT(10000),
			.per_channel_min = AMOUNT_SAT(0),
			.fuzz_factor = 0,
			.reserve_tank = AMOUNT_SAT(0),
			.fund_probability = 100,
			.leases_only = false,
		},

		.exp_our_funds = AMOUNT_SAT(500),
		.expect_err = false,
	},
	/* Fixed less than available funds */
	{
		.their_funds = AMOUNT_SAT(5000),
		.available_funds = AMOUNT_SAT(500),
		.our_last_funds = NULL,
		.channel_max = AMOUNT_SAT(10000),
		.lease_request = AMOUNT_SAT(0),
		.policy = {
			.opt = FIXED,
			.mod = 1001,
			.min_their_funding = AMOUNT_SAT(0),
			.max_their_funding = AMOUNT_SAT(10000),
			.per_channel_max = AMOUNT_SAT(10000),
			.per_channel_min = AMOUNT_SAT(0),
			.fuzz_factor = 0,
			.reserve_tank = AMOUNT_SAT(0),
			.fund_probability = 100,
			.leases_only = false,
		},

		.exp_our_funds = AMOUNT_SAT(500),
		.expect_err = false,
	},
	/* Peer is under 'min_their_funding' */
	{
		.their_funds = AMOUNT_SAT(5000),
		.available_funds = AMOUNT_SAT(1000),
		.our_last_funds = NULL,
		.channel_max = AMOUNT_SAT(10000),
		.lease_request = AMOUNT_SAT(0),
		.policy = {
			.opt = FIXED,
			.mod = 999,
			.min_their_funding = AMOUNT_SAT(5001),
			.max_their_funding = AMOUNT_SAT(10000),
			.per_channel_max = AMOUNT_SAT(10000),
			.per_channel_min = AMOUNT_SAT(0),
			.fuzz_factor = 0,
			.reserve_tank = AMOUNT_SAT(0),
			.fund_probability = 100,
			.leases_only = false,
		},

		.exp_our_funds = AMOUNT_SAT(0),
		.expect_err = true,
	},
	/* Peer exceeds 'max_their_funding' */
	{
		.their_funds = AMOUNT_SAT(5001),
		.available_funds = AMOUNT_SAT(5000),
		.our_last_funds = NULL,
		.channel_max = AMOUNT_SAT(10000),
		.lease_request = AMOUNT_SAT(0),
		.policy = {
			.opt = FIXED,
			.mod = 998,
			.min_their_funding = AMOUNT_SAT(0),
			.max_their_funding = AMOUNT_SAT(500),
			.per_channel_max = AMOUNT_SAT(10000),
			.per_channel_min = AMOUNT_SAT(0),
			.fuzz_factor = 0,
			.reserve_tank = AMOUNT_SAT(0),
			.fund_probability = 100,
			.leases_only = false,
		},

		.exp_our_funds = AMOUNT_SAT(0),
		.expect_err = true,
	},
	/* Fixed less than available funds less reserve tank */
	{
		.their_funds = AMOUNT_SAT(5000),
		.available_funds = AMOUNT_SAT(1000),
		.our_last_funds = NULL,
		.channel_max = AMOUNT_SAT(10000),
		.lease_request = AMOUNT_SAT(0),
		.policy = {
			.opt = FIXED,
			.mod = 997,
			.min_their_funding = AMOUNT_SAT(0),
			.max_their_funding = AMOUNT_SAT(10000),
			.per_channel_max = AMOUNT_SAT(10000),
			.per_channel_min = AMOUNT_SAT(0),
			.fuzz_factor = 0,
			.reserve_tank = AMOUNT_SAT(100),
			.fund_probability = 100,
			.leases_only = false,
		},

		.exp_our_funds = AMOUNT_SAT(900),
		.expect_err = false,
	},
	/* Fixed no funds available after reserve */
	{
		.their_funds = AMOUNT_SAT(5000),
		.available_funds = AMOUNT_SAT(999),
		.our_last_funds = NULL,
		.channel_max = AMOUNT_SAT(10000),
		.lease_request = AMOUNT_SAT(0),
		.policy = {
			.opt = FIXED,
			.mod = 996,
			.min_their_funding = AMOUNT_SAT(0),
			.max_their_funding = AMOUNT_SAT(10000),
			.per_channel_max = AMOUNT_SAT(10000),
			.per_channel_min = AMOUNT_SAT(0),
			.fuzz_factor = 0,
			.reserve_tank = AMOUNT_SAT(1000),
			.fund_probability = 100,
			.leases_only = false,
		},

		.exp_our_funds = AMOUNT_SAT(0),
		.expect_err = true,
	},
	/* Fixed no funds in channel */
	{
		.their_funds = AMOUNT_SAT(5000),
		.available_funds = AMOUNT_SAT(5000),
		.our_last_funds = NULL,
		.channel_max = AMOUNT_SAT(5000),
		.lease_request = AMOUNT_SAT(0),
		.policy = {
			.opt = FIXED,
			.mod = 995,
			.min_their_funding = AMOUNT_SAT(0),
			.max_their_funding = AMOUNT_SAT(10000),
			.per_channel_max = AMOUNT_SAT(10000),
			.per_channel_min = AMOUNT_SAT(0),
			.fuzz_factor = 0,
			.reserve_tank = AMOUNT_SAT(1000),
			.fund_probability = 100,
			.leases_only = false,
		},

		.exp_our_funds = AMOUNT_SAT(0),
		.expect_err = true,
	},
	/* Fixed below per-channel min */
	{
		.their_funds = AMOUNT_SAT(5000),
		.available_funds = AMOUNT_SAT(5000),
		.our_last_funds = NULL,
		.channel_max = AMOUNT_SAT(11000),
		.lease_request = AMOUNT_SAT(0),
		.policy = {
			.opt = FIXED,
			.mod = 988,
			.min_their_funding = AMOUNT_SAT(0),
			.max_their_funding = AMOUNT_SAT(10000),
			.per_channel_max = AMOUNT_SAT(10000),
			.per_channel_min = AMOUNT_SAT(989),
			.fuzz_factor = 0,
			.reserve_tank = AMOUNT_SAT(0),
			.fund_probability = 100,
			.leases_only = false,
		},

		.exp_our_funds = AMOUNT_SAT(0),
		.expect_err = true,
	},
	/* By default, use lease request as ceiling */
	{
		.their_funds = AMOUNT_SAT(5000),
		.available_funds = AMOUNT_SAT(100000),
		.our_last_funds = NULL,
		.channel_max = AMOUNT_SAT(11000),
		.lease_request = AMOUNT_SAT(980),
		.policy = {
			.opt = MATCH,
			.mod = 100,
			.min_their_funding = AMOUNT_SAT(0),
			.max_their_funding = AMOUNT_SAT(10000),
			.per_channel_max = AMOUNT_SAT(100000),
			.per_channel_min = AMOUNT_SAT(0),
			.fuzz_factor = 0,
			.reserve_tank = AMOUNT_SAT(0),
			.fund_probability = 100,
			.leases_only = false,
		},

		.exp_our_funds = AMOUNT_SAT(980),
		.expect_err = false,
	},
	/* Only fund lease requests */
	{
		.their_funds = AMOUNT_SAT(5000),
		.available_funds = AMOUNT_SAT(100000),
		.our_last_funds = NULL,
		.channel_max = AMOUNT_SAT(11000),
		.lease_request = AMOUNT_SAT(0),
		.policy = {
			.opt = FIXED,
			.mod = 985,
			.min_their_funding = AMOUNT_SAT(0),
			.max_their_funding = AMOUNT_SAT(10000),
			.per_channel_max = AMOUNT_SAT(100000),
			.per_channel_min = AMOUNT_SAT(0),
			.fuzz_factor = 0,
			.reserve_tank = AMOUNT_SAT(0),
			.fund_probability = 100,
			.leases_only = true,
		},

		.exp_our_funds = AMOUNT_SAT(0),
		.expect_err = true,
	},
};

static void check_fuzzing(struct test_case fuzzcase)
{
	struct node_id id;
	struct amount_sat our_funds;
	struct amount_sat fuzz_max = AMOUNT_SAT(0),
			  fuzz_min = AMOUNT_SAT(UINT_MAX);
	u64 fuzz_amt = fuzzcase.policy.mod * fuzzcase.policy.fuzz_factor / 100;

	memset(&id, 2, sizeof(struct node_id));

	for (size_t i = 0; i < 100; i++) {
		calculate_our_funding(&fuzzcase.policy, id,
				      fuzzcase.their_funds,
				      fuzzcase.our_last_funds,
				      fuzzcase.available_funds,
				      fuzzcase.channel_max,
				      fuzzcase.lease_request,
				      &our_funds);
		if (amount_sat_greater(our_funds, fuzz_max))
			fuzz_max = our_funds;
		if (amount_sat_less(our_funds, fuzz_min))
			fuzz_min = our_funds;
	}

	assert(fuzz_max.satoshis <= fuzzcase.policy.mod + fuzz_amt);
	assert(fuzz_min.satoshis >= fuzzcase.policy.mod - fuzz_amt);
}

int main(int argc, const char *argv[])
{
	struct funder_policy *policy;
	struct node_id id;
	struct amount_sat empty = AMOUNT_SAT(0), our_funds;
	bool ok = true;
	size_t i = 0, flips = 0;
	struct test_case flipcase, fuzzcase;
	size_t flipcount = 0;
	const char *err;

	common_setup(argv[0]);
	memset(&id, 2, sizeof(struct node_id));

	/* Check the default funder policy, at fixed (0msat) */
	policy = default_funder_policy(tmpctx, FIXED, 0);

	err = calculate_our_funding(policy, id,
				    AMOUNT_SAT(50000),
				    NULL,
				    AMOUNT_SAT(50000),
				    AMOUNT_SAT(100000),
				    AMOUNT_SAT(100000),
				    &our_funds);
	assert(amount_sat_eq(empty, our_funds));
	assert(!err);

	for (i = 0; i < ARRAY_SIZE(cases); i++) {
		err = calculate_our_funding(&cases[i].policy, id,
					    cases[i].their_funds,
					    cases[i].our_last_funds,
					    cases[i].available_funds,
					    cases[i].channel_max,
					    cases[i].lease_request,
					    &our_funds);
		if (!amount_sat_eq(cases[i].exp_our_funds, our_funds)) {
			fprintf(stderr, "FAIL policy: %s. expected %s, got %s\n",
				funder_policy_desc(NULL, &cases[i].policy),
				fmt_amount_sat(NULL, cases[i].exp_our_funds),
				fmt_amount_sat(NULL, our_funds));
			ok = false;
		}
		if (cases[i].expect_err != (err != NULL)) {
			fprintf(stderr, "FAIL policy: %s. expected %serr,"
					" got %s\n",
				funder_policy_desc(NULL, &cases[i].policy),
				cases[i].expect_err ? "" : "no ",
				err ? err : "no err");
			ok = false;
		}
	}
	if (!ok)
		exit(1);

	/* Try a few fund_probabilitys, we should only fund
	 * 1/10th of the time */
	flips = 10;
	flipcase = cases[0];
	flipcase.policy.fund_probability = flips;

	for (i = 0; i < 100 * flips; i++) {
		calculate_our_funding(&flipcase.policy, id,
				      flipcase.their_funds,
				      flipcase.our_last_funds,
				      flipcase.available_funds,
				      flipcase.channel_max,
				      flipcase.lease_request,
				      &our_funds);
		if (!amount_sat_eq(our_funds, AMOUNT_SAT(0)))
			flipcount++;
	}
	/* We should be close to 100, give or take 100 on each side */
	assert(flipcount > 0);
	assert(flipcount < 200);

	/* Try some value fuzzing with a high fuzz (for roll overs) */
	fuzzcase = cases[0];
	fuzzcase.policy.mod = 1000;
	/* This is higher than our allowed fuzz factor, it'll
	 * get shifted down to 100 */
	fuzzcase.policy.fuzz_factor = 100;
	check_fuzzing(fuzzcase);

	/* Try some fuzzing with a low fuzz */
	fuzzcase.policy.fuzz_factor = 1;
	check_fuzzing(fuzzcase);
	common_shutdown();

	return 0;
}
