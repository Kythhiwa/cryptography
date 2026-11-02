#include <ctime>
#include <stdexcept>
#include <gmpxx.h>

#include "order_finder.hpp"
#include "solovay_strassen.hpp"
#include "mod_arith.hpp"

namespace modarith
{

mpz_class find_element_with_order(
    const mpz_class& q, const std::vector<mpz_class>& qd, const mpz_class& m,
    gmp_randclass& rng, int k, int* round_out)
{
    if (round_out) *round_out = -1;

    if (m <= 1)
        throw std::invalid_argument("m must be > 1");
    if (q <= 0)
        throw std::invalid_argument("q must be positive");

    if (q == 1)
    {
        if (round_out) *round_out = 0;
        return 1;
    }

    mpz_class c = mul_mod(m - 1, pow_mod(q, m - 2, m), m);

    std::vector<mpz_class> exponents(qd.size());

    for (std::size_t i = 0; i < qd.size(); ++i)
        exponents[i] = mul_mod(q, pow_mod(qd[i], m - 2, m), m);

    for (int i = 1; i <= k; ++i)
    {
        mpz_class a = rng.get_z_range(m - 1) + 1;
        if (gcd(a, m) != 1)
            continue;

        a = pow_mod(a, c, m);
        if (a == 1)
            continue;

        bool ok = true;
        for (std::size_t j = 0; j < qd.size(); ++j)
        {
            if (pow_mod(a, exponents[j], m) == 1)
            {
                ok = false;
                break;
            }
        }

        if (!ok)
            continue;

        if (round_out) *round_out = i;
        return a;
    }

    return mpz_class(-1);
}

}