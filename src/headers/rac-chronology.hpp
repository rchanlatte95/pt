#pragma once
#include "rac.hpp"

namespace rac::chronology
{
    typedef std::chrono::steady_clock::time_point mut_TimeStamp;
    typedef std::chrono::steady_clock::time_point* mut_TimeStamp_ptr;
    typedef std::chrono::steady_clock::time_point& mut_TimeStamp_ref;
    typedef const std::chrono::steady_clock::time_point TimeStamp;
    typedef const std::chrono::steady_clock::time_point* TimeStamp_ptr;
    typedef const std::chrono::steady_clock::time_point& TimeStamp_ref;

    typedef std::chrono::steady_clock::duration mut_TimeSpan;
    typedef std::chrono::steady_clock::duration* mut_TimeSpan_ptr;
    typedef std::chrono::steady_clock::duration& mut_TimeSpan_ref;
    typedef const std::chrono::steady_clock::duration TimeSpan;
    typedef const std::chrono::steady_clock::duration* TimeSpan_ptr;
    typedef const std::chrono::steady_clock::duration& TimeSpan_ref;

    f64 NANOSECS_IN_SECS = 1e+9;
    f64 NANOSECS_TO_SECS = 1.0 / NANOSECS_IN_SECS;

    f64 MICROSECS_IN_SECS = 1e+6;
    f64 MICROSECS_TO_SECS = 1.0 / MICROSECS_IN_SECS;

    f64 MILISECS_IN_SECS = 1e+3;
    f64 MILISECS_TO_SECS = 1.0 / MILISECS_IN_SECS;

    class Timer
    {
    public:

        //  rdpmc_actual_cycles uses a "fixed-function" performance counter to return the count of actual CPU core cycles
        //  executed by the current core.  Core cycles are not accumulated while the processor is in the "HALT" state,
        //  which is used when the operating system has no task(s) to run on a processor core.
        static INLINE u64 Cycles()
        {
            u64 ctr_flag = (1ull << 30ull) + 1ull;
            return __readpmc(ctr_flag);
        }

        static INLINE u64 RefCycles()
        {
            return (i64)__rdtsc();
        }

        static INLINE TimeStamp Now()
        {
            return std::chrono::high_resolution_clock::now();
        }
        static INLINE f64 DurationInMilisecs(TimeStamp_ref start)
        {
            TimeSpan diff = Timer::Now() - start;
            return (f64)std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
        }
        static INLINE f64 DurationInSecs(TimeStamp_ref start)
        {
            return DurationInMilisecs(start) * MILISECS_TO_SECS;
        }
    };
}