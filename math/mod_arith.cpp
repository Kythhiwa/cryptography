#include "mod_arith.hpp"

namespace modarith
{
namespace
{

mpz_class abs(const mpz_class& a) {return(a > 0 ? a : -a);}

int bit_length(const mpz_class& t)
{
    mpz_class x = t;
    int n = 0;
    while (x > 0)
    {
        x >>= 1;
        ++n;
    }
    return n;
}

}

mpz_class gcd(const mpz_class& a, const mpz_class& b)
{
    if (a == 0)
        return abs(b);
    if (b == 0)
        return abs(a);

    mpz_class divisible = abs(a);
    mpz_class divider = abs(b);
    int shift = 0;

    while ((divisible & 1) == 0 && (divider & 1) == 0)
    {
        divisible >>= 1;
        divider >>= 1;
        ++shift;
    }

    while ((divisible & 1) == 0)
        divisible >>= 1;

    do
    {
        while ((divider & 1) == 0)
            divider >>= 1;
        if (divisible > divider)
            std::swap(divider, divisible);
        divider -= divisible;
    }
    while (divider > 0);

    return divisible << shift;
}

mpz_class pow_mod(const mpz_class& a, const mpz_class& b, const mpz_class& m)
{
    if (b == 0)
        return mpz_class(1);

    int len = bit_length(b);
    if (len == 1)
        return mul_mod(a, mpz_class(1), m);
    mpz_class mask = mpz_class(1) << (len - 2);
    mpz_class res = a;

    for (; mask > 0; mask >>= 1)
    {
        res = mul_mod(res, res, m);
        if ((b & mask) != 0)
            res = mul_mod(res, a, m);
    }
    return res;
}

mpz_class mul_mod(const mpz_class& a, const mpz_class& b, const mpz_class& m)
{
    if (b == 0 || a == 0)
        return mpz_class(0);

    mpz_class a_p = a;

    while (a_p >= m)
    {
        mpz_class t = m;
        while ((t << 1) <= a_p)
            t <<= 1;
        a_p -= t;
    }
    mpz_class res = 0;
    mpz_class mask = mpz_class(1) << (bit_length(b) - 1);

    for (; mask > 0; mask >>= 1)
    {
        res += res;
        if (res >= m)
            res -= m;
        if ((b & mask) != 0)
        {
            res += a_p;
            if (res >= m)
                res -= m;
        }
    }
    return res;
}

}
