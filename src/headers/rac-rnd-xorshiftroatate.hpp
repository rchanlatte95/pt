#pragma once
#include "rac-rnd-splitmix.hpp"

namespace rac::rnd::XorShiftRotate
{
    class mut_XorRng;
    typedef mut_XorRng* mut_XorRng_ptr;
    typedef mut_XorRng& mut_XorRng_ref;
    typedef const mut_XorRng XsrRng;
    typedef const mut_XorRng* XorRng_ptr;
    typedef const mut_XorRng& XorRng_ref;

    typedef struct mut_xoshiro512p_state
    {
        union
        {
            mut_u64 uint64[8];
            mut_p256 x[2];
        };

        mut_xoshiro512p_state()
        {
            x[0] = p256(0xFEEDC0DE);
            x[1] = p256(0xFEEDC0DE);
        }

        mut_xoshiro512p_state(u64 uint64_0, u64 uint64_1,
                            u64 uint64_2, u64 uint64_3,
                            u64 uint64_4, u64 uint64_5,
                            u64 uint64_6, u64 uint64_7)
        {
            uint64[0] = uint64_0;
            uint64[1] = uint64_1;
            uint64[2] = uint64_2;
            uint64[3] = uint64_3;

            uint64[4] = uint64_4;
            uint64[5] = uint64_5;
            uint64[6] = uint64_6;
            uint64[7] = uint64_7;
        }
    }mut_xoshiro512p_state;
    typedef struct mut_xoshiro512p_state* mut_xoshiro512p_stateptr;
    typedef struct mut_xoshiro512p_state& mut_xoshiro512p_stateref;
    typedef const struct mut_xoshiro512p_state xoshiro512p_state;
    typedef const struct mut_xoshiro512p_state* xoshiro512p_stateptr;
    typedef const struct mut_xoshiro512p_state& xoshiro512p_stateref;

    static INLINE uint64_t rotl(u64 x, i32 k)
    {
        return (x << k) | (x >> (64 - k));
    }

    // NOTE(RYAN_2024-09-14): Cryptographically generated random
    // numbers being used to select super primes
    // (https://en.wikipedia.org/wiki/Super-prime):
    static u64 MAX_SEED_CT = 128;
    static u64 PENULT_SEED_CT = MAX_SEED_CT - 1;
    static mut_u32 seeds[MAX_SEED_CT] = { 81013, 81043, 81077, 81203, 81233, 81371, 81707, 81919, 81931, 81973, 82217, 82361, 82463, 82549, 82657, 82757, 82763, 82799, 82903, 83059, 83101, 83219, 83443, 83617, 192767, 192853, 193009, 193031, 193183, 193373, 193433, 193619, 193703, 193763, 193813, 193873, 193883, 193957, 194101, 194263, 194591, 194723, 194933, 194989, 318211, 318443, 318467, 318569, 318817, 319049, 319061, 319169, 319201, 319339, 319679, 319687, 320027, 320081, 320237, 320431, 320521, 320791, 321017, 321037, 321109, 451499, 451681, 451753, 451859, 451939, 452041, 452213, 452329, 452531, 453199, 453269, 453329, 453377, 453683, 453737, 453797, 453847, 454021, 454379, 454507, 593573, 593627, 594023, 594047, 594203, 594359, 594401, 594421, 595073, 595087, 595267, 595319, 595363, 595453, 595687, 595709, 595807, 595963, 596081, 596179, 737843, 737929, 738107, 738197, 738301, 738383, 738509, 738539, 738877, 738917, 738953, 739027, 739183, 739217, 739253, 739511, 739649, 739751, 740099, 740359, 740429, 891557, 891577 };
    static mut_u32ptr SEEDS_BEGIN = seeds;
    static mut_u32ptr SEEDS_END = seeds + MAX_SEED_CT;

    static mut_u64 seed_state;

    // https://prng.di.unimi.it/xoshiro512plus.c
    static mut_xoshiro512p_state unsigned_state;
    static mut_xoshiro512p_state signed_state;
    static mut_xoshiro512p_state float_state;

