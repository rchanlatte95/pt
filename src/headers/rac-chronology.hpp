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

    class Timer
    {
    public:
        static INLINE TimeStamp Now()
        {
            return std::chrono::high_resolution_clock::now();
        }
        static INLINE f64 DurationInMS(TimeStamp_ref start)
        {
            TimeStamp now = Timer::Now();
            const std::chrono::steady_clock::duration diff = now - start;
            return (f64)std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
        }
        static INLINE f64 DurationInSecs(TimeStamp_ref start)
        {
            return DurationInMS(start) * MS_TO_SECS;
        }
    };
}