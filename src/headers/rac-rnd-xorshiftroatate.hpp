#pragma once
#include "rac-rnd-splitmix.hpp"

namespace rac::rnd::XorShiftRotate
{
    enum XsrRngState { Unsigned = 0, Signed, Float };

    class mut_XsrRng;
    typedef mut_XsrRng* mut_XsrRng_ptr;
    typedef mut_XsrRng& mut_XsrRng_ref;
    typedef const mut_XsrRng XsrRng;
    typedef const mut_XsrRng* XsrRng_ptr;
    typedef const mut_XsrRng& XsrRng_ref;

    class mut_XsrContext;
    typedef mut_XsrContext* mut_XsrContextPtr;
    typedef mut_XsrContext& mut_XsrContextRef;
    typedef const mut_XsrContext XsrContext;
    typedef const mut_XsrContext* XsrContextPtr;
    typedef const mut_XsrContext& XsrContextRef;

    // https://prng.di.unimi.it/xoshiro512plus.c
    typedef struct mut_xoshiro512p_state
    {
        union
        {
            mut_u32 s32[16];
            mut_u64 s[8];
            mut_p256 x[2];
        };

        mut_xoshiro512p_state()
        {
            x[0] = p256(0xFEEDC0DE);
            x[1] = p256(0xFEEDC0DE);
        }
        mut_xoshiro512p_state(u64 u64_0, u64 u64_1, u64 u64_2, u64 u64_3,
                            u64 u64_4, u64 u64_5, u64 u64_6, u64 u64_7)
        {
            s[0] = u64_0;
            s[1] = u64_1;
            s[2] = u64_2;
            s[3] = u64_3;

            s[4] = u64_4;
            s[5] = u64_5;
            s[6] = u64_6;
            s[7] = u64_7;
        }
    }mut_xoshiro512p_state;
    typedef struct mut_xoshiro512p_state* mut_xoshiro512p_stateptr;
    typedef struct mut_xoshiro512p_state& mut_xoshiro512p_stateref;
    typedef const struct mut_xoshiro512p_state xoshiro512p_state;
    typedef const struct mut_xoshiro512p_state* xoshiro512p_stateptr;
    typedef const struct mut_xoshiro512p_state& xoshiro512p_stateref;

    class mut_XsrContext
    {
    public:
        mut_xoshiro512p_state Unsigned;
        mut_xoshiro512p_state Signed;
        mut_xoshiro512p_state Float;

        mut_XsrContext()
        {
            Unsigned = mut_xoshiro512p_state();
            Signed = mut_xoshiro512p_state();
            Float = mut_xoshiro512p_state();
        }

        INLINE mut_xoshiro512p_state operator[](XsrRngState s) noexcept
        {
            return *(&Unsigned + s);
        }
    };

    static INLINE uint64_t rotl(u64 x, i32 k)
    {
        return (x << k) | (x >> (64 - k));
    }

    // NOTE(RYAN_2024-09-14): Cryptographically generated random
    // numbers being used to select super primes
    // (https://en.wikipedia.org/wiki/Super-prime):
    static u64 MAX_SEED_CT = 128;
    static mut_u64 seeds[MAX_SEED_CT] = { 81013, 81043, 81077, 81203, 81233, 81371, 81707, 81919, 81931, 81973, 82217, 82361, 82463, 82549, 82657, 82757, 82763, 82799, 82903, 83059, 83101, 83219, 83443, 83617, 192767, 192853, 193009, 193031, 193183, 193373, 193433, 193619, 193703, 193763, 193813, 193873, 193883, 193957, 194101, 194263, 194591, 194723, 194933, 194989, 318211, 318443, 318467, 318569, 318817, 319049, 319061, 319169, 319201, 319339, 319679, 319687, 320027, 320081, 320237, 320431, 320521, 320791, 321017, 321037, 321109, 451499, 451681, 451753, 451859, 451939, 452041, 452213, 452329, 452531, 453199, 453269, 453329, 453377, 453683, 453737, 453797, 453847, 454021, 454379, 454507, 593573, 593627, 594023, 594047, 594203, 594359, 594401, 594421, 595073, 595087, 595267, 595319, 595363, 595453, 595687, 595709, 595807, 595963, 596081, 596179, 737843, 737929, 738107, 738197, 738301, 738383, 738509, 738539, 738877, 738917, 738953, 739027, 739183, 739217, 739253, 739511, 739649, 739751, 740099, 740359, 740429, 891557, 891577 };
    static mut_u64ptr SEEDS_BEGIN = seeds;
    static mut_u64ptr SEEDS_END = seeds + MAX_SEED_CT;