    class mut_XorRng
    {
    private:
        INLINE static u64 GetSeed(void)
        {
            seed_state += 0x9e3779b97f4a7c15;
            mut_u64 z = seed_state;
            z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
            z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
            return z ^ (z >> 31);
        }
        INLINE static u64 GetSeed(u64 input_seed)
        {
            seed_state = input_seed;
            return GetSeed();
        }

    public:
        MAY_INLINE static void Init(void)
        {
            std::random_device rand_dev;
            std::mt19937 generator(rand_dev());
            std::uniform_int_distribution<int> distr(0, PENULT_SEED_CT);
            std::shuffle(SEEDS_BEGIN, SEEDS_END, generator);

            seed_state = seeds[distr(generator)];
            unsigned_state = mut_xoshiro512p_state(GetSeed(), GetSeed(),
                                                GetSeed(), GetSeed(),
                                                GetSeed(), GetSeed(),
                                                GetSeed(), GetSeed());

            seed_state = seeds[distr(generator)];
            signed_state = mut_xoshiro512p_state(GetSeed(), GetSeed(),
                                            GetSeed(), GetSeed(),
                                            GetSeed(), GetSeed(),
                                            GetSeed(), GetSeed());

            seed_state = seeds[distr(generator)];
            float_state = mut_xoshiro512p_state(GetSeed(), GetSeed(),
                                            GetSeed(), GetSeed(),
                                            GetSeed(), GetSeed(),
                                            GetSeed(), GetSeed());
        }
        MAY_INLINE static void Init(u64 input_seed, const std::mt19937& gen)
        {
            std::uniform_int_distribution<int> distr(0, MAX_SEED_CT);
            std::shuffle(SEEDS_BEGIN, SEEDS_END, gen);

            mut_u64 transformed_seed = input_seed ^ seeds[distr(gen)];
            transformed_seed ^= transformed_seed << 21;
            transformed_seed ^= transformed_seed >> 35;
            transformed_seed ^= transformed_seed << 4;

            seed_state = transformed_seed;
            unsigned_state = mut_xoshiro512p_state(GetSeed(), GetSeed(),
                                                GetSeed(), GetSeed(),
                                                GetSeed(), GetSeed(),
                                                GetSeed(), GetSeed());

            transformed_seed ^= transformed_seed << 21;
            transformed_seed ^= transformed_seed >> 35;
            transformed_seed ^= transformed_seed << 4;
            seed_state = transformed_seed;
            signed_state = mut_xoshiro512p_state(GetSeed(), GetSeed(),
                                            GetSeed(), GetSeed(),
                                            GetSeed(), GetSeed(),
                                            GetSeed(), GetSeed());

            transformed_seed ^= transformed_seed << 21;
            transformed_seed ^= transformed_seed >> 35;
            transformed_seed ^= transformed_seed << 4;
            seed_state = transformed_seed;
            float_state = mut_xoshiro512p_state(GetSeed(), GetSeed(),
                                            GetSeed(), GetSeed(),
                                            GetSeed(), GetSeed(),
                                            GetSeed(), GetSeed());

        }
        MAY_INLINE static void Init(u32 input_seed)
        {
            std::random_device rnd_dev;
            std::mt19937 base_generator(rnd_dev());
            Init(input_seed, base_generator);
        }

        MAY_INLINE u64 Get(void)
        {
            u64 result = unsigned_state.uint64[0] + unsigned_state.uint64[2];
            u64 t = unsigned_state.uint64[1] << 11;

            unsigned_state.uint64[2] ^= unsigned_state.uint64[0];
            unsigned_state.uint64[5] ^= unsigned_state.uint64[1];
            unsigned_state.uint64[1] ^= unsigned_state.uint64[2];
            unsigned_state.uint64[7] ^= unsigned_state.uint64[3];

            unsigned_state.uint64[3] ^= unsigned_state.uint64[4];
            unsigned_state.uint64[4] ^= unsigned_state.uint64[5];
            unsigned_state.uint64[0] ^= unsigned_state.uint64[6];
            unsigned_state.uint64[6] ^= unsigned_state.uint64[7];

            unsigned_state.uint64[6] ^= t;

            unsigned_state.uint64[7] = rotl(unsigned_state.uint64[7], 21);

            return result;
        }
    };
}