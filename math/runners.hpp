#pragma once

#include <gmpxx.h>
#include <vector>
#include <stdexcept>

namespace runners {

double run_find_element_with_order(
    const mpz_class& q,
    const std::vector<mpz_class>& qd,
    const mpz_class& m,
    gmp_randclass& rng,
    const double PTarget,
    const int l,
    std::vector<int>& rounds_out,
    int maxRounds = 0);

int count_N(const mpz_class& q, const std::vector<mpz_class>& qd, double PTarget);
}
