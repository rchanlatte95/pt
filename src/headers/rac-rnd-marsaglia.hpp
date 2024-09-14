#include "rac.hpp"

namespace rac::rnd::marsaglia
{
    class mut_XorRng;
    typedef mut_XorRng* mut_XorRng_ptr;
    typedef mut_XorRng& mut_XorRng_ref;
    typedef const mut_XorRng XorRng;
    typedef const mut_XorRng* XorRng_ref;
    typedef const mut_XorRng& XorRng_ref;

    // NOTE(RYAN_2024-09-14): Cryptographically generated random
    // numbers being used to select super primes
    // (https://en.wikipedia.org/wiki/Super-prime).
    // 41, 57, 190, 161, 127, 80, 98, 18, 187, 141, 124, 169, 75, 129, 180, 160
    u64 MAX_SEED_CT = 16;
    static u32 seeds[MAX_SEED_CT] = { 1063, 1723, 9293, 7481, 5381, 2803, 3733, 283, 8999, 6229, 5107, 8011, 2609, 5503, 8581, 7417 };
    static mut_u32 seed = seeds[std::rand() % MAX_SEED_CT];

    class mut_XorRng
    {
    public:
    };

}