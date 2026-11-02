#pragma once
#include  <gmpxx.h>
#include <vector>

namespace modarith
{

mpz_class find_element_with_order(
    const mpz_class& q, const std::vector<mpz_class>& qd, const mpz_class& m,
    gmp_randclass& rng, int k = 64, int* round_out = nullptr);

}
