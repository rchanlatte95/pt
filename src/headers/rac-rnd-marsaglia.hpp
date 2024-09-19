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

    typedef struct mut_xor_state128
    {
        mut_p64 x[2];
        mut_xor_state128()
        {
            x[0] = 0xFFFF;
            x[1] = 0xFFFFFFFF;
        }
        mut_xor_state128(u64 high, u64 low)
        {
            x[0] = low;
            x[1] = high;
        }
    }mut_xor_state128;
    typedef struct mut_xor_state128* mut_xor_state128ptr;
    typedef struct mut_xor_state128& mut_xor_state128ref;
    typedef const struct mut_xor_state128 xor_state128;
    typedef const struct mut_xor_state128* xor_state128ptr;
    typedef const struct mut_xor_state128& xor_state128ref;

    typedef struct mut_xor_state256
    {
        mut_p64 x[4];
        mut_xor_state256()
        {
            x[0] = 0xFFFF;
            x[1] = 0xFFFFFFFF;
            x[2] = 0xFFFFFFFFFFFF;
            x[3] = 0xFFFFFFFFFFFFFFFF;
        }
        mut_xor_state256(u64 u0, u64 u1, u64 u2, u64 u3)
        {
            x[0] = u0;
            x[1] = u1;
            x[2] = u2;
            x[3] = u3;
        }
    }mut_xor_state256;
    typedef struct mut_xor_state256* mut_xor_state256ptr;
    typedef struct mut_xor_state256& mut_xor_state256ref;
    typedef const struct mut_xor_state256 xor_state256;
    typedef const struct mut_xor_state256* xor_state256ptr;
    typedef const struct mut_xor_state256& xor_state256ref;

    static INLINE uint64_t rotl(u64 x, i32 k)
    {
        return (x << k) | (x >> (64 - k));
    }

    // NOTE(RYAN_2024-09-14): Cryptographically generated random
    // numbers being used to select super primes
    // (https://en.wikipedia.org/wiki/Super-prime):
    static u64 MAX_SEED_CT = 128;
    static mut_u32 seeds[MAX_SEED_CT] = { 81013, 81043, 81077, 81203, 81233, 81371, 81707, 81919, 81931, 81973, 82217, 82361, 82463, 82549, 82657, 82757, 82763, 82799, 82903, 83059, 83101, 83219, 83443, 83617, 192767, 192853, 193009, 193031, 193183, 193373, 193433, 193619, 193703, 193763, 193813, 193873, 193883, 193957, 194101, 194263, 194591, 194723, 194933, 194989, 318211, 318443, 318467, 318569, 318817, 319049, 319061, 319169, 319201, 319339, 319679, 319687, 320027, 320081, 320237, 320431, 320521, 320791, 321017, 321037, 321109, 451499, 451681, 451753, 451859, 451939, 452041, 452213, 452329, 452531, 453199, 453269, 453329, 453377, 453683, 453737, 453797, 453847, 454021, 454379, 454507, 593573, 593627, 594023, 594047, 594203, 594359, 594401, 594421, 595073, 595087, 595267, 595319, 595363, 595453, 595687, 595709, 595807, 595963, 596081, 596179, 737843, 737929, 738107, 738197, 738301, 738383, 738509, 738539, 738877, 738917, 738953, 739027, 739183, 739217, 739253, 739511, 739649, 739751, 740099, 740359, 740429, 891557, 891577 };
    static mut_u32ptr SEEDS_BEGIN = seeds;
    static mut_u32ptr SEEDS_END = seeds + MAX_SEED_CT;

    //https://prng.di.unimi.it/xoroshiro128plusplus.c
    static mut_xor_state128 u32_state_(seeds[0], seeds[1]);
    static mut_xor_state128 i32_state_(seeds[2], seeds[3]);
    static mut_xor_state128 f32_state_(seeds[4], seeds[5]);

    //https://prng.di.unimi.it/xoshiro256plusplus.c
    static mut_xor_state256 u64_state_(seeds[6], seeds[7], seeds[8], seeds[9]);
    static mut_xor_state256 i64_state_(seeds[10], seeds[11], seeds[12], seeds[13]);
    static mut_xor_state256 f64_state_(seeds[14], seeds[15], seeds[16], seeds[17]);

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
            std::uniform_int_distribution<int> distr(0, MAX_SEED_CT - 1);
            std::shuffle(SEEDS_BEGIN, SEEDS_END, generator);

            u32_seed = seeds[distr(generator)];
            i32_seed = seeds[distr(generator)];
            f32_seed = seeds[distr(generator)];


            mut_u64 High = seeds[distr(generator)];
            mut_u64 Low = seeds[distr(generator)];
            u64_seed = (High << 32) | Low;

            High = seeds[distr(generator)];
            Low = seeds[distr(generator)];
            i64_seed = (High << 32) | Low;

            High = seeds[distr(generator)];
            Low = seeds[distr(generator)];
            f64_seed = (High << 32) | Low;
            for (int i = 0; i < 4; ++i)
            {
                f32_state[i] = seeds[distr(generator)];

                High = seeds[distr(generator)];
                Low = seeds[distr(generator)];
                f64_state[i] = (High << 32) | Low;
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