#pragma once

#include <vector>
#include <gmpxx.h>

#include "utils.hpp"

namespace generate
{

mpz_class prime(int bits, gmp_randclass& rng);

mpz_class q_from_small_primes(int k, gmp_randclass& rng,
                              std::vector<mpz_class>& qd_out);

mpz_class m_for_q(const mpz_class& q, int bits, gmp_randclass& rng,
                  mpz_class& R_out);

}
