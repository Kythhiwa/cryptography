#include "mod_arith.hpp"


namespace modarith
{

mpz_class abs(mpz_class a) {return(a > 0 ? a : -a);}

void swap(mpz_class& a, mpz_class& b){mpz_class c = a; a = b, b = c;}

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

mpz_class gcd(const mpz_class& a, const mpz_class& b)
{
    if (a == 0)
        return b;
    if (b == 0)
        return a;

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
            swap(divider, divisible);
        divider -= divisible;
    }
    while (divider > 0);

    return divisible << shift;
}

mpz_class pow_mod(const mpz_class& a, const mpz_class& b, const mpz_class& m)
{
    if (b == 0)
        return mpz_class("1");

    mpz_class res = 1;
    mpz_class mask = mpz_class(1) << (bit_length(b) - 1);

    for (; mask > 0; mask >>= 1)
    {
        res = mul_mod(res, res, m);
        if ((b & mask) != 0)
            res = mul_mod(res, a, m);
    }
    return res;
}

mpz_class mul_mod(mpz_class a, const mpz_class& b, const mpz_class& m) // количество 1 в b меньше чем в a (иначе перед этим swap(a,b))
{
    if (b == 0)
        return mpz_class(0);

    while (a >= m)
    {
        mpz_class t = m;
        while ((t << 1) <= a)
            t <<= 1;
        a -= t;
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
            res += a;
            if (res >= m)
                res -= m;
        }
    }
    return res;
}

}
