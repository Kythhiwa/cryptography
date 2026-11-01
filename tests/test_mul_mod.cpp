#include <cassert>
#include <gmpxx.h>
#include "mod_arith.hpp"

void test_mul_mod() {
    assert(modarith::mul_mod(mpz_class(7),     mpz_class(8),    mpz_class(13)) == mpz_class(4));   // 56 mod 13
    assert(modarith::mul_mod(mpz_class(12345), mpz_class(6789), mpz_class(97)) == mpz_class(71));
    assert(modarith::mul_mod(mpz_class(0),   mpz_class(123), mpz_class(17)) == mpz_class(0));
    assert(modarith::mul_mod(mpz_class(123), mpz_class(0),   mpz_class(17)) == mpz_class(0));
    assert(modarith::mul_mod(mpz_class(0),   mpz_class(0),   mpz_class(17)) == mpz_class(0));
    assert(modarith::mul_mod(mpz_class(1),   mpz_class(1),   mpz_class(2))  == mpz_class(1));

    mpz_class M("1000000007");
    mpz_class A = M - 1;
    assert(modarith::mul_mod(A, A, M) == mpz_class(1));

    assert(modarith::mul_mod(M, mpz_class(5), M) == mpz_class(0));

    assert(modarith::mul_mod(mpz_class(12345), mpz_class(6789), mpz_class(97)) == mpz_class(71));

    assert(modarith::mul_mod(mpz_class(5), mpz_class(1000000007), mpz_class(97))
           == modarith::mul_mod(mpz_class(5), mpz_class(1000000007 % 97), mpz_class(97)));

    mpz_class x("123456789012345678901234567890");
    mpz_class y("987654321098765432109876543210");
    mpz_class m("1000000007");
    assert(modarith::mul_mod(x % m, y % m, m) == mpz_class("195963067"));

    mpz_class a("123456789"), b("987654321"), c("555555555");
    mpz_class ab = modarith::mul_mod(a, b, m);
    mpz_class bc = modarith::mul_mod(b, c, m);
    assert(modarith::mul_mod(ab, c, m) == modarith::mul_mod(a, bc, m));
}