    static mut_u64 XsrStateSeed = 0xFEDDEADC0DE;
    static mut_XsrContext XsrState;

    class mut_XsrRng
    {
    private:
        INLINE static u64 GetSeed(void)
        {
            XsrStateSeed += 0x9e3779b97f4a7c15;
            mut_u64 z = XsrStateSeed;
            z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
            z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
            return z ^ (z >> 31);
        }

    public:

        MAY_INLINE static void Init(void)
        {
            std::random_device rand_dev;
            std::mt19937 generator(rand_dev());
            std::uniform_int_distribution<int> distr(0, MAX_SEED_CT - 1);
            std::shuffle(SEEDS_BEGIN, SEEDS_END, generator);

            XsrStateSeed = seeds[distr(generator)];
            XsrState.Unsigned = mut_xoshiro512p_state(GetSeed(), GetSeed(),
                                                    GetSeed(), GetSeed(),
                                                    GetSeed(), GetSeed(),
                                                    GetSeed(), GetSeed());

            XsrStateSeed = seeds[distr(generator)];
            XsrState.Signed = mut_xoshiro512p_state(GetSeed(), GetSeed(),
                                                    GetSeed(), GetSeed(),
                                                    GetSeed(), GetSeed(),
                                                    GetSeed(), GetSeed());

            XsrStateSeed = seeds[distr(generator)];
            XsrState.Float = mut_xoshiro512p_state(GetSeed(), GetSeed(),
                                                    GetSeed(), GetSeed(),
                                                    GetSeed(), GetSeed(),
                                                    GetSeed(), GetSeed());
        }
        MAY_INLINE static void Init(u64 input_seed)
        {
            mut_u64 transformed_seed = input_seed;
            transformed_seed ^= transformed_seed << 21;
            transformed_seed ^= transformed_seed >> 35;
            transformed_seed ^= transformed_seed << 4;
            XsrStateSeed = transformed_seed;
            XsrState.Unsigned = mut_xoshiro512p_state(GetSeed(), GetSeed(),
                                                GetSeed(), GetSeed(),
                                                GetSeed(), GetSeed(),
                                                GetSeed(), GetSeed());

            transformed_seed ^= transformed_seed << 21;
            transformed_seed ^= transformed_seed >> 35;
            transformed_seed ^= transformed_seed << 4;
            XsrStateSeed = transformed_seed;
            XsrState.Signed = mut_xoshiro512p_state(GetSeed(), GetSeed(),
                                                GetSeed(), GetSeed(),
                                                GetSeed(), GetSeed(),
                                                GetSeed(), GetSeed());

            transformed_seed ^= transformed_seed << 21;
            transformed_seed ^= transformed_seed >> 35;
            transformed_seed ^= transformed_seed << 4;
            XsrStateSeed = transformed_seed;
            XsrState.Float = mut_xoshiro512p_state(GetSeed(), GetSeed(),
                                                GetSeed(), GetSeed(),
                                                GetSeed(), GetSeed(),
                                                GetSeed(), GetSeed());
        }
        MAY_INLINE static void Init(std::mt19937& gen)
        {
            std::uniform_int_distribution<int> distr(0, MAX_SEED_CT - 1);
            std::shuffle(SEEDS_BEGIN, SEEDS_END, gen);

            XsrStateSeed = seeds[distr(gen)];
            XsrState.Unsigned = mut_xoshiro512p_state(GetSeed(), GetSeed(),
                                                GetSeed(), GetSeed(),
                                                GetSeed(), GetSeed(),
                                                GetSeed(), GetSeed());

            XsrStateSeed = seeds[distr(gen)];
            XsrState.Signed = mut_xoshiro512p_state(GetSeed(), GetSeed(),
                                                GetSeed(), GetSeed(),
                                                GetSeed(), GetSeed(),
                                                GetSeed(), GetSeed());

            XsrStateSeed = seeds[distr(gen)];
            XsrState.Float = mut_xoshiro512p_state(GetSeed(), GetSeed(),
                                                GetSeed(), GetSeed(),
                                                GetSeed(), GetSeed(),
                                                GetSeed(), GetSeed());
        }

