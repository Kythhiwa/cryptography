#include "jacobi.hpp"
#include "mod_arith.hpp"

namespace util
{

using namespace modarith;

mpz_class jacobi(const mpz_class& a, const mpz_class& n)
{
    if (n == 1)
        return 1;
    if ((n & 1) == 0)
        return 0;

    mpz_class a_p = a;
    mpz_class n_p = n;
    int sign = 1;

    if (a_p < 0)
    {
        a_p = -a_p;
        if ((n_p & 3) == 3)
            sign = -sign;
    }

    while (a_p >= n_p)
    {
        mpz_class t = n_p;
        while ((t << 1) <= a_p)
            t <<= 1;
        a_p -= t;
    }

    while (a_p != 0)
    {
        if (a_p == 1)
            return sign;

        while ((a_p & 1) == 0)
        {
            a_p >>= 1;
            mpz_class n8 = n_p & 7;
            if (n8 == 3 || n8 == 5)
                sign = -sign;
        }

        if (a_p == 1)
            return sign;

        mpz_class n4 = n_p & 3;
        mpz_class a4 = a_p & 3;
        if (n4 == 3 && a4 == 3)
            sign = -sign;

        std::swap(a_p, n_p);
        while (a_p >= n_p)
        {
            mpz_class t = n_p;
            while ((t << 1) <= a_p)
                t <<= 1;
            a_p -= t;
        }
    }
    return 0;
}

}
