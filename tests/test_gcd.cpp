#include <cassert>
#include "mod_arith.hpp"

void test_gcd() {
    assert(modarith::gcd(mpz_class(12), mpz_class(8))  == mpz_class(4));
    assert(modarith::gcd(mpz_class(17), mpz_class(5))  == mpz_class(1));
    assert(modarith::gcd(mpz_class(48), mpz_class(18)) == mpz_class(6));
    assert(modarith::gcd(mpz_class(0),  mpz_class(5))  == mpz_class(5));
    assert(modarith::gcd(mpz_class(5),  mpz_class(0))  == mpz_class(5));
}