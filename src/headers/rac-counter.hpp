#pragma once
#include "rac.hpp"

namespace rac::chronology
{
    enum FixedCounterType : u64
    {
        // This event counts the number of instructions that retire
        // execution.For instructions that consist of multiple uops,
        // this event counts the retirement of the last uop of the
        // instruction.The counter continues counting during
        // hardware interrupts, traps, and in - side interrupt handlers.
        //
        InstructionsRetired = (1 << 30),

        // The CPU_CLK_UNHALTED.THREAD event counts the
        // number of core cycles while the logical processor is not in a
        // halt state.
        //
        // If there is only one logical processor in a processor core,
        // CPU_CLK_UNHALTED.CORE counts the unhalted cycles of
        // the processor core.
        //
        // The core frequency may change from time to time due to
        // transitions associated with Enhanced Intel SpeedStep
        // Technology or TM2.For this reason this event may have a
        // changing ratio with regards to time.
        //
        UnhaltedCoreCycles = InstructionsRetired + (u64)1,

        // This event counts the number of reference cycles at the
        // TSC rate when the core is not in a halt state and not in a TM
        // stop - clock state.The core enters the halt state when it is
        // running the HLT instruction or the MWAIT instruction.This
        // event is not affected by core frequency changes(e.g., P
        // states) but counts at the same frequency as the time stamp
        // counter.This event can approximate elapsed time while the
        // core was not in a halt state and not in a TM stopclock state.
        //
        UnhaltedReferenceCycles = InstructionsRetired + (u64)2,

        // This event counts the number of available slots for an
        // unhalted logical processor.The event increments by
        // machine - width of the narrowest pipeline as employed by
        // the Top - down Microarchitecture Analysis method.The
        // count is distributed among unhalted logical processors
        // (hyper - threads) who share the same physical core.
        // Software can use this event as the denominator for the
        // top - level metrics of the Top - down Microarchitecture
        // Analysis method.
        //
        TopdownSlot = InstructionsRetired + (u64)3,
    };

    enum PerformanceEventType : u64
    {
        // This event counts core clock cycles when the clock signal on
        // a specific core is running (not halted). The counter does
        // not advance in the following conditions:
        //
        //      — An ACPI C - state other than C0 for normal operation.
        //      — HLT.
        //      — STPCLK# pin asserted.
        //      — Being throttled by TM1.
        //      — During the frequency switching phase of a performance
        //          state transition (see Chapter 15, “Power and Thermal Management”).
        //
        // The performance counter for this event counts across
        // performance state transitions using different core clock
        // frequencies.
        //
        UnhaltedCoreCycles = 0,


        //
        InstructionsRetired = (1 << 1),


        //
        UnhaltedReferenceCycles = (1 << 2),


        //
        LastLevelCacheReference = (1 << 3),


        //
        LastLevelCacheMisses = (1 << 4),


        //
        BranchInstructionRetired = (1 << 5),


        //
        BranchMissesRetired = (1 << 6),


        //
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