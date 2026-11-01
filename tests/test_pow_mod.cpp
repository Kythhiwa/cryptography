#include <cassert>
#include "mod_arith.hpp"

void test_pow_mod() {
    assert(modarith::pow_mod(mpz_class(2), mpz_class(10), mpz_class(1000)) == mpz_class(24));
    assert(modarith::pow_mod(mpz_class(2), mpz_class(0),  mpz_class(100))  == mpz_class(1));
    assert(modarith::pow_mod(mpz_class(2), mpz_class(13), mpz_class(100))  == mpz_class(92));
}