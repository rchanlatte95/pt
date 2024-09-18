#pragma once
#include "rac-packedtypes.hpp"

namespace rac::rnd::marsaglia
{
    class mut_XorRng;
    typedef mut_XorRng* mut_XorRng_ptr;
    typedef mut_XorRng& mut_XorRng_ref;
    typedef const mut_XorRng XorRng;
    typedef const mut_XorRng* XorRng_ptr;
    typedef const mut_XorRng& XorRng_ref;

    // NOTE(RYAN_2024-09-14): Cryptographically generated random
    // numbers being used to select super primes
    // (https://en.wikipedia.org/wiki/Super-prime):
    static u64 MAX_SEED_CT = 128;
    static mut_u32 seeds[MAX_SEED_CT] = { 3, 5, 11, 17, 31, 41, 59, 67, 83, 109, 127, 157, 179, 191, 211, 241, 277, 283, 331, 353, 367, 401, 431, 461, 509, 547, 563, 587, 599, 617, 709, 739, 773, 797, 859, 877, 919, 967, 991, 1031, 1063, 1087, 1153, 1171, 1201, 1217, 1297, 1409, 1433, 1447, 1471, 1499, 1523, 1597, 1621, 1669, 1723, 1741, 1787, 1823, 1847, 1913, 2027, 2063, 2081, 2099, 2221, 2269, 2341, 2351, 2381, 2417, 2477, 2549, 2609, 2647, 2683, 2719, 2749, 2803, 2897, 2909, 3001, 3019, 3067, 3109, 3169, 3229, 3259, 3299, 3319, 3407, 3469, 3517, 3559, 3593, 3637, 3733, 3761, 3911, 3943, 4027, 4091, 4133, 4153, 4217, 4273, 4339, 4397, 4421, 4463, 4517, 4549, 4567, 4663, 4759, 4787, 4801, 4877, 4933, 4943, 5021, 5059, 5107, 5189, 5281, 5381, 5441 };
    static mut_u32ptr SEEDS_BEGIN = seeds;
    static mut_u32ptr SEEDS_END = seeds + MAX_SEED_CT;

    static mut_u32 u32_seed = seeds[0];
    static mut_i32 i32_seed = seeds[1];
    static mut_u32 f32_seed = seeds[2];
    static mut_u32 f32_state[4] = { seeds[3], seeds[4], seeds[5], seeds[6] };

    static mut_u64 u64_seed = seeds[7];
    static mut_i64 i64_seed = seeds[8];
    static mut_u64 f64_seed = seeds[9];
    static mut_u64 f64_state[4] = { seeds[10], seeds[11], seeds[12], seeds[13] };

    class mut_XorRng
    {
    public:

        MAY_INLINE static void InitRng()
        {
            std::random_device rand_dev;
            std::mt19937 generator(rand_dev());
            std::uniform_int_distribution<int> distr(0, MAX_SEED_CT);
            std::shuffle(SEEDS_BEGIN, SEEDS_END, generator);

            u32_seed = seeds[distr(generator)];
            i32_seed = seeds[distr(generator)];

            u64_seed = seeds[distr(generator)];
            i64_seed = seeds[distr(generator)];

            f32_seed = seeds[distr(generator)];
            f64_seed = seeds[distr(generator)];
            for (int i = 0; i < 4; ++i)
            {
                f32_state[i] = (u32)seeds[distr(generator)];
                f64_state[i] = seeds[distr(generator)];
            }
        }

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

        INLINE static u64 GetU64()
        {
            // a = 21
            // b = 35
            // c = 4
            mut_u64 res = u64_seed;
            res ^= res << 21;
            res ^= res >> 35;
            res ^= res << 4;
            u64_seed = res;
            return res;
        }
        INLINE static u64 GetI64()
        {
            // a = 20
            // b = 41
            // c = 5
            mut_i64 res = i64_seed;
            res ^= res >> 20;
            res ^= res << 41;
            res ^= res >> 5;
            i64_seed = res;
            return res;
        }
        INLINE static p64 GetP64()
        {
            // a = 17
            // b = 31
            // c = 8
            mut_p64 res = u64_seed;
            res.uint64 ^= res.uint64 << 27;
            res.uint64 ^= res.uint64 >> 11;
            res.uint64 ^= res.uint64 << 16;
            u64_seed = res.uint64;
            return res;
        }

