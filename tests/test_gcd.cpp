#include <gtest/gtest.h>
#include <gmpxx.h>
#include "mod_arith.hpp"

TEST(GcdTest, BasicValues)
{
    EXPECT_EQ(modarith::gcd(mpz_class(12), mpz_class(8)),  mpz_class(4));
    EXPECT_EQ(modarith::gcd(mpz_class(17), mpz_class(5)),  mpz_class(1));
    EXPECT_EQ(modarith::gcd(mpz_class(48), mpz_class(18)), mpz_class(6));
    EXPECT_EQ(modarith::gcd(mpz_class(0),  mpz_class(5)),  mpz_class(5));
    EXPECT_EQ(modarith::gcd(mpz_class(5),  mpz_class(0)),  mpz_class(5));
}

TEST(GcdTest, EdgeCases)
{
    EXPECT_EQ(modarith::gcd(mpz_class(0), mpz_class(0)),   mpz_class(0));
    EXPECT_EQ(modarith::gcd(mpz_class(0), mpz_class(1)),   mpz_class(1));
    EXPECT_EQ(modarith::gcd(mpz_class(1), mpz_class(0)),   mpz_class(1));
    EXPECT_EQ(modarith::gcd(mpz_class(1), mpz_class(1)),   mpz_class(1));
    EXPECT_EQ(modarith::gcd(mpz_class(1), mpz_class(100)), mpz_class(1));
    EXPECT_EQ(modarith::gcd(mpz_class(100), mpz_class(1)), mpz_class(1));
    EXPECT_EQ(modarith::gcd(mpz_class(7), mpz_class(7)),   mpz_class(7));
}

TEST(GcdTest, NegativeNumbers)
{
    EXPECT_EQ(modarith::gcd(mpz_class(-12), mpz_class(8)),  mpz_class(4));
    EXPECT_EQ(modarith::gcd(mpz_class(12), mpz_class(-8)),  mpz_class(4));
    EXPECT_EQ(modarith::gcd(mpz_class(-12), mpz_class(-8)), mpz_class(4));
    EXPECT_EQ(modarith::gcd(mpz_class(-17), mpz_class(5)),  mpz_class(1));
    EXPECT_EQ(modarith::gcd(mpz_class(-5),  mpz_class(0)),  mpz_class(5));
    EXPECT_EQ(modarith::gcd(mpz_class(0),   mpz_class(-5)), mpz_class(5));
}

TEST(GcdTest, MultiplesAndPrimes)
{
    EXPECT_EQ(modarith::gcd(mpz_class(100), mpz_class(25)), mpz_class(25));
    EXPECT_EQ(modarith::gcd(mpz_class(25), mpz_class(100)), mpz_class(25));
    EXPECT_EQ(modarith::gcd(mpz_class(97), mpz_class(89)),  mpz_class(1));
    EXPECT_EQ(modarith::gcd(mpz_class(1000000007), mpz_class(1000000009)), mpz_class(1));
    EXPECT_EQ(modarith::gcd(mpz_class(100), mpz_class(10)), mpz_class(10));
    EXPECT_EQ(modarith::gcd(mpz_class(10), mpz_class(100)), mpz_class(10));
}

TEST(GcdTest, PowersOfTwo)
{
    EXPECT_EQ(modarith::gcd(mpz_class(1024), mpz_class(256)),  mpz_class(256));
    EXPECT_EQ(modarith::gcd(mpz_class(256), mpz_class(1024)),  mpz_class(256));
    EXPECT_EQ(modarith::gcd(mpz_class(1024), mpz_class(1023)), mpz_class(1));
    EXPECT_EQ(modarith::gcd(mpz_class(1024), mpz_class(768)),  mpz_class(256));
    EXPECT_EQ(modarith::gcd(mpz_class(65536), mpz_class(4096)), mpz_class(4096));
}

TEST(GcdTest, LargeNumbers)
{
    mpz_class a("123456789123456789123456789");
    mpz_class b = a * mpz_class(42);
    EXPECT_EQ(modarith::gcd(a, b), a);
    EXPECT_EQ(modarith::gcd(b, a), a);

    mpz_class c("1000000000000000000000000000000");
    mpz_class d("250000000000000000000000000000");
    EXPECT_EQ(modarith::gcd(c, d), d);
    EXPECT_EQ(modarith::gcd(d, c), d);

    mpz_class p1("10000000000000000000000000000051");
    mpz_class p2("10000000000000000000000000000097");
    EXPECT_EQ(modarith::gcd(p1, p2), mpz_class(1));

    mpz_class m("987654321098765432109876543210");
    mpz_class n("123456789012345678901234567890");
    EXPECT_EQ(modarith::gcd(m, n), mpz_class("9000000000900000000090"));
}
