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

        static INLINE TimeStamp Now()
        {
            return std::chrono::high_resolution_clock::now();
        }
        static INLINE f64 DurationNanoseconds(TimeSpan_ref span)
        {
            return (f64)std::chrono::duration_cast<std::chrono::nanoseconds>(span).count();
        }
        static INLINE f64 DurationMicroseconds(TimeSpan_ref span)
        {
            return (f64)std::chrono::duration_cast<std::chrono::microseconds>(span).count();
        }
        static INLINE f64 Duration(TimeSpan_ref span)
        {
            return (f64)std::chrono::duration_cast<std::chrono::milliseconds>(span).count();
        }
        static INLINE f64 DurationSeconds(TimeSpan_ref span)
        {
            return Duration(span) * MILISECS_TO_SECS;
        }

        static INLINE f64 DurationNanoseconds(TimeStamp_ref start)
        {
            TimeSpan diff = Timer::Now() - start;
            return (f64)std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count();
        }
        static INLINE f64 DurationMicroseconds(TimeStamp_ref start)
        {
            TimeSpan diff = Timer::Now() - start;
            return (f64)std::chrono::duration_cast<std::chrono::microseconds>(diff).count();
        }
        static INLINE f64 Duration(TimeStamp_ref start)
        {
            TimeSpan diff = Timer::Now() - start;
            return (f64)std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
        }
        static INLINE f64 DurationSeconds(TimeStamp_ref start)
        {
            return Duration(start) * MILISECS_TO_SECS;
        }
    };
}