        INLINE static f32 GetF32()
        {
            mut_u32ptr u = f32_state;
            mut_u32ptr v = f32_state + 1;
            mut_u32ptr w1 = f32_state + 2;
            mut_u32ptr w2 = f32_state + 3;

            *u = *u * 2891336453U + 1640531513U;
            *v ^= *v >> 13;
            *v ^= *v << 17;
            *v ^= *v >> 5;

            *w1 = 33378 * (*w1 & 0xffff) + (*w1 >> 16);
            *w2 = 57225 * (*w2 & 0xffff) + (*w2 >> 16);

            mut_u32 x = *u ^ (*u << 9);
            x ^= x >> 17;
            x ^= x << 6;

            mut_u32 y = *w1 ^ (*w1 << 17);
            y ^= y >> 15;
            y ^= y << 5;

            u32 res = (x + *v) ^ (y + *w2);
            return 2.32830643653869629E-10f * (f32)res;
        }
        INLINE static f32 GetF32(f32 min_inclusive, f32 max_exclusive)
        {
            assert(min_inclusive < max_exclusive);

            f32 random_num = GetF32();
            f32 diff = max_exclusive - min_inclusive;
            return (random_num * diff) + min_inclusive;
        }
        INLINE static pf32 GetPF32() { return pf32(GetF32()); }
        INLINE static pf32 GetPF32(f32 min_inclusive, f32 max_exclusive)
        {
            return pf32(GetF32(min_inclusive, max_exclusive));
        }

        INLINE static f64 GetF64()
        {
            mut_u64ptr u = f64_state;
            mut_u64ptr v = f64_state + 1;
            mut_u64ptr w = f64_state + 2;

            *u = *u * 2862933555777941757LL + 7046029254386353087LL;

            *v ^= *v >> 11;
            *v ^= *v << 29;
            *v ^= *v >> 14;

            *w = 4294957665U * (*w & 0xffffffff) + (*w >> 32);

            mut_u64 x = *u ^ (*u << 21);
            x ^= x >> 35;
            x ^= x << 4;
            u64 res = (x + *v) ^ *w;
            return 5.42101086242752217E-20 * res;
        }
        INLINE static f64 GetF64(f64 min_inclusive, f64 max_exclusive)
        {
            assert(min_inclusive < max_exclusive);

            f64 random_num = GetF64();
            f64 diff = max_exclusive - min_inclusive;
            return (random_num * diff) + min_inclusive;
        }
        INLINE static pf64 GetPF64() { return pf64(GetF64()); }
        INLINE static pf64 GetPF64(f64 min_inclusive, f64 max_exclusive)
        {
            return pf64(GetF64(min_inclusive, max_exclusive));
        }

        INLINE static u32 GetU32(u32 min_inclusive, u32 max_exclusive)
        {
            assert(min_inclusive < max_exclusive);

            f32 rand_zero_to_one = GetF32();
            f32 diff = (f32)max_exclusive - (f32)min_inclusive + 1.0f;
            f32 res = rand_zero_to_one * diff;
            return (i32)res + min_inclusive;
        }
        INLINE static i32 GetI32(i32 min_inclusive, i32 max_exclusive)
        {
            assert(min_inclusive < max_exclusive);

            f32 rand_zero_to_one = GetF32();
            f32 diff = (f32)max_exclusive - (f32)min_inclusive + 1.0f;
            f32 res = rand_zero_to_one * diff;
            return (i32)res + min_inclusive;
        }
        INLINE static p32 GetP32(i32 min_inclusive, i32 max_exclusive)
        {
            return p32(GetI32(min_inclusive, max_exclusive));
        }

