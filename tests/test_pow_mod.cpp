#include <gtest/gtest.h>
#include <gmpxx.h>
#include "mod_arith.hpp"

TEST(PowModTest, BasicValues)
{
    EXPECT_EQ(modarith::pow_mod(mpz_class(2), mpz_class(10), mpz_class(1000)), mpz_class(24));
    EXPECT_EQ(modarith::pow_mod(mpz_class(2), mpz_class(0),  mpz_class(100)),  mpz_class(1));
    EXPECT_EQ(modarith::pow_mod(mpz_class(2), mpz_class(13), mpz_class(100)),  mpz_class(92));
    EXPECT_EQ(modarith::pow_mod(mpz_class(3), mpz_class(4),  mpz_class(5)),    mpz_class(1));
    EXPECT_EQ(modarith::pow_mod(mpz_class(5), mpz_class(3),  mpz_class(13)),   mpz_class(8));
}

TEST(PowModTest, EdgeCases)
{
    EXPECT_EQ(modarith::pow_mod(mpz_class(0), mpz_class(0), mpz_class(7)),  mpz_class(1));
    EXPECT_EQ(modarith::pow_mod(mpz_class(0), mpz_class(5), mpz_class(7)),  mpz_class(0));
    EXPECT_EQ(modarith::pow_mod(mpz_class(5), mpz_class(0), mpz_class(1)),  mpz_class(0));
    EXPECT_EQ(modarith::pow_mod(mpz_class(5), mpz_class(5), mpz_class(1)),  mpz_class(0));
    EXPECT_EQ(modarith::pow_mod(mpz_class(1), mpz_class(100), mpz_class(97)), mpz_class(1));
    EXPECT_EQ(modarith::pow_mod(mpz_class(2), mpz_class(1), mpz_class(2)),  mpz_class(0));
    EXPECT_EQ(modarith::pow_mod(mpz_class(3), mpz_class(2), mpz_class(2)),  mpz_class(1));
}

TEST(PowModTest, NegativeBase)
{
    EXPECT_EQ(modarith::pow_mod(mpz_class(-2), mpz_class(3), mpz_class(5)), mpz_class(2));
    EXPECT_EQ(modarith::pow_mod(mpz_class(-2), mpz_class(4), mpz_class(5)), mpz_class(1));
    EXPECT_EQ(modarith::pow_mod(mpz_class(-3), mpz_class(3), mpz_class(7)), mpz_class(1));
    EXPECT_EQ(modarith::pow_mod(mpz_class(-1), mpz_class(101), mpz_class(97)), mpz_class(96));
}

TEST(PowModTest, LargeNumbers)
{
    mpz_class base("12345678901234567890");
    mpz_class exp("98765432109876543210");
    mpz_class mod("1000000007");
    mpz_class result = modarith::pow_mod(base, exp, mod);
    EXPECT_TRUE(result >= mpz_class(0) && result < mod);

    mpz_class p("10000000000000000000000000000051");
    EXPECT_EQ(modarith::pow_mod(p - 1, mpz_class(2), p), mpz_class(1));
    EXPECT_EQ(modarith::pow_mod(p - 1, mpz_class(3), p), p - 1);

    mpz_class big_mod("1000000000000000000000000000000000000000007");
    mpz_class b("999999999999999999999999999999999999999999");
    mpz_class e("123456789012345678901234567890");
    mpz_class res = modarith::pow_mod(b, e, big_mod);
    EXPECT_TRUE(res >= mpz_class(0) && res < big_mod);
}

TEST(PowModTest, Properties)
{
    mpz_class a("123456789");
    mpz_class b("987654321");
    mpz_class c("555555555");
    mpz_class m("1000000007");

    mpz_class sum_exp = b + c;
    mpz_class prod_exp = b * c;

    EXPECT_EQ(
        modarith::pow_mod(a, sum_exp, m),
        (modarith::pow_mod(a, b, m) * modarith::pow_mod(a, c, m)) % m
    );

    EXPECT_EQ(
        modarith::pow_mod(a, prod_exp, m),
        modarith::pow_mod(modarith::pow_mod(a, b, m), c, m)
    );

    EXPECT_EQ(
        modarith::pow_mod(a, mpz_class(1), m),
        a % m
    );

    EXPECT_EQ(
        modarith::pow_mod(a, mpz_class(2), m),
        (a * a) % m
    );
}