        INLINE static u64 GetU64(void)
        {
            u64 result = XsrState.Unsigned.s[0] + XsrState.Unsigned.s[2];
            u64 t = XsrState.Unsigned.s[1] << 11;

            XsrState.Unsigned.s[2] ^= XsrState.Unsigned.s[0];
            XsrState.Unsigned.s[5] ^= XsrState.Unsigned.s[1];
            XsrState.Unsigned.s[1] ^= XsrState.Unsigned.s[2];
            XsrState.Unsigned.s[7] ^= XsrState.Unsigned.s[3];

            XsrState.Unsigned.s[3] ^= XsrState.Unsigned.s[4];
            XsrState.Unsigned.s[4] ^= XsrState.Unsigned.s[5];
            XsrState.Unsigned.s[0] ^= XsrState.Unsigned.s[6];
            XsrState.Unsigned.s[6] ^= XsrState.Unsigned.s[7];

            XsrState.Unsigned.s[6] ^= t;

            XsrState.Unsigned.s[7] = rotl(XsrState.Unsigned.s[7], 21);

            return result;
        }
        INLINE static i64 GetI64(void)
        {
            i64 result = (i64)(XsrState.Signed.s[0] + XsrState.Signed.s[2]);
            u64 t = XsrState.Signed.s[1] << 11;

            XsrState.Signed.s[2] ^= XsrState.Signed.s[0];
            XsrState.Signed.s[5] ^= XsrState.Signed.s[1];
            XsrState.Signed.s[1] ^= XsrState.Signed.s[2];
            XsrState.Signed.s[7] ^= XsrState.Signed.s[3];

            XsrState.Signed.s[3] ^= XsrState.Signed.s[4];
            XsrState.Signed.s[4] ^= XsrState.Signed.s[5];
            XsrState.Signed.s[0] ^= XsrState.Signed.s[6];
            XsrState.Signed.s[6] ^= XsrState.Signed.s[7];

            XsrState.Signed.s[6] ^= t;

            XsrState.Signed.s[7] = rotl(XsrState.Signed.s[7], 21);

            return result;
        }
        INLINE static f64 GetF64(void)
        {
            f64 result = (f64)(XsrState.Float.s[0] + XsrState.Float.s[2]);
            u64 t = XsrState.Float.s[1] << 11;

            XsrState.Float.s[2] ^= XsrState.Float.s[0];
            XsrState.Float.s[5] ^= XsrState.Float.s[1];
            XsrState.Float.s[1] ^= XsrState.Float.s[2];
            XsrState.Float.s[7] ^= XsrState.Float.s[3];

            XsrState.Float.s[3] ^= XsrState.Float.s[4];
            XsrState.Float.s[4] ^= XsrState.Float.s[5];
            XsrState.Float.s[0] ^= XsrState.Float.s[6];
            XsrState.Float.s[6] ^= XsrState.Float.s[7];

            XsrState.Float.s[6] ^= t;

            XsrState.Float.s[7] = rotl(XsrState.Float.s[7], 21);

            return 5.42101086242752217E-20 * result;
        }

        INLINE static u64 GetU64(u64 min_inclusive, u64 max_exclusive)
        {
            assert(!(min_inclusive >= max_exclusive));

            f64 rand_zero_to_one = GetF64();
            f64 diff = (f64)max_exclusive - (f64)min_inclusive;
            f64 res = rand_zero_to_one * diff;
            return (u64)res + min_inclusive;
        }
        INLINE static u64 GetI64(i64 min_inclusive, i64 max_exclusive)
        {
            assert(!(min_inclusive >= max_exclusive));

            f64 rand_zero_to_one = GetF64();
            f64 diff = (f64)max_exclusive - (f64)min_inclusive;
            f64 res = rand_zero_to_one * diff;
            return (u64)res + min_inclusive;
        }
        INLINE static f64 GetF64(f64 min_inclusive, f64 max_exclusive)
        {
            assert(!(min_inclusive >= max_exclusive));

            f64 random_num = GetF64();
            f64 diff = max_exclusive - min_inclusive;
            return (random_num * diff) + min_inclusive;
        }

