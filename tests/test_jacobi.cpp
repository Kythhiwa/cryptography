#include <cassert>
#include <gmpxx.h>
#include "jacobi.hpp"

void test_jacobi() {
    using namespace util;

    assert(jacobi(mpz_class(2),  mpz_class(3))  == mpz_class(-1));
    assert(jacobi(mpz_class(3),  mpz_class(7))  == mpz_class(-1));
    assert(jacobi(mpz_class(5),  mpz_class(7))  == mpz_class(-1));
    assert(jacobi(mpz_class(4),  mpz_class(7))  == mpz_class(1));
    assert(jacobi(mpz_class(2),  mpz_class(15)) == mpz_class(1));
    assert(jacobi(mpz_class(6),  mpz_class(11)) == mpz_class(-1));
    assert(jacobi(mpz_class(6),  mpz_class(9))  == mpz_class(0));
    assert(jacobi(mpz_class(0),  mpz_class(7))  == mpz_class(0));
    assert(jacobi(mpz_class(5),  mpz_class(1))  == mpz_class(1));
    assert(jacobi(mpz_class(1001), mpz_class(9907)) == mpz_class(-1));

    assert(jacobi(mpz_class(1),  mpz_class(3))  == mpz_class(1));
    assert(jacobi(mpz_class(1),  mpz_class(7))  == mpz_class(1));
    assert(jacobi(mpz_class(1),  mpz_class(15)) == mpz_class(1));

    assert(jacobi(mpz_class(-1), mpz_class(3))  == mpz_class(-1));
    assert(jacobi(mpz_class(-1), mpz_class(5))  == mpz_class(1));
    assert(jacobi(mpz_class(-1), mpz_class(7))  == mpz_class(-1));
    assert(jacobi(mpz_class(-1), mpz_class(11)) == mpz_class(-1));
    assert(jacobi(mpz_class(-1), mpz_class(13)) == mpz_class(1));

    assert(jacobi(mpz_class(2),  mpz_class(5))  == mpz_class(-1));
    assert(jacobi(mpz_class(2),  mpz_class(7))  == mpz_class(1));
    assert(jacobi(mpz_class(2),  mpz_class(9))  == mpz_class(1));
    assert(jacobi(mpz_class(2),  mpz_class(11)) == mpz_class(-1));
    assert(jacobi(mpz_class(2),  mpz_class(17)) == mpz_class(1));
    assert(jacobi(mpz_class(2),  mpz_class(25)) == mpz_class(1));
    assert(jacobi(mpz_class(2),  mpz_class(27)) == mpz_class(-1));

    assert(jacobi(mpz_class(0),  mpz_class(9))  == mpz_class(0));
    assert(jacobi(mpz_class(3),  mpz_class(9))  == mpz_class(0));
    assert(jacobi(mpz_class(6),  mpz_class(15)) == mpz_class(0));
    assert(jacobi(mpz_class(10), mpz_class(25)) == mpz_class(0));

    assert(jacobi(mpz_class(6),  mpz_class(35)) == mpz_class(-1));
    assert(jacobi(mpz_class(15), mpz_class(77)) == mpz_class(1));
    assert(jacobi(mpz_class(91), mpz_class(105)) == mpz_class(0));

    assert(jacobi(mpz_class(19), mpz_class(23)) == mpz_class(-1));
    assert(jacobi(mpz_class(31), mpz_class(37)) == mpz_class(-1));
    assert(jacobi(mpz_class(29), mpz_class(41)) == mpz_class(-1));
    assert(jacobi(mpz_class(43), mpz_class(53)) == mpz_class(1));

    assert(jacobi(mpz_class(100), mpz_class(101)) == mpz_class(1));

    mpz_class a("123456789012345678901234567890");
    mpz_class n("987654321098765432109876543211");
    mpz_class r = jacobi(a, n);
    assert(r == mpz_class(1) || r == mpz_class(-1) || r == mpz_class(0));

    mpz_class p("1000000007");
    mpz_class q("1000000009");

    assert(jacobi(mpz_class(4), p) == mpz_class(1));
    assert(jacobi(p - 1, p) == mpz_class(-1));
    assert(jacobi(mpz_class(1), p) == mpz_class(1));
    assert(jacobi(p, p) == mpz_class(0));

    assert(jacobi(mpz_class(2), p) * jacobi(mpz_class(3), p) == jacobi(mpz_class(6), p));
    assert(jacobi(mpz_class(5), p) * jacobi(mpz_class(7), p) == jacobi(mpz_class(35), p));

    mpz_class m1("123456789");
    mpz_class m2("987654321");
    assert(jacobi(m1 * m2, p) == jacobi(m1, p) * jacobi(m2, p));

    assert(jacobi(p, q) * jacobi(q, p) == mpz_class(1));

    mpz_class x("12345678901234567890123456789");
    assert(jacobi(x, p) * jacobi(x, p) == mpz_class(1));

    mpz_class big("123456789012345678901234567890");
    mpz_class prime("10000000000000000000000000000051");
    mpz_class jb = jacobi(big, prime);
    assert(jb == mpz_class(1) || jb == mpz_class(-1));

    assert(jacobi(big + prime, prime) == jacobi(big, prime));
    assert(jacobi(big + 2 * prime, prime) == jacobi(big, prime));
}