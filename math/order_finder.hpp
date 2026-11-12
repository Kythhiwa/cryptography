#pragma once
#include <gmpxx.h>
#include <vector>
#include <stdexcept>
#include <optional>


namespace modarith
{

struct OrderResult
{
    mpz_class x;
    int round = -1;
};

OrderResult find_element_with_order(
    const mpz_class& q, const std::vector<mpz_class>& qd, const mpz_class& m,
    gmp_randclass& rng, int k = 64);

}