        INLINE static u64 GetU64(u64 min_inclusive, u64 max_exclusive)
        {
            assert(min_inclusive < max_exclusive);

            f64 rand_zero_to_one = GetF64();
            f64 diff = (f64)max_exclusive - (f64)min_inclusive + 1.0;
            f64 res = rand_zero_to_one * diff;
            return (u64)res + min_inclusive;
        }
        INLINE static u64 GetI64(i64 min_inclusive, i64 max_exclusive)
        {
            assert(min_inclusive < max_exclusive);

            f64 rand_zero_to_one = GetF64();
            f64 diff = (f64)max_exclusive - (f64)min_inclusive + 1.0;
            f64 res = rand_zero_to_one * diff;
            return (i64)res + min_inclusive;
        }
        INLINE static p64 GetP64(i64 min_inclusive, i64 max_exclusive)
        {
            return p64(GetI64(min_inclusive, max_exclusive));
        }

        MAY_INLINE static void InitRng(i32 input_seed)
        {
            std::random_device rand_dev;
            std::mt19937 generator(rand_dev());
            std::uniform_int_distribution<int> distr(0, MAX_SEED_CT);
            std::shuffle(SEEDS_BEGIN, SEEDS_END, generator);

            mut_u32 transformed_seed32 = input_seed ^ seeds[distr(generator)];
            transformed_seed32 ^= transformed_seed32 >> 14;
            transformed_seed32 ^= transformed_seed32 << 29;
            transformed_seed32 ^= transformed_seed32 >> 11;
            u32_seed = transformed_seed32;

            transformed_seed32 ^= input_seed;
            transformed_seed32 ^= transformed_seed32 << 16;
            transformed_seed32 ^= transformed_seed32 >> 5;
            transformed_seed32 ^= transformed_seed32 << 17;
            i32_seed = (i32)transformed_seed32;

            transformed_seed32 ^= input_seed;
            transformed_seed32 ^= transformed_seed32 >> 13;
            transformed_seed32 ^= transformed_seed32 << 9;
            transformed_seed32 ^= transformed_seed32 >> 15;
            f32_seed = transformed_seed32;
            for (int i = 0; i < 4; ++i)
            {
                transformed_seed32 ^= transformed_seed32 >> 13;
                transformed_seed32 ^= transformed_seed32 << 9;
                transformed_seed32 ^= transformed_seed32 >> 15;
                f32_state[i] = transformed_seed32;
            }

            u64 uHigh = input_seed ^ seeds[distr(generator)];
            u64 uLow = input_seed ^ seeds[distr(generator)];
            mut_u64 transformed_seed64 = (uHigh << 32) | uLow;
            transformed_seed64 ^= transformed_seed64 << 30;
            transformed_seed64 ^= transformed_seed64 >> 35;
            transformed_seed64 ^= transformed_seed64 << 13;
            u64_seed = transformed_seed64;

            transformed_seed64 ^= input_seed;
            transformed_seed64 ^= transformed_seed64 << 21;
            transformed_seed64 ^= transformed_seed64 >> 37;
            transformed_seed64 ^= transformed_seed64 << 4;
            i64_seed = (i64)transformed_seed64;

            transformed_seed64 ^= input_seed;
            transformed_seed64 ^= transformed_seed64 << 23;
            transformed_seed64 ^= transformed_seed64 >> 41;
            transformed_seed64 ^= transformed_seed64 << 18;
            f64_seed = transformed_seed64;
            for (int i = 0; i < 4; ++i)
            {
                transformed_seed64 ^= transformed_seed64 >> 23;
                transformed_seed64 ^= transformed_seed64 << 41;
                transformed_seed64 ^= transformed_seed64 >> 18;
                f64_state[i] = transformed_seed64;
            }
        }
    };
}