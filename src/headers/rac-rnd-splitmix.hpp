#pragma once
#include "rac-packedtypes.hpp"

namespace rac::rnd::SplitMix
{
    class mut_SmRng;
    typedef mut_SmRng* mut_SmRng_ptr;
    typedef mut_SmRng& mut_SmRng_ref;
    typedef const mut_SmRng SmRng;
    typedef const mut_SmRng* SmRng_ptr;
    typedef const mut_SmRng& SmRng_ref;

    // NOTE(RYAN_2024-09-14): First 128 Super primes
    // (https://en.wikipedia.org/wiki/Super-prime):
    static u64 MAX_SEED_CT = 128;
    static mut_u32 seeds[MAX_SEED_CT] = { 3, 5, 11, 17, 31, 41, 59, 67, 83, 109, 127, 157, 179, 191, 211, 241, 277, 283, 331, 353, 367, 401, 431, 461, 509, 547, 563, 587, 599, 617, 709, 739, 773, 797, 859, 877, 919, 967, 991, 1031, 1063, 1087, 1153, 1171, 1201, 1217, 1297, 1409, 1433, 1447, 1471, 1499, 1523, 1597, 1621, 1669, 1723, 1741, 1787, 1823, 1847, 1913, 2027, 2063, 2081, 2099, 2221, 2269, 2341, 2351, 2381, 2417, 2477, 2549, 2609, 2647, 2683, 2719, 2749, 2803, 2897, 2909, 3001, 3019, 3067, 3109, 3169, 3229, 3259, 3299, 3319, 3407, 3469, 3517, 3559, 3593, 3637, 3733, 3761, 3911, 3943, 4027, 4091, 4133, 4153, 4217, 4273, 4339, 4397, 4421, 4463, 4517, 4549, 4567, 4663, 4759, 4787, 4801, 4877, 4933, 4943, 5021, 5059, 5107, 5189, 5281, 5381, 5441 };
    static mut_u32ptr SEEDS_BEGIN = seeds;
    static mut_u32ptr SEEDS_END = seeds + MAX_SEED_CT;

    static mut_u64 splitmix_state;

    class mut_SmRng
    {
    public:

        MAY_INLINE static void Init(void)
        {
            std::random_device rand_dev;
            std::mt19937 generator(rand_dev());
            std::uniform_int_distribution<int> distr(0, MAX_SEED_CT - 1);
            std::shuffle(SEEDS_BEGIN, SEEDS_END, generator);
            splitmix_state = seeds[distr(generator)];
        }
        MAY_INLINE static void Init(u32 input_seed, const std::mt19937& gen)
        {
            std::uniform_int_distribution<int> distr(0, MAX_SEED_CT);
            std::shuffle(SEEDS_BEGIN, SEEDS_END, gen);

            mut_u32 transformed_seed = input_seed ^ seeds[distr(gen)];
            transformed_seed ^= transformed_seed << 9;
            transformed_seed ^= transformed_seed >> 17;
            transformed_seed ^= transformed_seed << 6;
            splitmix_state = transformed_seed;
        }
        MAY_INLINE static void Init(u32 input_seed)
        {
            std::random_device rnd_dev;
            std::mt19937 rnd_gen(rnd_dev());
            Init(input_seed, rnd_gen);
        }

        INLINE static u64 Get(void)
        {
            splitmix_state += 0x9e3779b97f4a7c15;
            mut_u64 z = splitmix_state;
            z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
            z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
            return z ^ (z >> 31);
        }
        INLINE static u32 GetU32(void)
        {
            splitmix_state += 0x9e3779b97f4a7c15;
            mut_p64 z = splitmix_state;
            z.uint64 = (z.uint64 ^ (z.uint64 >> 30)) * 0xbf58476d1ce4e5b9;
            z.uint64 = (z.uint64 ^ (z.uint64 >> 27)) * 0x94d049bb133111eb;
            z.uint64 ^= z.uint64 >> 31;
            return z.High();
        }
    };
}