#pragma once
#include "rac.hpp"

namespace rac::chronology
{
    class mut_CycleStamp;
    typedef mut_CycleStamp* mut_CycleStamp_ptr;
    typedef mut_CycleStamp& mut_CycleStamp_ref;
    typedef const mut_CycleStamp CycleStamp;
    typedef const mut_CycleStamp* CycleStamp_ptr;
    typedef const mut_CycleStamp& CycleStamp_ref;

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