#pragma once
#include "rac-counter.hpp"
#include "rac-timer.hpp"

namespace rac::chronology
{
    class mut_PerfSample;
    typedef mut_PerfSample* mut_PerfSample_ptr;
    typedef mut_PerfSample& mut_PerfSample_ref;
    typedef const mut_PerfSample PerfSample;
    typedef const mut_PerfSample* PerfSample_ptr;
    typedef const mut_PerfSample& PerfSample_ref;

    class mut_PerfSampleResult;
    typedef mut_PerfSampleResult* mut_PerfSampleResult_ptr;
    typedef mut_PerfSampleResult& mut_PerfSampleResult_ref;
    typedef const mut_PerfSampleResult PerfSampleResult;
    typedef const mut_PerfSampleResult* PerfSampleResult_ptr;
    typedef const mut_PerfSampleResult& PerfSampleResult_ref;

    class mut_PerfSampleResult
    {
    public:
        mut_CycleSpan cycles_elapsed;
        mut_TimeSpan time_elapsed;

        mut_PerfSampleResult()
        {
            cycles_elapsed = CycleSpan((u64)0);
            time_elapsed = TimeSpan();
        }
        mut_PerfSampleResult(TimeStamp_ref start_time, TimeStamp_ref end_time, CycleStamp start_cycle, CycleStamp end_cycle)
        {
            cycles_elapsed = end_cycle - start_cycle;
            time_elapsed = end_time - start_time;
        }

        INLINE u64 Cycles() const noexcept
        {
            return cycles_elapsed.Cycles();
        }
        INLINE f64 Kilocycles() const noexcept
        {
            return cycles_elapsed.Kilocycles();
        }
        INLINE f64 Milicycles() const noexcept
        {
            return cycles_elapsed.Milicycles();
        }
        INLINE f64 Gigacycles() const noexcept
        {
            return cycles_elapsed.Gigacycles();
        }

        INLINE f64 Seconds() const noexcept
        {
            return Timer::DurationSeconds(time_elapsed);
        }
        INLINE f64 Miliseconds() const noexcept
        {
            return Timer::Duration(time_elapsed);
        }
        INLINE f64 Microseconds() const noexcept
        {
            return Timer::DurationMicroseconds(time_elapsed);
        }
        INLINE f64 Nanoseconds() const noexcept
        {
            return Timer::DurationNanoseconds(time_elapsed);
        }
    };

    class mut_PerfSample
    {
        bool active;
        mut_TimeStamp start_time;
        mut_TimeStamp end_time;
        mut_CycleStamp start_cycles;
        mut_CycleStamp end_cycles;
        mut_PerfSampleResult result;

    public:
        mut_PerfSample()
        {
            active = false;
            start_time = TimeStamp();
            end_time = TimeStamp();
            start_cycles = CycleStamp();
            end_cycles = CycleStamp();
            result = PerfSampleResult();
        }

        MAY_INLINE PerfSampleResult GetResult() const noexcept
        {
            if (active)
            {
                return PerfSampleResult(start_time, Timer::Now(), start_cycles, Counter::Now());
            }
            return result;
        }

        INLINE void Start() noexcept
        {
            if (active) { return; }

            active = true;
            start_time = TimeStamp(Timer::Now());
            start_cycles = CycleStamp(Counter::Now());
        }
        INLINE PerfSampleResult End() noexcept
        {
            if (!active) { return PerfSampleResult(); }

            end_cycles = CycleStamp(Counter::Now());
            end_time = TimeStamp(Timer::Now());
            active = false;
            result = PerfSampleResult(start_time, end_time, start_cycles, end_cycles);
            return result;
        }
    };
}