#pragma once
#include "rac.hpp"

namespace rac
{
    struct mut_p16;
    typedef mut_p16* mut_p16ptr;
    typedef mut_p16& mut_p16ref;
    typedef const mut_p16 p16;
    typedef const mut_p16* p16ptr;
    typedef const mut_p16& p16ref;

    struct mut_p32;
    typedef mut_p32* mut_p32ptr;
    typedef mut_p32& mut_p32ref;
    typedef const mut_p32 p32;
    typedef const mut_p32* p32ptr;
    typedef const mut_p32& p32ref;

    struct mut_p64;
    typedef mut_p64* mut_p64ptr;
    typedef mut_p64& mut_p64ref;
    typedef const mut_p64 p64;
    typedef const mut_p64* p64ptr;
    typedef const mut_p64& p64ref;

    struct mut_p128;
    typedef mut_p128* mut_p128ptr;
    typedef mut_p128& mut_p128ref;
    typedef const mut_p128 p128;
    typedef const mut_p128* p128ptr;
    typedef const mut_p128& p128ref;

    struct mut_p256;
    typedef mut_p256* mut_p256ptr;
    typedef mut_p256& mut_p256ref;
    typedef const mut_p256 p256;
    typedef const mut_p256* p256ptr;
    typedef const mut_p256& p256ref;

    struct mut_pf32;
    typedef mut_pf32* mut_pf32ptr;
    typedef mut_pf32& mut_pf32ref;
    typedef const mut_pf32 pf32;
    typedef const mut_pf32* pf32ptr;
    typedef const mut_pf32& pf32ref;

    struct mut_pf64;
    typedef mut_pf64* mut_pf64ptr;
    typedef mut_pf64& mut_pf64ref;
    typedef const mut_pf64 pf64;
    typedef const mut_pf64* pf64ptr;
    typedef const mut_pf64& pf64ref;

    struct mut_pf128;
    typedef mut_pf128* mut_pf128ptr;
    typedef mut_pf128& mut_pf128ref;
    typedef const mut_pf128 pf128;
    typedef const mut_pf128* pf128ptr;
    typedef const mut_pf128& pf128ref;

    struct mut_pf256;
    typedef mut_pf256* mut_pf256ptr;
    typedef mut_pf256& mut_pf256ref;
    typedef const mut_pf256 pf256;
    typedef const mut_pf256* pf256ptr;
    typedef const mut_pf256& pf256ref;

    static i32 HIGH = 0;
    static i32 LOW = 1;

    class mut_p16
    {
    public:
        union
        {
            mut_i8 bytes[sizeof(u16)];
            mut_i16 int16;

            mut_u8 ubytes[sizeof(u16)];
            mut_u16 uint16;
        };

        mut_p16() { int16 = 0; }
        mut_p16(i16 i) { int16 = i; }
        mut_p16(u16 u) { uint16 = u; }
        mut_p16(u8 b0, u8 b1)
        {
            bytes[0] = b0;
            bytes[1] = b1;
        }

        INLINE u8 High() const noexcept { return ubytes[HIGH]; }
        INLINE u8 Low() const noexcept { return ubytes[LOW]; }
    };

    class mut_p32
    {
    public:
        union
        {
            mut_i8 bytes[sizeof(u32)];
            mut_i16 int16[sizeof(u32) / sizeof(u16)];
            mut_i32 int32;

            mut_u8 ubytes[sizeof(u32)];
            mut_u16 uint16[sizeof(u32) / sizeof(u16)];
            mut_u32 uint32;

            mut_p16 packed16[sizeof(u32) / sizeof(p16)];
        };

        mut_p32() { uint32 = 0; }
        mut_p32(i32 i) { uint32 = i; }
        mut_p32(u32 u) { uint32 = u; }
        mut_p32(u16 high, u16 low)
        {
            uint16[HIGH] = high;
            uint16[LOW] = low;
        }
        mut_p32(p16 high, p16 low)
        {
            uint16[HIGH] = high.uint16;
            uint16[LOW] = low.uint16;
        }
        mut_p32(u8 b0, u8 b1, u8 b2, u8 b3)
        {
            bytes[0] = b0;
            bytes[1] = b1;
            bytes[2] = b2;
            bytes[3] = b3;
        }

