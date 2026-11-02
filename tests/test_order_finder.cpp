#include <gtest/gtest.h>
#include <gmpxx.h>
#include <vector>
#include <stdexcept>
#include <ctime>

#include "order_finder.hpp" 
#include "solovay_strassen.hpp"
#include "mod_arith.hpp"
#include "generate.hpp"

/*
 *  q - делитель m - 1
 *  m - простое
 */


class OrderFinderTest : public ::testing::Test
{
protected:

    void SetUp() override
    {
        rng.seed(static_cast<unsigned long>(time(nullptr)));
    }

    gmp_randclass rng{gmp_randinit_mt};
};

void assert_valid_order(const mpz_class& x, const mpz_class& q, 
    const std::vector<mpz_class>& qd, const mpz_class& m) 
{
    (void)qd;
    EXPECT_GE(x, 1);
    EXPECT_LT(x, m);

    mpz_class pow_q = modarith::pow_mod(x, q, m);
    EXPECT_EQ(pow_q, 1) << "Failed: x^q != 1 (mod m)";
}

TEST_F(OrderFinderTest, ThrowsOnInvalidM)
{
    EXPECT_THROW(
        modarith::find_element_with_order(2, {2}, 1, rng, 64, nullptr), 
        std::invalid_argument
    );
}

TEST_F(OrderFinderTest, ThrowsOnInvalidQ)
{
    EXPECT_THROW(
        modarith::find_element_with_order(0, {}, 7, rng, 64, nullptr), 
        std::invalid_argument
    );
    
    EXPECT_THROW(
        modarith::find_element_with_order(-2, {}, 7, rng, 64, nullptr), 
        std::invalid_argument
    );
}


TEST_F(OrderFinderTest, TrivialOrderQEqualsOne)
{
    mpz_class res = modarith::find_element_with_order(1, {}, 7, rng, 64, nullptr);
    EXPECT_EQ(res, 1);
}

TEST_F(OrderFinderTest, CorrectnessForSmallPrime7)
{
    mpz_class m = 7;
    
    {
        mpz_class q = 2;
        std::vector<mpz_class> qd = {2};
        mpz_class x = modarith::find_element_with_order(q, qd, m, rng, 64, nullptr);
        assert_valid_order(x, q, qd, m);
    }
    
    {
        mpz_class q = 3;
        std::vector<mpz_class> qd = {3};
        mpz_class x = modarith::find_element_with_order(q, qd, m, rng, 64, nullptr);
        assert_valid_order(x, q, qd, m);
    }
    
    {
        mpz_class q = 6;
        std::vector<mpz_class> qd = {2, 3};
        mpz_class x = modarith::find_element_with_order(q, qd, m, rng, 64, nullptr);
        assert_valid_order(x, q, qd, m);
    }
}

TEST_F(OrderFinderTest, CorrectnessForPrime11)
{
    mpz_class m = 11;
    mpz_class q = 5;
    std::vector<mpz_class> qd = {5};
    
    mpz_class x = modarith::find_element_with_order(q, qd, m, rng, 64, nullptr);
    assert_valid_order(x, q, qd, m);
}

TEST_F(OrderFinderTest, CorrectnessForPrime13)
{
    mpz_class m = 13;
    mpz_class q = 4;
    std::vector<mpz_class> qd = {2};
    
    mpz_class x = modarith::find_element_with_order(q, qd, m, rng, 64, nullptr);
    assert_valid_order(x, q, qd, m);
}

TEST_F(OrderFinderTest, CorrectnessForLargerPrime)
{
    mpz_class m = 101;
    mpz_class q = 20;
    std::vector<mpz_class> qd = {2, 5};

    for (int i = 0; i < 5; ++i)
    {
        mpz_class x = modarith::find_element_with_order(q, qd, m, rng, 64, nullptr);
        assert_valid_order(x, q, qd, m);
    }
}

/* ========== 1000 запусков на 32-битных числах ========== */

TEST_F(OrderFinderTest, ThousandRunsOn32Bit)
{
    rng.seed(42);

    const int NUM_M        = 10;
    const int RUNS_PER_M   = 100;
    const int K            = 200;

    int total_runs = 0;
    int failed_not_found = 0;
    int failed_round = 0;

    for (int mi = 0; mi < NUM_M; ++mi)
    {
        mpz_class p1, p2;
        mpz_class m = generate::m_2p1p2(32, rng, p1, p2);
        auto cases = generate::make_cases(m, p1, p2);

        for (int r = 0; r < RUNS_PER_M; ++r)
        {
            const auto& tc = cases[r % cases.size()];
            int round_out = -1;

            mpz_class x = modarith::find_element_with_order(
                tc.q, tc.qd, tc.m, rng, K, &round_out);

            ++total_runs;

            if (x == mpz_class(-1)) { ++failed_not_found; continue; }
            if (round_out < 1)      { ++failed_round;     continue; }
            assert_valid_order(x, tc.q, tc.qd, tc.m);
        }
    }

    EXPECT_EQ(total_runs, 1000);
    EXPECT_EQ(failed_not_found, 0) << "algorithm returned -1";
    EXPECT_EQ(failed_round, 0)     << "round_out not set";
}

TEST_F(OrderFinderTest, SingleModulusManyRunsOn32Bit)
{
    rng.seed(7);

    mpz_class p1, p2;
    mpz_class m = generate::m_2p1p2(32, rng, p1, p2);
    auto cases = generate::make_cases(m, p1, p2);

    int failed = 0;
    for (int r = 0; r < 1000; ++r)
    {
        const auto& tc = cases[r % cases.size()];
        int round_out = -1;
        mpz_class x = modarith::find_element_with_order(
            tc.q, tc.qd, tc.m, rng, 200, &round_out);

        if (x == mpz_class(-1)) { ++failed; continue; }
        assert_valid_order(x, tc.q, tc.qd, tc.m);
    }

    EXPECT_EQ(failed, 0);
}