#include <gtest/gtest.h>
#include <gmpxx.h>
#include "mod_arith.hpp"

TEST(MulModTest, BasicValues)
{
    EXPECT_EQ(modarith::mul_mod(mpz_class(7),     mpz_class(8),    mpz_class(13)), mpz_class(4));
    EXPECT_EQ(modarith::mul_mod(mpz_class(12345), mpz_class(6789), mpz_class(97)), mpz_class(71));
    EXPECT_EQ(modarith::mul_mod(mpz_class(10),    mpz_class(20),   mpz_class(7)),  mpz_class(4));
    EXPECT_EQ(modarith::mul_mod(mpz_class(15),    mpz_class(15),   mpz_class(10)), mpz_class(5));
}

TEST(MulModTest, EdgeCases)
{
    EXPECT_EQ(modarith::mul_mod(mpz_class(0),   mpz_class(123), mpz_class(17)), mpz_class(0));
    EXPECT_EQ(modarith::mul_mod(mpz_class(123), mpz_class(0),   mpz_class(17)), mpz_class(0));
    EXPECT_EQ(modarith::mul_mod(mpz_class(0),   mpz_class(0),   mpz_class(17)), mpz_class(0));
    EXPECT_EQ(modarith::mul_mod(mpz_class(1),   mpz_class(1),   mpz_class(2)),  mpz_class(1));
    EXPECT_EQ(modarith::mul_mod(mpz_class(1),   mpz_class(100), mpz_class(97)), mpz_class(3));
    EXPECT_EQ(modarith::mul_mod(mpz_class(100), mpz_class(1),   mpz_class(97)), mpz_class(3));

    mpz_class M("1000000007");
    EXPECT_EQ(modarith::mul_mod(M, mpz_class(5), M), mpz_class(0));
    EXPECT_EQ(modarith::mul_mod(mpz_class(5), M, M), mpz_class(0));
}

TEST(MulModTest, ModuloProperties)
{
    mpz_class M("1000000007");
    mpz_class A = M - 1;
    EXPECT_EQ(modarith::mul_mod(A, A, M), mpz_class(1));
    EXPECT_EQ(modarith::mul_mod(A, mpz_class(1), M), A);

    EXPECT_EQ(
        modarith::mul_mod(mpz_class(5), mpz_class(1000000007), mpz_class(97)),
        modarith::mul_mod(mpz_class(5), mpz_class(1000000007 % 97), mpz_class(97))
    );

    EXPECT_EQ(
        modarith::mul_mod(mpz_class(10), mpz_class(20), mpz_class(7)),
        modarith::mul_mod(mpz_class(20), mpz_class(10), mpz_class(7))
    );

    mpz_class a("123456789"), b("987654321"), c("555555555"), m("1000000007");
    mpz_class ab = modarith::mul_mod(a, b, m);
    mpz_class bc = modarith::mul_mod(b, c, m);
    
    EXPECT_EQ(modarith::mul_mod(ab, c, m), modarith::mul_mod(a, bc, m));
}

TEST(MulModTest, PowerOfTwoModulo)
{
    EXPECT_EQ(modarith::mul_mod(mpz_class(5),   mpz_class(7),   mpz_class(8)),  mpz_class(3));
    EXPECT_EQ(modarith::mul_mod(mpz_class(15),  mpz_class(15),  mpz_class(16)), mpz_class(1));
    EXPECT_EQ(modarith::mul_mod(mpz_class(100), mpz_class(200), mpz_class(256)), mpz_class(32));
}

TEST(MulModTest, LargeNumbers)
{
    mpz_class x("123456789012345678901234567890");
    mpz_class y("987654321098765432109876543210");
    mpz_class m("1000000007");
    
    EXPECT_EQ(modarith::mul_mod(x % m, y % m, m), mpz_class("195963067"));
    EXPECT_EQ(modarith::mul_mod(x, y, m), modarith::mul_mod(x % m, y % m, m));

    mpz_class p("10000000000000000000000000000051");
    mpz_class q("10000000000000000000000000000097");
    
    EXPECT_EQ(modarith::mul_mod(p - 1, q - 1, p), mpz_class(1));
    
    mpz_class huge_val("9999999999999999999999999999999999999999999");
    mpz_class huge_mod("1000000000000000000000000000000000000000007");
    
    EXPECT_EQ(modarith::mul_mod(huge_val, mpz_class(2), huge_mod), mpz_class("9999999999999999999999999999999999999999985"));
}
