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
    };

    class mut_PerfSample
    {
        bool active;
        mut_TimeStamp start_time;
        mut_TimeStamp end_time;
        mut_CycleStamp start_cycles;
        mut_CycleStamp end_cycles;

    public:

        INLINE void Start() noexcept
        {
            if (active) { return; }

            active = true;
            start_time = TimeStamp(Timer::Now());
            start_cycles = CycleStamp(Counter::Now());
        }
        INLINE void End() noexcept
        {
            if (!active) { return; }

            end_cycles = CycleStamp(Counter::Now());
            end_time = TimeStamp(Timer::Now());
            active = false;
        }

        MAY_INLINE PerfSampleResult GetResult() const noexcept
        {
            if (active)
            {
                return PerfSampleResult(start_time, Timer::Now(), start_cycles, Counter::Now());
            }
            return PerfSampleResult(start_time, end_time, start_cycles, end_cycles);
        }
    };
}