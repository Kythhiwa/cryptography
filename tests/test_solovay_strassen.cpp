#include <cassert>
#include <gmpxx.h>
#include <ctime>
#include "solovay_strassen.hpp"

void test_solovay_strassen() {
    using namespace util;

    gmp_randclass rng(gmp_randinit_mt);
    rng.seed(static_cast<unsigned long>(time(nullptr)));

    int k = 30;

    assert(solovay_strassen(mpz_class(0),  k, rng) == false);
    assert(solovay_strassen(mpz_class(1),  k, rng) == false);
    assert(solovay_strassen(mpz_class(2),  k, rng) == true);
    assert(solovay_strassen(mpz_class(3),  k, rng) == true);
    assert(solovay_strassen(mpz_class(4),  k, rng) == false);
    assert(solovay_strassen(mpz_class(5),  k, rng) == true);
    assert(solovay_strassen(mpz_class(6),  k, rng) == false);
    assert(solovay_strassen(mpz_class(7),  k, rng) == true);
    assert(solovay_strassen(mpz_class(8),  k, rng) == false);
    assert(solovay_strassen(mpz_class(9),  k, rng) == false);
    assert(solovay_strassen(mpz_class(10), k, rng) == false);
    assert(solovay_strassen(mpz_class(11), k, rng) == true);
    assert(solovay_strassen(mpz_class(13), k, rng) == true);
    assert(solovay_strassen(mpz_class(15), k, rng) == false);
    assert(solovay_strassen(mpz_class(17), k, rng) == true);
    assert(solovay_strassen(mpz_class(19), k, rng) == true);
    assert(solovay_strassen(mpz_class(21), k, rng) == false);
    assert(solovay_strassen(mpz_class(23), k, rng) == true);
    assert(solovay_strassen(mpz_class(25), k, rng) == false);
    assert(solovay_strassen(mpz_class(27), k, rng) == false);
    assert(solovay_strassen(mpz_class(29), k, rng) == true);
    assert(solovay_strassen(mpz_class(31), k, rng) == true);
    assert(solovay_strassen(mpz_class(33), k, rng) == false);
    assert(solovay_strassen(mpz_class(35), k, rng) == false);
    assert(solovay_strassen(mpz_class(37), k, rng) == true);
    assert(solovay_strassen(mpz_class(41), k, rng) == true);
    assert(solovay_strassen(mpz_class(43), k, rng) == true);
    assert(solovay_strassen(mpz_class(47), k, rng) == true);
    assert(solovay_strassen(mpz_class(49), k, rng) == false);
    assert(solovay_strassen(mpz_class(51), k, rng) == false);
    assert(solovay_strassen(mpz_class(97), k, rng) == true);

    assert(solovay_strassen(mpz_class(100), k, rng) == false);
    assert(solovay_strassen(mpz_class(121), k, rng) == false);
    assert(solovay_strassen(mpz_class(143), k, rng) == false);
    assert(solovay_strassen(mpz_class(169), k, rng) == false);
    assert(solovay_strassen(mpz_class(221), k, rng) == false);
    assert(solovay_strassen(mpz_class(341), k, rng) == false);
    assert(solovay_strassen(mpz_class(561), k, rng) == false);
    assert(solovay_strassen(mpz_class(1105), k, rng) == false);
    assert(solovay_strassen(mpz_class(1729), k, rng) == false);
    assert(solovay_strassen(mpz_class(2047), k, rng) == false);
    assert(solovay_strassen(mpz_class(2465), k, rng) == false);
    assert(solovay_strassen(mpz_class(2821), k, rng) == false);
    assert(solovay_strassen(mpz_class(6601), k, rng) == false);

    assert(solovay_strassen(mpz_class(997),  k, rng) == true);
    assert(solovay_strassen(mpz_class(1009), k, rng) == true);
    assert(solovay_strassen(mpz_class(1013), k, rng) == true);
    assert(solovay_strassen(mpz_class(1019), k, rng) == true);
    assert(solovay_strassen(mpz_class(1021), k, rng) == true);
    assert(solovay_strassen(mpz_class(65537), k, rng) == true);

    assert(solovay_strassen(mpz_class("1000000007"), k, rng) == true);
    assert(solovay_strassen(mpz_class("1000000009"), k, rng) == true);
    assert(solovay_strassen(mpz_class("1000003"), k, rng) == true);
    assert(solovay_strassen(mpz_class("1000001"), k, rng) == false);

    assert(solovay_strassen(mpz_class("2147483647"), k, rng) == true);
    assert(solovay_strassen(mpz_class("2147483649"), k, rng) == false);

    mpz_class mersenne("2305843009213693951");
    assert(solovay_strassen(mersenne, k, rng) == true);

    mpz_class fermat_5("4294967297");
    assert(solovay_strassen(fermat_5, k, rng) == false);

    assert(solovay_strassen(mpz_class(9) * mpz_class(11) * mpz_class(13), k, rng) == false);
    assert(solovay_strassen(mpz_class(101) * mpz_class(103), k, rng) == false);
    assert(solovay_strassen(mpz_class(999983) * mpz_class(999979), k, rng) == false);

    mpz_class p("1000000007");
    assert(solovay_strassen(p, k, rng) == true);
    for (int trial = 0; trial < 5; ++trial)
        assert(solovay_strassen(p, k, rng) == true);

    assert(solovay_strassen(p * p, k, rng) == false);
    assert(solovay_strassen(p * p * p, k, rng) == false);

    for (int r = 1; r <= 10; ++r)
    {
        assert(solovay_strassen(mpz_class(7),  r, rng) == true);
        assert(solovay_strassen(mpz_class(11), r, rng) == true);
        assert(solovay_strassen(mpz_class(15), r, rng) == false);
        assert(solovay_strassen(mpz_class(21), r, rng) == false);
    }
}