#include "solovay_strassen.hpp"
#include "mod_arith.hpp"
#include "jacobi.hpp"

namespace util
{

using namespace modarith;

bool solovay_strassen(const mpz_class& m, int k, gmp_randclass& rng)
{
    if (m < 2)
        return false;
    if (m == 2 || m == 3)
        return true;
    if ((m & 1) == 0)
        return false;

    for (int i = 0; i < k; ++i)
    {
        mpz_class a = rng.get_z_range(m - 3) + 2;

        if (gcd(a, m) != 1)
            return false;

        mpz_class x = pow_mod(a, (m-1) >> 1, m);
        mpz_class j = jacobi(a, m);

        if (j == -1)
            j = m - 1;

        if (x != j)
            return false;
    }
    return true;
}

}