        INLINE u16 High() const noexcept { return uint16[HIGH]; }
        INLINE u16 Low() const noexcept { return uint16[LOW]; }
        INLINE p16 PackedHigh() const noexcept { return packed16[HIGH]; }
        INLINE p16 PackedLow() const noexcept { return packed16[LOW]; }
    };

    class mut_p64
    {
    public:
        union
        {
            mut_i8 bytes[sizeof(u64)];
            mut_i16 int16[sizeof(u64) / sizeof(u16)];
            mut_i32 int32[sizeof(u64) / sizeof(u32)];
            mut_i64 int64;

            mut_u8 ubytes[sizeof(u64)];
            mut_u16 uint16[sizeof(u64) / sizeof(u16)];
            mut_u32 uint32[sizeof(u64) / sizeof(u32)];
            mut_u64 uint64;

            mut_p16 packed16[sizeof(u64) / sizeof(p16)];
            mut_p32 packed32[sizeof(u64) / sizeof(p32)];
        };

        mut_p64() { uint64 = 0; }
        mut_p64(i32 i) { uint64 = i; }
        mut_p64(u32 u) { uint64 = u; }
        mut_p64(u32 high, u32 low)
        {
            uint16[HIGH] = high;
            uint16[LOW] = low;
        }
        mut_p64(p32 high, p32 low)
        {
            uint32[HIGH] = high.uint32;
            uint32[LOW] = low.uint32;
        }
        mut_p64(u8 b0, u8 b1, u8 b2, u8 b3, u8 b4, u8 b5, u8 b6, u8 b7)
        {
            bytes[0] = b0;
            bytes[1] = b1;
            bytes[2] = b2;
            bytes[3] = b3;

            bytes[4] = b4;
            bytes[5] = b5;
            bytes[6] = b6;
            bytes[7] = b7;
        }

        INLINE u32 High() const noexcept { return uint32[HIGH]; }
        INLINE u32 Low() const noexcept { return uint32[LOW]; }
        INLINE p32 PackedHigh() const noexcept { return packed32[HIGH]; }
        INLINE p32 PackedLow() const noexcept { return packed32[LOW]; }
    };

    class mut_p128
    {
        union
        {
            mut_i8 bytes[sizeof(__m128i)];
            mut_i16 int16[sizeof(__m128i) / sizeof(u16)];
            mut_i32 int32[sizeof(__m128i) / sizeof(u32)];
            mut_i64 int64[sizeof(__m128i) / sizeof(u64)];

            mut_u8 ubytes[sizeof(__m128i)];
            mut_u16 uint16[sizeof(__m128i) / sizeof(u16)];
            mut_u32 uint32[sizeof(__m128i) / sizeof(u32)];
            mut_u64 uint64[sizeof(__m128i) / sizeof(u64)];

            __m128i int128;

            mut_p16 packed16[sizeof(__m128i) / sizeof(p16)];
            mut_p32 packed32[sizeof(__m128i) / sizeof(p32)];
            mut_p64 packed64[sizeof(__m128i) / sizeof(p64)];
        };

        INLINE u64 High() const noexcept { return uint64[HIGH]; }
        INLINE u64 Low() const noexcept { return uint64[LOW]; }
        INLINE p64 PackedHigh() const noexcept { return packed64[HIGH]; }
        INLINE p64 PackedLow() const noexcept { return packed64[LOW]; }
    };

    class mut_p256
    {
        union
        {
            mut_i8 bytes[sizeof(__m256i)];
            mut_i16 int16[sizeof(__m256i) / sizeof(u16)];
            mut_i32 int32[sizeof(__m256i) / sizeof(u32)];
            mut_i64 int64[sizeof(__m256i) / sizeof(u64)];

