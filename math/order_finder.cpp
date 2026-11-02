#include <ctime>
#include <gmpxx.h>

#include "order_finder.hpp"
#include "solovay_strassen.hpp"
#include "mod_arith.hpp"

namespace modarith
{

// q < m
mpz_class find_element_with_order(                                                  // -1 при неудаче
    const mpz_class& q, const std::vector<mpz_class>& qd, const mpz_class& m,
    gmp_randclass& rng, int k)
{
    if (q == 1)
        return 1;

    mpz_class c = mul_mod(m - 1, pow_mod(q, m - 2, m), m);

    std::vector<mpz_class> exponents(qd.size());

    for (std::size_t i = 0; i < qd.size(); ++i)
        exponents[i] = mul_mod(q, pow_mod(qd[i], m - 2, m), m);

    for (int i = 0; i < k; ++i)
    {
        mpz_class a = rng.get_z_range(m - 1) + 1;
        if (gcd(a, m) != 1)
            continue;
        
        a = pow_mod(a, c, m);
        if (a == 1)
            continue;
        
        bool ok = 1;
        for (std::size_t i = 0; i < qd.size(); ++i)
        {
            if (pow_mod(a, exponents[i], m) == 1)
            {
                ok = false;
                break;
            }
        }

        if (!ok)
            continue;
        return a;
    }

    return mpz_class(-1); // неудача
}


}
