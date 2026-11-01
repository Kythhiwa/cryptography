#include "mod_arith.hpp"

namespace modarith
{
namespace
{

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
    if(m == 1)
        return mpz_class(0);

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
    if (a_p < 0)
    {
        mpz_class k = -a_p;
        mod_shift(k, m);
        a_p = (k == 0) ? mpz_class(0) : (m - k);
    }
    else
    {
        mod_shift(a_p, m);
    }

    mpz_class b_p;
    const mpz_class* b_ptr = &b;
    if (b < 0)
    {
        mpz_class k = -b;
        mod_shift(k, m);
        b_p = (k == 0) ? mpz_class(0) : (m - k);
        if (b_p == 0) return mpz_class(0);
        b_ptr = &b_p;
    }
    const mpz_class& bb = *b_ptr;

    mpz_class res = 0;
    mpz_class mask = mpz_class(1) << (bit_length(bb) - 1);

    for (; mask > 0; mask >>= 1)
    {
        res += res;
        if (res >= m)
            res -= m;
        if ((bb & mask) != 0)
        {
            res += a_p;
            if (res >= m)
                res -= m;
        }
    }
    return res;
}

void mod_shift(mpz_class& a, const mpz_class& n)
{
    mpz_class temp;
    while (a >= n)
    {
        temp = n;
        while((temp << 1) <= a)
            temp <<= 1;
        a -= temp;
    }
}

}
