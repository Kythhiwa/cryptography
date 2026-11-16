#include "utils.hpp"


namespace utils 
{



std::size_t bit_length(const mpz_class& t)
{
    mpz_class x = t;
    std::size_t n = 0;
    while (x > 0)
    {
        x >>= 1;
        ++n;
    }
    return n;
}


}