        INLINE static u32 GetU32(void)
        {
            u32 result = XsrState.Unsigned.s32[0];
            u64 t = XsrState.Unsigned.s[1] << 11;

            XsrState.Unsigned.s[2] ^= XsrState.Unsigned.s[0];
            XsrState.Unsigned.s[5] ^= XsrState.Unsigned.s[1];
            XsrState.Unsigned.s[1] ^= XsrState.Unsigned.s[2];
            XsrState.Unsigned.s[7] ^= XsrState.Unsigned.s[3];

            XsrState.Unsigned.s[3] ^= XsrState.Unsigned.s[4];
            XsrState.Unsigned.s[4] ^= XsrState.Unsigned.s[5];
            XsrState.Unsigned.s[0] ^= XsrState.Unsigned.s[6];
            XsrState.Unsigned.s[6] ^= XsrState.Unsigned.s[7];

            XsrState.Unsigned.s[6] ^= t;

            XsrState.Unsigned.s[7] = rotl(XsrState.Unsigned.s[7], 21);

            return result;
        }
        INLINE static i32 GetI32(void)
        {
            i32 result = (i32)XsrState.Signed.s32[0];
            u64 t = XsrState.Signed.s[1] << 11;

            XsrState.Signed.s[2] ^= XsrState.Signed.s[0];
            XsrState.Signed.s[5] ^= XsrState.Signed.s[1];
            XsrState.Signed.s[1] ^= XsrState.Signed.s[2];
            XsrState.Signed.s[7] ^= XsrState.Signed.s[3];

            XsrState.Signed.s[3] ^= XsrState.Signed.s[4];
            XsrState.Signed.s[4] ^= XsrState.Signed.s[5];
            XsrState.Signed.s[0] ^= XsrState.Signed.s[6];
            XsrState.Signed.s[6] ^= XsrState.Signed.s[7];

            XsrState.Signed.s[6] ^= t;

            XsrState.Signed.s[7] = rotl(XsrState.Signed.s[7], 21);

            return result;
        }
        INLINE static f32 GetF32(void)
        {
            f32 result = (f32)XsrState.Float.s32[0];
            u64 t = XsrState.Float.s[1] << 11;

            XsrState.Float.s[2] ^= XsrState.Float.s[0];
            XsrState.Float.s[5] ^= XsrState.Float.s[1];
            XsrState.Float.s[1] ^= XsrState.Float.s[2];
            XsrState.Float.s[7] ^= XsrState.Float.s[3];

            XsrState.Float.s[3] ^= XsrState.Float.s[4];
            XsrState.Float.s[4] ^= XsrState.Float.s[5];
            XsrState.Float.s[0] ^= XsrState.Float.s[6];
            XsrState.Float.s[6] ^= XsrState.Float.s[7];

            XsrState.Float.s[6] ^= t;

            XsrState.Float.s[7] = rotl(XsrState.Float.s[7], 21);

            return 2.32830643653869629E-10f * result;
        }

        INLINE static u32 GetU32(u32 min_inclusive, u32 max_exclusive)
        {
            assert(!(min_inclusive >= max_exclusive));

            f32 rand_zero_to_one = GetF32();
            f32 diff = (f32)max_exclusive - (f32)min_inclusive;
            f32 res = rand_zero_to_one * diff;
            return (i32)res + min_inclusive;
        }
        INLINE static i32 GetI32(i32 min_inclusive, i32 max_exclusive)
        {
            assert(!(min_inclusive >= max_exclusive));

            f32 rand_zero_to_one = GetF32();
            f32 diff = (f32)max_exclusive - (f32)min_inclusive;
            f32 res = rand_zero_to_one * diff;
            return (i32)res + min_inclusive;
        }
        INLINE static f32 GetF32(f32 min_inclusive, f32 max_exclusive)
        {
            assert(!(min_inclusive >= max_exclusive));

            f32 random_num = GetF32();
            f32 diff = max_exclusive - min_inclusive;
            return (random_num * diff) + min_inclusive;
        }

        INLINE static u8 GetBit(void)
        {
            i64 v = GetI64();
            return (v > 0) - (v < 0);
        }
        INLINE static bool GetBool(void)
        {
            i64 v = GetI64();
            return (v > 0) - (v < 0);
        }

        MAY_INLINE static XsrContext GetContext(void)
        {
            return XsrState;
        }
        MAY_INLINE static void SetContext(XsrContextRef state)
        {
            XsrState = state;
        }
    };
}