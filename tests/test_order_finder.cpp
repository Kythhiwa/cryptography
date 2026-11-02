#include <gtest/gtest.h>
#include <gmpxx.h>
#include <vector>
#include <stdexcept>

#include "order_finder.hpp" 
#include "solovay_strassen.hpp"
#include "mod_arith.hpp"

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
}

TEST_F(OrderFinderTest, ThrowsOnInvalidM)
{
    EXPECT_THROW(
        modarith::find_element_with_order(2, {2}, 1, rng), 
        std::invalid_argument
    );

    EXPECT_THROW(
        modarith::find_element_with_order(4, {2}, 15, rng), 
        std::invalid_argument
    );
}

TEST_F(OrderFinderTest, ThrowsOnInvalidQ)
{
    EXPECT_THROW(
        modarith::find_element_with_order(0, {}, 7, rng), 
        std::invalid_argument
    );
    
    EXPECT_THROW(
        modarith::find_element_with_order(-2, {}, 7, rng), 
        std::invalid_argument
    );
}


TEST_F(OrderFinderTest, TrivialOrderQEqualsOne)
{
    mpz_class res = modarith::find_element_with_order(1, {}, 7, rng);
    EXPECT_EQ(res, 1);
}

TEST_F(OrderFinderTest, CorrectnessForSmallPrime7)
{
    mpz_class m = 7;
    
    {
        mpz_class q = 2;
        std::vector<mpz_class> qd = {2};
        mpz_class x = modarith::find_element_with_order(q, qd, m, rng);
        assert_valid_order(x, q, qd, m);
    }
    
    {
        mpz_class q = 3;
        std::vector<mpz_class> qd = {3};
        mpz_class x = modarith::find_element_with_order(q, qd, m, rng);
        assert_valid_order(x, q, qd, m);
    }
    
    {
        mpz_class q = 6;
        std::vector<mpz_class> qd = {2, 3};
        mpz_class x = modarith::find_element_with_order(q, qd, m, rng);
        assert_valid_order(x, q, qd, m);
    }
}

TEST_F(OrderFinderTest, CorrectnessForPrime11)
{
    mpz_class m = 11;
    mpz_class q = 5;
    std::vector<mpz_class> qd = {5};
    
    mpz_class x = modarith::find_element_with_order(q, qd, m, rng);
    assert_valid_order(x, q, qd, m);
}

TEST_F(OrderFinderTest, CorrectnessForPrime13)
{
    mpz_class m = 13;
    mpz_class q = 4;
    std::vector<mpz_class> qd = {2};
    
    mpz_class x = modarith::find_element_with_order(q, qd, m, rng);
    assert_valid_order(x, q, qd, m);
}

TEST_F(OrderFinderTest, CorrectnessForLargerPrime)
{
    mpz_class m = 101;
    mpz_class q = 20;
    std::vector<mpz_class> qd = {2, 5};

    for (int i = 0; i < 5; ++i)
    {
        mpz_class x = modarith::find_element_with_order(q, qd, m, rng);
        assert_valid_order(x, q, qd, m);
    }
}
