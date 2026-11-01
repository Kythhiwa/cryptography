#include <gtest/gtest.h>
#include <gmpxx.h>
#include <ctime>
#include "solovay_strassen.hpp"

class SolovayStrassenTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        rng.seed(static_cast<unsigned long>(time(nullptr)));
        k = 30;
    }

    gmp_randclass rng{gmp_randinit_mt};
    int k;
};

TEST_F(SolovayStrassenTest, SmallNumbers)
{
    EXPECT_FALSE(util::solovay_strassen(mpz_class(0),  k, rng));
    EXPECT_FALSE(util::solovay_strassen(mpz_class(1),  k, rng));
    EXPECT_TRUE(util::solovay_strassen(mpz_class(2),  k, rng));
    EXPECT_TRUE(util::solovay_strassen(mpz_class(3),  k, rng));
    EXPECT_FALSE(util::solovay_strassen(mpz_class(4),  k, rng));
    EXPECT_TRUE(util::solovay_strassen(mpz_class(5),  k, rng));
    EXPECT_FALSE(util::solovay_strassen(mpz_class(6),  k, rng));
    EXPECT_TRUE(util::solovay_strassen(mpz_class(7),  k, rng));
    EXPECT_FALSE(util::solovay_strassen(mpz_class(8),  k, rng));
    EXPECT_FALSE(util::solovay_strassen(mpz_class(9),  k, rng));
    EXPECT_FALSE(util::solovay_strassen(mpz_class(10), k, rng));
    EXPECT_TRUE(util::solovay_strassen(mpz_class(11), k, rng));
    EXPECT_TRUE(util::solovay_strassen(mpz_class(13), k, rng));
    EXPECT_FALSE(util::solovay_strassen(mpz_class(15), k, rng));
    EXPECT_TRUE(util::solovay_strassen(mpz_class(17), k, rng));
    EXPECT_TRUE(util::solovay_strassen(mpz_class(19), k, rng));
    EXPECT_FALSE(util::solovay_strassen(mpz_class(21), k, rng));
    EXPECT_TRUE(util::solovay_strassen(mpz_class(23), k, rng));
    EXPECT_FALSE(util::solovay_strassen(mpz_class(25), k, rng));
    EXPECT_FALSE(util::solovay_strassen(mpz_class(27), k, rng));
    EXPECT_TRUE(util::solovay_strassen(mpz_class(29), k, rng));
    EXPECT_TRUE(util::solovay_strassen(mpz_class(31), k, rng));
    EXPECT_FALSE(util::solovay_strassen(mpz_class(33), k, rng));
    EXPECT_FALSE(util::solovay_strassen(mpz_class(35), k, rng));
    EXPECT_TRUE(util::solovay_strassen(mpz_class(37), k, rng));
    EXPECT_TRUE(util::solovay_strassen(mpz_class(41), k, rng));
    EXPECT_TRUE(util::solovay_strassen(mpz_class(43), k, rng));
    EXPECT_TRUE(util::solovay_strassen(mpz_class(47), k, rng));
    EXPECT_FALSE(util::solovay_strassen(mpz_class(49), k, rng));
    EXPECT_FALSE(util::solovay_strassen(mpz_class(51), k, rng));
    EXPECT_TRUE(util::solovay_strassen(mpz_class(97), k, rng));
}

TEST_F(SolovayStrassenTest, CompositesAndCarmichael)
{
    EXPECT_FALSE(util::solovay_strassen(mpz_class(100),  k, rng));
    EXPECT_FALSE(util::solovay_strassen(mpz_class(121),  k, rng));
    EXPECT_FALSE(util::solovay_strassen(mpz_class(143),  k, rng));
    EXPECT_FALSE(util::solovay_strassen(mpz_class(169),  k, rng));
    EXPECT_FALSE(util::solovay_strassen(mpz_class(221),  k, rng));
    EXPECT_FALSE(util::solovay_strassen(mpz_class(341),  k, rng));
    EXPECT_FALSE(util::solovay_strassen(mpz_class(561),  k, rng));
    EXPECT_FALSE(util::solovay_strassen(mpz_class(1105), k, rng));
    EXPECT_FALSE(util::solovay_strassen(mpz_class(1729), k, rng));
    EXPECT_FALSE(util::solovay_strassen(mpz_class(2047), k, rng));
    EXPECT_FALSE(util::solovay_strassen(mpz_class(2465), k, rng));
    EXPECT_FALSE(util::solovay_strassen(mpz_class(2821), k, rng));
    EXPECT_FALSE(util::solovay_strassen(mpz_class(6601), k, rng));
}

TEST_F(SolovayStrassenTest, MediumPrimes)
{
    EXPECT_TRUE(util::solovay_strassen(mpz_class(997),   k, rng));
    EXPECT_TRUE(util::solovay_strassen(mpz_class(1009),  k, rng));
    EXPECT_TRUE(util::solovay_strassen(mpz_class(1013),  k, rng));
    EXPECT_TRUE(util::solovay_strassen(mpz_class(1019),  k, rng));
    EXPECT_TRUE(util::solovay_strassen(mpz_class(1021),  k, rng));
    EXPECT_TRUE(util::solovay_strassen(mpz_class(65537), k, rng));
}

TEST_F(SolovayStrassenTest, LargeNumbers)
{
    EXPECT_TRUE(util::solovay_strassen(mpz_class("1000000007"), k, rng));
    EXPECT_TRUE(util::solovay_strassen(mpz_class("1000000009"), k, rng));
    EXPECT_TRUE(util::solovay_strassen(mpz_class("1000003"),    k, rng));
    EXPECT_FALSE(util::solovay_strassen(mpz_class("1000001"),    k, rng));

    EXPECT_TRUE(util::solovay_strassen(mpz_class("2147483647"), k, rng));
    EXPECT_FALSE(util::solovay_strassen(mpz_class("2147483649"), k, rng));

    mpz_class mersenne("2305843009213693951");
    EXPECT_TRUE(util::solovay_strassen(mersenne, k, rng));

    mpz_class fermat_5("4294967297");
    EXPECT_FALSE(util::solovay_strassen(fermat_5, k, rng));
}

TEST_F(SolovayStrassenTest, SemiprimesAndPowers)
{
    EXPECT_FALSE(util::solovay_strassen(mpz_class(9) * mpz_class(11) * mpz_class(13), k, rng));
    EXPECT_FALSE(util::solovay_strassen(mpz_class(101) * mpz_class(103), k, rng));
    EXPECT_FALSE(util::solovay_strassen(mpz_class(999983) * mpz_class(999979), k, rng));

    mpz_class p("1000000007");
    EXPECT_TRUE(util::solovay_strassen(p, k, rng));
    
    for (int trial = 0; trial < 5; ++trial)
    {
        EXPECT_TRUE(util::solovay_strassen(p, k, rng));
    }

    EXPECT_FALSE(util::solovay_strassen(p * p, k, rng));
    EXPECT_FALSE(util::solovay_strassen(p * p * p, k, rng));
}

TEST_F(SolovayStrassenTest, VaryingRounds)
{
    for (int r = 1; r <= 10; ++r)
    {
        EXPECT_TRUE(util::solovay_strassen(mpz_class(7),  r, rng));
        EXPECT_TRUE(util::solovay_strassen(mpz_class(11), r, rng));
        EXPECT_FALSE(util::solovay_strassen(mpz_class(15), r, rng));
        EXPECT_FALSE(util::solovay_strassen(mpz_class(21), r, rng));
    }
}
