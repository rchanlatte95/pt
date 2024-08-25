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
        mut_CycleSpan cycle_duration;
        mut_TimeSpan time_duration;
    };

    class mut_PerfSample
    {
        bool active;
        mut_TimeStamp start_time;
        mut_TimeStamp end_time;
        mut_CountStamp start_cycles;
        mut_CountStamp end_cycles;

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
            end_cycles = CycleStamp(Counter::Now());
            end_time = TimeStamp(Timer::Now());
            active = false;
        }

        MAY_INLINE PerfSampleResult GetResult() const noexcept
        {
            if (active)
            {

            }
            else
            {

            }
        }
    };
}