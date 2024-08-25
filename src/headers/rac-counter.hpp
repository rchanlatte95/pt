#pragma once
#include "rac.hpp"

namespace rac::chronology
{
    enum CounterType : u64
    {
        UnhaltedCoreCycles = 0,
        InstructionsRetired = (1 << 1),
        UnhaltedReferenceCycles = (1 << 2),
        LastLevelCacheReference = (1 << 3),
        LastLevelCacheMisses = (1 << 4),
        BranchInstructionRetired = (1 << 5),
        BranchMissesRetired = (1 << 6),
        TopdownSlots = (1 << 7)
    };

    class mut_CountStamp;
    typedef mut_CountStamp* mut_CountStamp_ptr;
    typedef mut_CountStamp& mut_CountStamp_ref;
    typedef const mut_CountStamp CountStamp;
    typedef const mut_CountStamp* CountStamp_ptr;
    typedef const mut_CountStamp& CountStamp_ref;

    class Counter
    {
    public:
        // rdpmc_actual_cycles uses a "fixed-function" performance counter to
        // return the count of actual CPU core cycles executed by the current
        // core. Core cycles are not accumulated while the processor is in the
        // "HALT" state, which is used when the operating system has no task(s)
        //  to run on a processor core.
        static INLINE u64 Cycles()
        {
            u64 ctr_flag = (1ull << 30ull) + 1ull;
            return __readpmc(ctr_flag);
        }

        static INLINE u64 RefCycles()
        {
            return (i64)__rdtsc();
        }
    };
}