            mut_u8 ubytes[sizeof(__m256i)];
            mut_u16 uint16[sizeof(__m256i) / sizeof(u16)];
            mut_u32 uint32[sizeof(__m256i) / sizeof(u32)];
            mut_u64 uint64[sizeof(__m256i) / sizeof(u64)];

            __m128i int128[sizeof(__m256i) / sizeof(__m128i)];
            __m256i int256;

            mut_p16 packed16[sizeof(__m256i) / sizeof(p16)];
            mut_p32 packed32[sizeof(__m256i) / sizeof(p32)];
            mut_p64 packed64[sizeof(__m256i) / sizeof(p64)];
            mut_p128 packed128[sizeof(__m256i) / sizeof(p128)];
        };

        INLINE __m128i High() const noexcept { return int128[HIGH]; }
        INLINE __m128i Low() const noexcept { return int128[LOW]; }
        INLINE p128 PackedHigh() const noexcept { return packed128[HIGH]; }
        INLINE p128 PackedLow() const noexcept { return packed128[LOW]; }
    };


    // Packed Types that have floating point data
    class mut_pf32
    {
        union
        {
            mut_p32 packed;

            mut_f32 float32;
        };
    };

    class mut_pf64
    {
        union
        {
            mut_p32 packedf32[sizeof(p64) / sizeof(p32)];
            mut_p64 packed64;

            mut_f32 float32[sizeof(p64) / sizeof(f32)];
            mut_f64 float64;
        };

        INLINE f32 High() const noexcept { return float32[HIGH]; }
        INLINE f32 Low() const noexcept { return float32[LOW]; }
        INLINE p32 PackedHigh() const noexcept { return packedf32[HIGH]; }
        INLINE p32 PackedLow() const noexcept { return packedf32[LOW]; }
    };

    class mut_pf128
    {
        union
        {
            mut_p32 packed32[sizeof(__m128) / sizeof(p32)];
            mut_p64 packed64[sizeof(__m128) / sizeof(p64)];
            mut_p128 packed128;

            mut_pf32 packedf32[sizeof(__m128) / sizeof(pf32)];
            mut_pf64 packedf64[sizeof(__m128) / sizeof(pf64)];

            mut_f32 float32[sizeof(__m128) / sizeof(f32)];
            mut_f64 float64[sizeof(__m128) / sizeof(f64)];

            __m128 f128;
        };

        INLINE f64 High() const noexcept { return float64[HIGH]; }
        INLINE f64 Low() const noexcept { return float64[LOW]; }
        INLINE pf64 PackedHigh() const noexcept { return packedf64[HIGH]; }
        INLINE pf64 PackedLow() const noexcept { return packedf64[LOW]; }
    };

    class mut_pf256
    {
        union
        {
            mut_p32 packed32[sizeof(__m256) / sizeof(p32)];
            mut_p64 packed64[sizeof(__m256) / sizeof(p64)];
            mut_p128 packed128[sizeof(__m256) / sizeof(p128)];

            mut_pf32 packedf32[sizeof(__m256) / sizeof(pf32)];
            mut_pf64 packedf64[sizeof(__m256) / sizeof(pf64)];
            mut_pf128 packedf128[sizeof(__m256) / sizeof(pf128)];

            mut_f32 float32[sizeof(__m256) / sizeof(f32)];
            mut_f64 float64[sizeof(__m256) / sizeof(f64)];

            __m128 float128[sizeof(__m256) / sizeof(__m128)];
            __m256 float256;
        };

        INLINE __m128 High() const noexcept { return float128[HIGH]; }
        INLINE __m128 Low() const noexcept { return float128[LOW]; }
        INLINE pf128 PackedHigh() const noexcept { return packedf128[HIGH]; }
        INLINE pf128 PackedLow() const noexcept { return packedf128[LOW]; }
    };
}
