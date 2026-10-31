#pragma once
#include <gmpxx.h>

namespace modarith
{

mpz_class gcd_mod(const mpz_class& a, const mpz_class& b, const mpz_class& m);
    
mpz_class pow_mod(const mpz_class& a, const mpz_class& b, const mpz_class& m);

mpz_class mul_mod(const mpz_class& a, const mpz_class& b, const mpz_class& m);

}
