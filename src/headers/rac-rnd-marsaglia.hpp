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
    // (https://en.wikipedia.org/wiki/Super-prime):
    // 41, 57, 190, 161, 127, 80, 98, 18, 187, 141, 124, 169, 75, 129, 180, 160
    u64 MAX_SEED_CT = 16;
    static u32 u32_seeds[MAX_SEED_CT] = { 1063, 1723, 9293, 7481, 5381, 2803, 3733, 283, 8999, 6229, 5107, 8011, 2609, 5503, 8581, 7417 };
    static mut_u32 u32_seed = u32_seeds[std::rand() % MAX_SEED_CT];
    static mut_i32 i32_seed = u32_seeds[std::rand() % MAX_SEED_CT];

    // NOTE(RYAN_2024-09-14): Cryptographically generated random
    // numbers being used to select MORE super primes
    // (https://en.wikipedia.org/wiki/Super-prime):
    // 155, 143, 135, 85, 193, 199, 111, 192, 2, 140, 46, 146, 6, 15, 191, 188
    static u64 u64_seeds[MAX_SEED_CT] = { 7057, 6323, 5801, 3067, 9461, 9859, 4463, 9403, 5, 6217, 1217, 6469, 41, 211, 9319, 9041 };
    static mut_u64 u64_seed = u64_seeds[std::rand() % MAX_SEED_CT];
    static mut_u64 i64_seed = u64_seeds[std::rand() % MAX_SEED_CT];

    class mut_XorRng
    {
    public:

        static u32 GetU32()
        {
            mut_u32 res = u32_seed;
            res ^= res << 3;
            res ^= res >> 25;
            res ^= res << 24;
            u32_seed = res;
            return res;
        }
        static i32 GetI32()
        {
            mut_i32 res = i32_seed;
            res ^= res >> 5;
            res ^= res << 21;
            res ^= res >> 12;
            i32_seed = res;
            return res;
        }

        static u64 GetU64()
        {
            mut_u64 res = u64_seed;
            res ^= res >> 7;
            res ^= res >> 24;
            res ^= res << 51;
            u32_seed = res;
            return res;
        }

        /*
        y�=y>>c; y�=y<<b; y�=y>>a;
        y�=y<<a; y�=y<<c; y�=y>>b;
        y�=y<<c; y�=y<<a; y�=y>>b;
        y�=y>>c; y�=y>>a; y�=y<<b;
        */
        static u64 GetI64()
        {
            mut_i64 res = i64_seed;
            res ^= res << 36;
            res ^= res >> 33;
            res ^= res << 25;
            i32_seed = res;
            return res;
        }

        //16,11,27
        //4, 9,13
    };
}