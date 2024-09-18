#pragma once
#include "rac-packedtypes.hpp"

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

    // NOTE(RYAN_2024-09-14): Cryptographically generated random
    // numbers being used to select MORE super primes
    // (https://en.wikipedia.org/wiki/Super-prime):
    // 355, 306, 531, 436, 464, 325, 429, 496, 516, 507, 285, 555, 239, 279, 255, 556
    static u64 float_seeds[MAX_SEED_CT] = { 21269, 17539, 35993, 27847, 30577, 18917, 27091, 33029, 34607, 33827, 16061, 38039, 12547, 15413, 13649	, 38053 };
    static u64 f32_seed_index = std::rand() % MAX_SEED_CT;
    static mut_u32 f32_seed = float_seeds[f32_seed_index];
    static mut_u32 f32_v = float_seeds[(f32_seed_index + 1) % MAX_SEED_CT];
    static mut_u32 f32_w1 = float_seeds[(f32_seed_index + 2) % MAX_SEED_CT];
    static mut_u32 f32_w2 = float_seeds[(f32_seed_index + 3) % MAX_SEED_CT];
    static mut_u32 f32_u = f32_seed ^ f32_v;

    static u64 f64_seed_index = std::rand() % MAX_SEED_CT;
    static mut_u64 f64_seed = float_seeds[f64_seed_index];
    mut_u64 f64_v = float_seeds[(f64_seed_index + 1) % MAX_SEED_CT];
    mut_u64 f64_w = float_seeds[(f64_seed_index + 2) % MAX_SEED_CT];
    mut_u64 f64_u = f64_seed ^ f64_v;

    class mut_XorRng
    {
    public:

        /*
        Unused transformations:
            y^=y<<c; y^=y<<a; y^=y>>b;
            y^=y>>c; y^=y>>a; y^=y<<b;
        */

        INLINE static u32 GetU32()
        {
            // a = 3
            // b = 25
            // c = 24
            mut_u32 res = u32_seed;
            res ^= res << 3;
            res ^= res >> 25;
            res ^= res << 24;
            u32_seed = res;
            return res;
        }
        INLINE static i32 GetI32()
        {
            // a = 5
            // b = 21
            // c = 12
            mut_i32 res = i32_seed;
            res ^= res >> 5;
            res ^= res << 21;
            res ^= res >> 12;
            i32_seed = res;
            return res;
        }
        INLINE static p32 GetP32()
        {
            // a = 13
            // b = 17
            // c = 5
            mut_p32 res = u32_seed;
            res.uint32 ^= res.uint32 >> 13;
            res.uint32 ^= res.uint32 << 17;
            res.uint32 ^= res.uint32 >> 5;
            u32_seed = res.uint32;
            return res;
        }
        INLINE static u32 GetU32(u32 min_inclusive, u32 max_exclusive)
        {
            assert(min_inclusive < max_exclusive);

            f32 random_num = (f32)GetU32();
            f32 diff = ((f32)max_exclusive - (f32)min_inclusive) + 1.0f;
            return (u32)(random_num * diff) + min_inclusive;
        }
        INLINE static i32 GetI32(i32 min_inclusive, i32 max_exclusive)
        {
            assert(min_inclusive < max_exclusive);

            f32 random_num = (f32)GetU32();
            f32 diff = ((f32)max_exclusive - (f32)min_inclusive) + 1.0f;
            return (i32)(random_num * diff) + min_inclusive;
        }
        INLINE static p32 GetP32(i32 min_inclusive, i32 max_exclusive)
        {
            assert(min_inclusive < max_exclusive);

            f32 random_num = (f32)GetU32();
            f32 diff = ((f32)max_exclusive - (f32)min_inclusive) + 1.0f;
            return p32((i32)(random_num * diff) + min_inclusive);
        }

        INLINE static u64 GetU64()
        {
            // a = 7
            // b = 51
            // c = 24
            mut_u64 res = u64_seed;
            res ^= res >> 7;
            res ^= res >> 24;
            res ^= res << 51;
            u32_seed = res;
            return res;
        }
        INLINE static u64 GetI64()
        {
            // a = 25
            // b = 33
            // c = 36
            mut_i64 res = i64_seed;
            res ^= res << 36;
            res ^= res >> 33;
            res ^= res << 25;
            i32_seed = res;
            return res;
        }
        INLINE static p64 GetP64()
        {
            // a = 16
            // b = 11
            // c = 27
            mut_p64 res = u64_seed;
            res.uint64 ^= res.uint64 >> 27;
            res.uint64 ^= res.uint64 << 11;
            res.uint64 ^= res.uint64 >> 16;
            u64_seed = res.uint64;
            return res;
        }
        INLINE static u64 GetU64(u64 min_inclusive, u64 max_exclusive)
        {
            assert(min_inclusive < max_exclusive);

            f64 random_num = (f64)GetU32();
            f64 diff = ((f64)max_exclusive - (f64)min_inclusive) + 1.0;
            return (u64)(random_num * diff) + min_inclusive;
        }
        INLINE static u64 GetI64(i64 min_inclusive, i64 max_exclusive)
        {
            assert(min_inclusive < max_exclusive);

            f64 random_num = (f64)GetU32();
            f64 diff = ((f64)max_exclusive - (f64)min_inclusive) + 1.0;
            return (i64)(random_num * diff) + min_inclusive;
        }
        INLINE static p64 GetP64(i64 min_inclusive, i64 max_exclusive)
        {
            assert(min_inclusive < max_exclusive);

            f64 random_num = (f64)GetU32();
            f64 diff = ((f64)max_exclusive - (f64)min_inclusive) + 1.0;
            return p64((i64)(random_num * diff) + min_inclusive);
        }

        INLINE static f32 GetF32()
        {
            f32_u = f32_u * 2891336453U + 1640531513U;
            f32_v ^= f32_v >> 13;
            f32_v ^= f32_v << 17;
            f32_v ^= f32_v >> 5;

            f32_w1 = 33378 * (f32_w1 & 0xffff) + (f32_w1 >> 16);
            f32_w2 = 57225 * (f32_w2 & 0xffff) + (f32_w2 >> 16);

            mut_u32 x = f32_u ^ (f32_u << 9);
            x ^= x >> 17;
            x ^= x << 6;

            mut_u32 y = f32_w1 ^ (f32_w1 << 17);
            y ^= y >> 15;
            y ^= y << 5;

            u32 res = (x + f32_v) ^ (y + f32_w2);
            return 2.32830643653869629E-10 * res;
        }
        INLINE static f64 GetF64()
        {
            f64_u = f64_u * 2862933555777941757LL + 7046029254386353087LL;

            f64_v ^= f64_v >> 17;
            f64_v ^= f64_v << 31;
            f64_v ^= f64_v >> 8;

            f64_w = 4294957665U * (f64_w & 0xffffffff) + (f64_w >> 32);

            mut_u64 x = f64_u ^ (f64_u << 21);
            x ^= x >> 35;
            x ^= x << 4;
            u64 res = (x + f64_v) ^ f64_w;
            return 5.42101086242752217E-20 * res;
        }
        INLINE static pf32 GetPF64()
        {

        }
    };
}