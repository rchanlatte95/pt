#pragma once
#include "rac.hpp"

namespace rac::chronology
{
    enum FixedCounterType : u64
    {
        // Event Mask Mnemonic -> INST_RETIRED.ANY
        // Address -> 309H
        //
        // This event counts the number of instructions that retire
        // execution.For instructions that consist of multiple uops,
        // this event counts the retirement of the last uop of the
        // instruction.The counter continues counting during
        // hardware interrupts, traps, and in - side interrupt
        // handlers.
        //
        InstructionsRetired = (1 << 30),

        // Event Mask Mnemonic -> CPU_CLK_UNHALTED.THREAD/CORE
        // Address -> 30AH
        //
        // The CPU_CLK_UNHALTED.THREAD event counts the
        // number of core cycles while the logical processor is not in
        // a halt state.
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

        // Event Mask Mnemonic -> CPU_CLK_UNHALTED.REF_TSC
        // Address -> 30BH
        //
        // This event counts the number of reference cycles at the
        // TSC rate when the core is not in a halt state and not in a
        // TM stop - clock state.The core enters the halt state when it
        // is running the HLT instruction or the MWAIT instruction.
        //
        // This event is not affected by core frequency changes(e.g.,
        // P-states) but counts at the same frequency as the timestamp
        // counter.
        //
        // This event can approximate elapsed time while the
        // core was not in a halt state and not in a TM stopclock
        // state.
        //
        UnhaltedReferenceCycles = InstructionsRetired + (u64)2,

        // Event Mask Mnemonic -> TOPDOWN.SLOTS
        // Address -> 30CH
        //
        // This event counts the number of available slots for an
        // unhalted logical processor. The event increments by
        // machine-width of the narrowest pipeline as employed by
        // the Top-down Microarchitecture Analysis method. The
        // count is distributed among unhalted logical processors
        // (hyper-threads) who share the same physical core.
        // Software can use this event as the denominator for the
        // top-level metrics of the Top-down Microarchitecture Analysis
        // method.
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
        //          state transition (see Chapter 15, “Power and
        //          Thermal Management”).
        //
        // The performance counter for this event counts across
        // performance state transitions using different core clock
        // frequencies.
        //
        UnhaltedCoreCycles = 0,

        // This event counts the number of instructions at retirement.
        // For instructions that consist of multiple micro-ops, this
        // event counts the retirement of the last micro-op of the
        // instruction. An instruction with a REP prefix counts as one
        // instruction (not per iteration). Faults before the retirement
        // of the last micro-op of a multi-ops instruction are not
        // counted.
        //
        // This event does not increment under VM - exit conditions.
        // Counters continue counting during hardware interrupts,
        // traps, and inside interrupt handlers.
        //
        InstructionsRetired = (1 << 1),

        // This event counts reference clock cycles at a fixed
        // frequency while the clock signal on the core is running. The
        // event counts at a fixed frequency, irrespective of core
        // frequency changes due to performance state transitions.
        // Processors may implement this behavior differently. Current
        // implementations use the core crystal clock, TSC or the bus
        // clock.
        //
        //      *** Because the rate may differ between implementations,
        //          software should calibrate it to a time source with
        //          known frequency.
        //
        UnhaltedReferenceCycles = (1 << 2),

        // This event counts requests originating from the core that
        // reference a cache line in the last level on-die cache. The
        // event count includes speculation and cache line fills due to
        // the first-level cache hardware prefetcher, but may exclude
        // cacheline fills due to other hardware-prefetchers.
        //
        //      *** Because cache hierarchy, cache sizes and other
        //          implementation-specific characteristics; value
        //          comparison to estimate performance differences is
        //          not recommended.
        //
        LastLevelCacheReference = (1 << 3),

        // This event counts each cache miss condition for references
        // to the last level on-die cache. The event count may include
        // speculation and cache line fills due to the first-level
        // cache hardware prefetcher, but may exclude cacheline fills
        // due to other hardware-prefetchers.
        //
        //      *** Because cache hierarchy, cache sizes and other
        //          implementation-specific characteristics; value
        //          comparison to estimate performance differences is
        //          not recommended.
        //
        LastLevelCacheMisses = (1 << 4),

        // This event counts branch instructions at retirement. It
        // counts the retirement of the last micro-op of a branch
        // instruction.
        //
        BranchInstructionRetired = (1 << 5),

        // This event counts mispredicted branch instructions at
        // retirement. It counts the retirement of the last micro-op of
        // a branch instruction in the architectural path of execution
        // and experienced misprediction in the branch prediction hardware.
        //
        //      *** Branch prediction hardware is
        //          implementation-specific across microarchitectures;
        //          value comparison to estimate performance
        //          differences is not recommended.
        //
        BranchMissesRetired = (1 << 6),

        // This event counts the total number of available slots for an
        // unhalted logical processor. The event increments by
        // machine-width of the narrowest pipeline as employed by the
        // Top-down Microarchitecture Analysis method. The count is
        // distributed among unhalted logical processors (hyper-threads)
        // who share the same physical core, in processors that support
        // Intel Hyper-Threading Technology.
        //
        // Software can use this event as the denominator for the
        // top-level metrics of the Top-down Microarchitecture
        // Analysis method.
        //
        TopdownSlots = (1 << 7)
    };

    class mut_CountStamp;
    typedef mut_CountStamp* mut_CountStamp_ptr;
    typedef mut_CountStamp& mut_CountStamp_ref;
    typedef const mut_CountStamp CountStamp;
    typedef const mut_CountStamp* CountStamp_ptr;
    typedef const mut_CountStamp& CountStamp_ref;

    class mut_CountSpan;
    typedef mut_CountSpan* mut_CountSpan_ptr;
    typedef mut_CountSpan& mut_CountSpan_ref;
    typedef const mut_CountSpan CountSpan;
    typedef const mut_CountSpan* CountSpan_ptr;
    typedef const mut_CountSpan& CountSpan_ref;

    class mut_CountStamp
    {
    public:
        mut_u64 Cycles;

        mut_CountStamp() { Cycles = 0; }
        mut_CountStamp(u64 c) { Cycles = c; }
    };

    class Counter
    {
    public:

        static INLINE CountStamp Now() { return CountStamp(__rdtsc()); }
        static INLINE CountSpan Duration(CountStamp_ref start)
        {
            return CountSpan(__rdtsc() - start.Cycles);
        }
    };

    class mut_CountSpan
    {
    public:
        mut_u64 cycle_duration;

        mut_CountSpan() { cycle_duration = 0; }
        mut_CountSpan(u64 c) { cycle_duration = c; }
    };
}