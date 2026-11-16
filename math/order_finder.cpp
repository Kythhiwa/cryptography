#include <ctime>
#include <stdexcept>
#include <gmpxx.h>

#include "order_finder.hpp"
#include "solovay_strassen.hpp"
#include "mod_arith.hpp"

namespace modarith
{

OrderResult find_element_with_order(
    const mpz_class& q, const std::vector<mpz_class>& qd, const mpz_class& m,
    gmp_randclass& rng, int k)
{
    OrderResult res;

    if (m <= 1)
        throw std::invalid_argument("m must be > 1");
    if (q <= 0)
        throw std::invalid_argument("q must be positive");
    if (gcd(q, m - 1) != q)
        throw std::invalid_argument("q must divide m-1");
    if (!util::solovay_strassen(m, 40, rng))
        throw std::invalid_argument("m must be prime");

    if (q == 1)
    {
        res.x = 1;
        res.round = 0;
        return res;
    }

    mpz_class c = mul_mod(m - 1, pow_mod(q, m - 2, m), m);

    std::vector<mpz_class> exponents(qd.size());
    for (std::size_t i = 0; i < qd.size(); ++i)
        exponents[i] = mul_mod(q, pow_mod(qd[i], m - 2, m), m);

    for (std::size_t i = 1; i <= k; ++i)
    {
        mpz_class a = rng.get_z_range(m - 1) + 1;
        if (gcd(a, m) != 1)
            continue;

        a = pow_mod(a, c, m);
        if (a == 1)
            continue;

        bool ok = std::none_of(exponents.begin(), exponents.end(), 
                [&] (const mpz_class& e) { return pow_mod(a, e, m) == 1; });

        if (!ok)
            continue;

        res.x = a;
        res.round = i;
        return res;
    }

    res.x = mpz_class(-1);
    res.round = -1;
    return res;
}

}
