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
    EXPECT_GE(x, 1);
    EXPECT_LT(x, m);

    mpz_class pow_q = modarith::pow_mod(x, q, m);
    EXPECT_EQ(pow_q, 1) << "Failed: x^q != 1 (mod m)";

    for (const auto& d : qd) 
    {
        mpz_class exp = modarith::mul_mod(q, modarith::pow_mod(d, m - 2, m), m);
        EXPECT_NE(modarith::pow_mod(x, exp, m), 1)
            << "Failed: order is smaller than q (divisor " << d << ")";
    }
}

TEST_F(OrderFinderTest, ThrowsOnInvalidM)
{
    EXPECT_THROW(
        modarith::find_element_with_order(2, {2}, 1, rng, 64), 
        std::invalid_argument
    );
}

TEST_F(OrderFinderTest, ThrowsOnInvalidQ)
{
    EXPECT_THROW(
        modarith::find_element_with_order(0, {}, 7, rng, 64), 
        std::invalid_argument
    );
    
    EXPECT_THROW(
        modarith::find_element_with_order(-2, {}, 7, rng, 64), 
        std::invalid_argument
    );
}


TEST_F(OrderFinderTest, TrivialOrderQEqualsOne)
{
    auto res = modarith::find_element_with_order(1, {}, 7, rng, 64);
    EXPECT_EQ(res.x, 1);
}

TEST_F(OrderFinderTest, CorrectnessForSmallPrime7)
{
    mpz_class m = 7;
    
    {
        mpz_class q = 2;
        std::vector<mpz_class> qd = {2};
        auto res = modarith::find_element_with_order(q, qd, m, rng, 64);
        assert_valid_order(res.x, q, qd, m);
    }
    
    {
        mpz_class q = 3;
        std::vector<mpz_class> qd = {3};
        auto res = modarith::find_element_with_order(q, qd, m, rng, 64);
        assert_valid_order(res.x, q, qd, m);
    }
    
    {
        mpz_class q = 6;
        std::vector<mpz_class> qd = {2, 3};
        auto res = modarith::find_element_with_order(q, qd, m, rng, 64);
        assert_valid_order(res.x, q, qd, m);
    }
}

TEST_F(OrderFinderTest, CorrectnessForPrime11)
{
    mpz_class m = 11;
    mpz_class q = 5;
    std::vector<mpz_class> qd = {5};
    
    auto res = modarith::find_element_with_order(q, qd, m, rng, 64);
    assert_valid_order(res.x, q, qd, m);
}

TEST_F(OrderFinderTest, CorrectnessForPrime13)
{
    mpz_class m = 13;
    mpz_class q = 4;
    std::vector<mpz_class> qd = {2};
    
    auto res = modarith::find_element_with_order(q, qd, m, rng, 64);
    assert_valid_order(res.x, q, qd, m);
}

TEST_F(OrderFinderTest, CorrectnessForLargerPrime)
{
    mpz_class m = 101;
    mpz_class q = 20;
    std::vector<mpz_class> qd = {2, 5};

    for (int i = 0; i < 5; ++i)
    {
        auto res = modarith::find_element_with_order(q, qd, m, rng, 64);
        assert_valid_order(res.x, q, qd, m);
    }
}

/* ========== 1000 запусков на 32-битных числах ========== */
TEST_F(OrderFinderTest, ThousandRunsOn32Bit)
{
    rng.seed(42);

    const int NUM_CONFIGS = 10;
    const int RUNS_PER_CFG = 100;
    const int K            = 200;
    const int BITS         = 64;

    int total_runs = 0;
    int failed_not_found = 0;
    int failed_round = 0;

    for (int ci = 0; ci < NUM_CONFIGS; ++ci)
    {
        std::vector<mpz_class> qd;
        mpz_class q = generate::q_from_small_primes(1 + (ci % 5), rng, qd);

        mpz_class R;
        mpz_class m = generate::m_for_q(q, BITS, rng, R);

        for (int r = 0; r < RUNS_PER_CFG; ++r)
        {
            auto res = modarith::find_element_with_order(
                q, qd, m, rng, K);

            ++total_runs;

            if (res.x == mpz_class(-1)) { ++failed_not_found; continue; }
            if (res.round < 1)          { ++failed_round;     continue; }
            assert_valid_order(res.x, q, qd, m);
        }
    }

    EXPECT_EQ(total_runs, 1000);
    EXPECT_EQ(failed_not_found, 0) << "algorithm returned -1";
    EXPECT_EQ(failed_round, 0)     << "round_out not set";
}

TEST_F(OrderFinderTest, ModulusManyRunsOn32Bit)
{
    rng.seed(7);

    const int NUM_CONFIGS = 50;
    const int RUNS_PER_CFG = 20;
    const int K            = 200;
    const int BITS         = 64;

    int failed = 0;
    int total  = 0;

    for (int ci = 0; ci < NUM_CONFIGS; ++ci)
    {
        std::vector<mpz_class> qd;
        mpz_class q = generate::q_from_small_primes(1 + (ci % 5), rng, qd);

        mpz_class R;
        mpz_class m = generate::m_for_q(q, BITS, rng, R);

        for (int r = 0; r < RUNS_PER_CFG; ++r)
        {
            auto res = modarith::find_element_with_order(
                q, qd, m, rng, K);
            ++total;
            if (res.x == mpz_class(-1)) { ++failed; continue; }
            assert_valid_order(res.x, q, qd, m);
        }
    }

    EXPECT_EQ(total, NUM_CONFIGS * RUNS_PER_CFG);
    EXPECT_EQ(failed, 0);
}