#pragma once
#include "rac.hpp"

namespace rac
{
    class mut_p16;
    typedef mut_p16* mut_p16ptr;
    typedef mut_p16& mut_p16ref;
    typedef const mut_p16 p16;
    typedef const mut_p16* p16ptr;
    typedef const mut_p16& p16ref;

    class mut_p32;
    typedef mut_p32* mut_p32ptr;
    typedef mut_p32& mut_p32ref;
    typedef const mut_p32 p32;
    typedef const mut_p32* p32ptr;
    typedef const mut_p32& p32ref;

    class mut_p64;
    typedef mut_p64* mut_p64ptr;
    typedef mut_p64& mut_p64ref;
    typedef const mut_p64 p64;
    typedef const mut_p64* p64ptr;
    typedef const mut_p64& p64ref;

    class mut_p128;
    typedef mut_p128* mut_p128ptr;
    typedef mut_p128& mut_p128ref;
    typedef const mut_p128 p128;
    typedef const mut_p128* p128ptr;
    typedef const mut_p128& p128ref;

    class mut_p256;
    typedef mut_p256* mut_p256ptr;
    typedef mut_p256& mut_p256ref;
    typedef const mut_p256 p256;
    typedef const mut_p256* p256ptr;
    typedef const mut_p256& p256ref;

    class mut_pf32;
    typedef mut_pf32* mut_pf32ptr;
    typedef mut_pf32& mut_pf32ref;
    typedef const mut_pf32 pf32;
    typedef const mut_pf32* pf32ptr;
    typedef const mut_pf32& pf32ref;

    class mut_pf64;
    typedef mut_pf64* mut_pf64ptr;
    typedef mut_pf64& mut_pf64ref;
    typedef const mut_pf64 pf64;
    typedef const mut_pf64* pf64ptr;
    typedef const mut_pf64& pf64ref;

    class mut_pf128;
    typedef mut_pf128* mut_pf128ptr;
    typedef mut_pf128& mut_pf128ref;
    typedef const mut_pf128 pf128;
    typedef const mut_pf128* pf128ptr;
    typedef const mut_pf128& pf128ref;

    class mut_pf256;
    typedef mut_pf256* mut_pf256ptr;
    typedef mut_pf256& mut_pf256ref;
    typedef const mut_pf256 pf256;
    typedef const mut_pf256* pf256ptr;
    typedef const mut_pf256& pf256ref;

    static i32 LOW = 0;
    static i32 HIGH = 1;

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
        mut_p16(u16 u) { uint16 = u; }
        mut_p16(u8 b0, u8 b1)
        {
            bytes[LOW] = b0;
            bytes[HIGH] = b1;
        }

        INLINE mut_p16 operator-() const noexcept { return mut_p16(-int16); }
        INLINE const mut_p16& operator+=(const mut_p16 p) noexcept
        {
            uint16 += p.uint16;
        }
        INLINE const mut_p16& operator-=(const mut_p16 p) noexcept
        {
            uint16 -= p.uint16;
        }
        INLINE const mut_p16& operator*=(const mut_p16 p) noexcept
        {
            uint16 *= p.uint16;
        }
        INLINE const mut_p16& operator/=(const mut_p16 p) noexcept
        {
            uint16 /= p.uint16;
        }
        INLINE const mut_p16& operator+=(u16 u) noexcept
        {
            uint16 += u;
        }
        INLINE const mut_p16& operator-=(u16 u) noexcept
        {
            uint16 -= u;
        }
        INLINE const mut_p16& operator*=(u16 u) noexcept
        {
            uint16 *= u;
        }
        INLINE const mut_p16& operator/=(u16 u) noexcept
        {
            uint16 /= u;
        }

        INLINE u8 High() const noexcept { return ubytes[HIGH]; }
        INLINE u8 Low() const noexcept { return ubytes[LOW]; }

        INLINE p16 RotateLeft(i32 rotate_by)
        {
            return (uint16 << rotate_by) | (uint16 >> (16 - rotate_by));
        }
    };

    INLINE p16 operator+(p16ref lhs, u16ref rhs)
    {
        return p16(lhs.uint16 + rhs);
    }
    INLINE p16 operator-(p16ref lhs, u16ref rhs)
    {
        return p16(lhs.uint16 - rhs);
    }
    INLINE p16 operator*(p16ref lhs, u16ref rhs)
    {
        return p16(lhs.uint16 * rhs);
    }
    INLINE p16 operator/(p16ref lhs, u16ref rhs)
    {
        return p16(lhs.uint16 / rhs);
    }

    INLINE p16 operator+(u16ref lhs, p16ref rhs)
    {
        return p16(lhs + rhs.uint16);
    }
    INLINE p16 operator-(u16ref lhs, p16ref rhs)
    {
        return p16(lhs - rhs.uint16);
    }
    INLINE p16 operator*(u16ref lhs, p16ref rhs)
    {
        return p16(lhs * rhs.uint16);
    }
    INLINE p16 operator/(u16ref lhs, p16ref rhs)
    {
        return p16(lhs / rhs.uint16);
    }

    INLINE p16 operator+(p16ref lhs, p16ref rhs)
    {
        return lhs + rhs.uint16;
    }
    INLINE p16 operator-(p16ref lhs, p16ref rhs)
    {
        return lhs - rhs.uint16;
    }
    INLINE p16 operator*(p16ref lhs, p16ref rhs)
    {
        return lhs * rhs.uint16;
    }
    INLINE p16 operator/(p16ref lhs, p16ref rhs)
    {
        return lhs / rhs.uint16;
    }

    INLINE bool operator==(p16ref lhs, u16ref rhs) noexcept
    {
        return lhs.uint16 == rhs;
    }
    INLINE bool operator!=(p16ref lhs, u16ref rhs) noexcept
    {
        return !(lhs == rhs);
    }
    INLINE bool operator<(p16ref lhs, u16ref rhs) noexcept
    {
        return lhs.uint16 < rhs;
    }
    INLINE bool operator>(p16ref lhs, u16ref rhs) noexcept
    {
        return rhs < lhs.uint16;
    }
    INLINE bool operator<=(p16ref lhs, u16ref rhs) noexcept
    {
        return !(lhs > rhs);
    }
    INLINE bool operator>=(p16ref lhs, u16ref rhs) noexcept
    {
        return !(lhs < rhs);
    }

    INLINE bool operator==(u16ref lhs, p16ref rhs) noexcept
    {
        return lhs == rhs.uint16;
    }
    INLINE bool operator!=(u16ref lhs, p16ref rhs) noexcept
    {
        return !(lhs == rhs);
    }
    INLINE bool operator<(u16ref lhs, p16ref rhs) noexcept
    {
        return lhs < rhs.uint16;
    }
    INLINE bool operator>(u16ref lhs, p16ref rhs) noexcept
    {
        return rhs.uint16 < lhs;
    }
    INLINE bool operator<=(u16ref lhs, p16ref rhs) noexcept
    {
        return !(lhs > rhs);
    }
    INLINE bool operator>=(u16ref lhs, p16ref rhs) noexcept
    {
        return !(lhs < rhs);
    }

    INLINE bool operator==(p16ref lhs, p16ref rhs) noexcept
    {
        return lhs.uint16 == rhs.uint16;
    }
    INLINE bool operator!=(p16ref lhs, p16ref rhs) noexcept
    {
        return !(lhs.uint16 == rhs.uint16);
    }
    INLINE bool operator<(p16ref lhs, p16ref rhs) noexcept
    {
        return lhs.uint16 < rhs.uint16;
    }
    INLINE bool operator>(p16ref lhs, p16ref rhs) noexcept
    {
        return rhs.uint16 < lhs.uint16;
    }
    INLINE bool operator<=(p16ref lhs, p16ref rhs) noexcept
    {
        return !(lhs > rhs);
    }
    INLINE bool operator>=(p16ref lhs, p16ref rhs) noexcept
    {
        return !(lhs < rhs);
    }

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

        INLINE mut_p32 operator-() const noexcept
        {
            return mut_p32(-int32);
        }
        INLINE const mut_p32& operator+=(const mut_p32 p) noexcept
        {
            uint32 += p.uint32;
        }
        INLINE const mut_p32& operator-=(const mut_p32 p) noexcept
        {
            uint32 -= p.uint32;
        }
        INLINE const mut_p32& operator*=(const mut_p32 p) noexcept
        {
            uint32 *= p.uint32;
        }
        INLINE const mut_p32& operator/=(const mut_p32 p) noexcept
        {
            uint32 /= p.uint32;
        }
        INLINE const mut_p32& operator+=(u32 u) noexcept
        {
            uint32 += u;
        }
        INLINE const mut_p32& operator-=(u32 u) noexcept
        {
            uint32 -= u;
        }
        INLINE const mut_p32& operator*=(u32 u) noexcept
        {
            uint32 *= u;
        }
        INLINE const mut_p32& operator/=(u32 u) noexcept
        {
            uint32 /= u;
        }

        INLINE u16 High() const noexcept { return uint16[HIGH]; }
        INLINE u16 Low() const noexcept { return uint16[LOW]; }
        INLINE u16 HighWord() const noexcept { return High(); }
        INLINE u16 LowWord() const noexcept { return Low(); }
        INLINE p16 PackedHigh() const noexcept { return packed16[HIGH]; }
        INLINE p16 PackedLow() const noexcept { return packed16[LOW]; }

        INLINE p32 RotateLeft(i32 rotate_by)
        {
            return (uint32 << rotate_by) | (uint32 >> (32 - rotate_by));
        }
    };

    INLINE p32 operator+(p32ref lhs, u32ref rhs)
    {
        return p32(lhs.uint32 + rhs);
    }
    INLINE p32 operator-(p32ref lhs, u32ref rhs)
    {
        return p32(lhs.uint32 - rhs);
    }
    INLINE p32 operator*(p32ref lhs, u32ref rhs)
    {
        return p32(lhs.uint32 * rhs);
    }
    INLINE p32 operator/(p32ref lhs, u32ref rhs)
    {
        return p32(lhs.uint32 / rhs);
    }

    INLINE p32 operator+(u32ref lhs, p32ref rhs)
    {
        return p32(lhs + rhs.uint32);
    }
    INLINE p32 operator-(u32ref lhs, p32ref rhs)
    {
        return p32(lhs - rhs.uint32);
    }
    INLINE p32 operator*(u32ref lhs, p32ref rhs)
    {
        return p32(lhs * rhs.uint32);
    }
    INLINE p32 operator/(u32ref lhs, p32ref rhs)
    {
        return p32(lhs / rhs.uint32);
    }

    INLINE p32 operator+(p32ref lhs, p32ref rhs)
    {
        return lhs + rhs.uint32;
    }
    INLINE p32 operator-(p32ref lhs, p32ref rhs)
    {
        return lhs - rhs.uint32;
    }
    INLINE p32 operator*(p32ref lhs, p32ref rhs)
    {
        return lhs * rhs.uint32;
    }
    INLINE p32 operator/(p32ref lhs, p32ref rhs)
    {
        return lhs / rhs.uint32;
    }

    INLINE bool operator==(p32ref lhs, u32ref rhs) noexcept
    {
        return lhs.uint32 == rhs;
    }
    INLINE bool operator!=(p32ref lhs, u32ref rhs) noexcept
    {
        return !(lhs == rhs);
    }
    INLINE bool operator<(p32ref lhs, u32ref rhs) noexcept
    {
        return lhs.uint32 < rhs;
    }
    INLINE bool operator>(p32ref lhs, u32ref rhs) noexcept
    {
        return rhs < lhs.uint32;
    }
    INLINE bool operator<=(p32ref lhs, u32ref rhs) noexcept
    {
        return !(lhs > rhs);
    }
    INLINE bool operator>=(p32ref lhs, u32ref rhs) noexcept
    {
        return !(lhs < rhs);
    }

    INLINE bool operator==(u32ref lhs, p32ref rhs) noexcept
    {
        return lhs == rhs.uint32;
    }
    INLINE bool operator!=(u32ref lhs, p32ref rhs) noexcept
    {
        return !(lhs == rhs);
    }
    INLINE bool operator<(u32ref lhs, p32ref rhs) noexcept
    {
        return lhs < rhs.uint32;
    }
    INLINE bool operator>(u32ref lhs, p32ref rhs) noexcept
    {
        return rhs.uint32 < lhs;
    }
    INLINE bool operator<=(u32ref lhs, p32ref rhs) noexcept
    {
        return !(lhs > rhs);
    }
    INLINE bool operator>=(u32ref lhs, p32ref rhs) noexcept
    {
        return !(lhs < rhs);
    }

    INLINE bool operator==(p32ref lhs, p32ref rhs) noexcept
    {
        return lhs.uint32 == rhs.uint32;
    }
    INLINE bool operator!=(p32ref lhs, p32ref rhs) noexcept
    {
        return !(lhs.uint32 == rhs.uint32);
    }
    INLINE bool operator<(p32ref lhs, p32ref rhs) noexcept
    {
        return lhs.uint32 < rhs.uint32;
    }
    INLINE bool operator>(p32ref lhs, p32ref rhs) noexcept
    {
        return rhs.uint32 < lhs.uint32;
    }
    INLINE bool operator<=(p32ref lhs, p32ref rhs) noexcept
    {
        return !(lhs > rhs);
    }
    INLINE bool operator>=(p32ref lhs, p32ref rhs) noexcept
    {
        return !(lhs < rhs);
    }

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
        mut_p64(i64 i) { int64 = i; }

        mut_p64(u32 high, u32 low)
        {
            uint32[HIGH] = high;
            uint32[LOW] = low;
        }
        mut_p64(p32 high, p32 low)
        {
            uint32[HIGH] = high.uint32;
            uint32[LOW] = low.uint32;
        }

        mut_p64(u16 uint16_0, u16 uint16_1, u16 uint16_2, u16 uint16_3)
        {
            uint16[0] = uint16_0;
            uint16[1] = uint16_1;
            uint16[2] = uint16_2;
            uint16[3] = uint16_3;
        }
        mut_p64(i16 int16_0, i16 int16_1, i16 int16_2, i16 int16_3)
        {
            int16[0] = int16_0;
            int16[1] = int16_1;
            int16[2] = int16_2;
            int16[3] = int16_3;
        }
        mut_p64(p16 p16_0, p16 p16_1, p16 p16_2, p16 p16_3)
        {
            packed16[0] = p16_0;
            packed16[1] = p16_1;
            packed16[2] = p16_2;
            packed16[3] = p16_3;
        }

        mut_p64(u8 b0, u8 b1, u8 b2, u8 b3, u8 b4, u8 b5, u8 b6, u8 b7)
        {
            ubytes[0] = b0;
            ubytes[1] = b1;
            ubytes[2] = b2;
            ubytes[3] = b3;

            ubytes[4] = b4;
            ubytes[5] = b5;
            ubytes[6] = b6;
            ubytes[7] = b7;
        }
        mut_p64(i8 b0, i8 b1, i8 b2, i8 b3, i8 b4, i8 b5, i8 b6, i8 b7)
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

        INLINE mut_p64 operator-() const noexcept
        {
            return mut_p64(-int64);
        }
        INLINE const mut_p64& operator+=(const mut_p64 p) noexcept
        {
            uint64 += p.uint64;
        }
        INLINE const mut_p64& operator-=(const mut_p64 p) noexcept
        {
            uint64 -= p.uint64;
        }
        INLINE const mut_p64& operator*=(const mut_p64 p) noexcept
        {
            uint64 *= p.uint64;
        }
        INLINE const mut_p64& operator/=(const mut_p64 p) noexcept
        {
            uint64 /= p.uint64;
        }
        INLINE const mut_p64& operator+=(u64 u) noexcept
        {
            uint64 += u;
        }
        INLINE const mut_p64& operator-=(u64 u) noexcept
        {
            uint64 -= u;
        }
        INLINE const mut_p64& operator*=(u64 u) noexcept
        {
            uint64 *= u;
        }
        INLINE const mut_p64& operator/=(u64 u) noexcept
        {
            uint64 /= u;
        }

        INLINE u32 High() const noexcept { return uint32[HIGH]; }
        INLINE u32 Low() const noexcept { return uint32[LOW]; }
        INLINE u32 HighDword() const noexcept { return High(); }
        INLINE u32 LowDword() const noexcept { return Low(); }
        INLINE p32 PackedHigh() const noexcept { return packed32[HIGH]; }
        INLINE p32 PackedLow() const noexcept { return packed32[LOW]; }

        INLINE p64 RotateLeft(i32 rotate_by)
        {
            return (uint64 << rotate_by) | (uint64 >> (64 - rotate_by));
        }
    };

    INLINE p64 operator+(p64ref lhs, u64ref rhs)
    {
        return p64(lhs.uint64 + rhs);
    }
    INLINE p64 operator-(p64ref lhs, u64ref rhs)
    {
        return p64(lhs.uint64 - rhs);
    }
    INLINE p64 operator*(p64ref lhs, u64ref rhs)
    {
        return p64(lhs.uint64 * rhs);
    }
    INLINE p64 operator/(p64ref lhs, u64ref rhs)
    {
        return p64(lhs.uint64 / rhs);
    }

    INLINE p64 operator+(u64ref lhs, p64ref rhs)
    {
        return p64(lhs + rhs.uint64);
    }
    INLINE p64 operator-(u64ref lhs, p64ref rhs)
    {
        return p64(lhs - rhs.uint64);
    }
    INLINE p64 operator*(u64ref lhs, p64ref rhs)
    {
        return p64(lhs * rhs.uint64);
    }
    INLINE p64 operator/(u64ref lhs, p64ref rhs)
    {
        return p64(lhs / rhs.uint64);
    }

    INLINE p64 operator+(p64ref lhs, p64ref rhs)
    {
        return lhs + rhs.uint64;
    }
    INLINE p64 operator-(p64ref lhs, p64ref rhs)
    {
        return lhs - rhs.uint64;
    }
    INLINE p64 operator*(p64ref lhs, p64ref rhs)
    {
        return lhs * rhs.uint64;
    }
    INLINE p64 operator/(p64ref lhs, p64ref rhs)
    {
        return lhs / rhs.uint64;
    }

    INLINE bool operator==(p64ref lhs, u64ref rhs) noexcept
    {
        return lhs.uint64 == rhs;
    }
    INLINE bool operator!=(p64ref lhs, u64ref rhs) noexcept
    {
        return !(lhs == rhs);
    }
    INLINE bool operator<(p64ref lhs, u64ref rhs) noexcept
    {
        return lhs.uint64 < rhs;
    }
    INLINE bool operator>(p64ref lhs, u64ref rhs) noexcept
    {
        return rhs < lhs.uint64;
    }
    INLINE bool operator<=(p64ref lhs, u64ref rhs) noexcept
    {
        return !(lhs > rhs);
    }
    INLINE bool operator>=(p64ref lhs, u64ref rhs) noexcept
    {
        return !(lhs < rhs);
    }

    INLINE bool operator==(u64ref lhs, p64ref rhs) noexcept
    {
        return lhs == rhs.uint64;
    }
    INLINE bool operator!=(u64ref lhs, p64ref rhs) noexcept
    {
        return !(lhs == rhs);
    }
    INLINE bool operator<(u64ref lhs, p64ref rhs) noexcept
    {
        return lhs < rhs.uint64;
    }
    INLINE bool operator>(u64ref lhs, p64ref rhs) noexcept
    {
        return rhs.uint64 < lhs;
    }
    INLINE bool operator<=(u64ref lhs, p64ref rhs) noexcept
    {
        return !(lhs > rhs);
    }
    INLINE bool operator>=(u64ref lhs, p64ref rhs) noexcept
    {
        return !(lhs < rhs);
    }

    INLINE bool operator==(p64ref lhs, p64ref rhs) noexcept
    {
        return lhs.uint64 == rhs.uint64;
    }
    INLINE bool operator!=(p64ref lhs, p64ref rhs) noexcept
    {
        return !(lhs.uint64 == rhs.uint64);
    }
    INLINE bool operator<(p64ref lhs, p64ref rhs) noexcept
    {
        return lhs.uint64 < rhs.uint64;
    }
    INLINE bool operator>(p64ref lhs, p64ref rhs) noexcept
    {
        return rhs.uint64 < lhs.uint64;
    }
    INLINE bool operator<=(p64ref lhs, p64ref rhs) noexcept
    {
        return !(lhs > rhs);
    }
    INLINE bool operator>=(p64ref lhs, p64ref rhs) noexcept
    {
        return !(lhs < rhs);
    }

    class mut_p128
    {
    public:
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

            mut_p16 packed16[sizeof(uint16)];
            mut_p32 packed32[sizeof(uint32)];
            mut_p64 packed64[sizeof(uint64)];
        };

        mut_p128() { int128 = _mm_setzero_si128(); }

        mut_p128(__m128i i128) { int128 = _mm_loadu_si128(&i128); }

        mut_p128(i64 i64_all) { int128 = _mm_set1_epi64x(i64_all); }
        mut_p128(i64 Low, i64 High)
        {
            int128 = _mm_set_epi64x(High, Low);
        }

        mut_p128(i32 i32_all) { int128 = _mm_set1_epi32(i32_all); }
        mut_p128(i32 i32_0, i32 i32_1, i32 i32_2, i32 i32_3)
        {
            int128 = _mm_set_epi32(i32_3, i32_2, i32_1, i32_0);
        }

        mut_p128(i16 i16_all) { int128 = _mm_set1_epi16(i16_all); }
        mut_p128(i16 i16_0, i16 i16_1, i16 i16_2, i16 i16_3,
                i16 i16_4, i16 i16_5, i16 i16_6, i16 i16_7)
        {
            int128 = _mm_set_epi16(i16_7, i16_6, i16_5, i16_4,
                                i16_3, i16_2, i16_1, i16_0);
        }

        mut_p128(i8 b_all) { int128 = _mm_set1_epi8(b_all); }
        mut_p128(i8 b0, i8 b1, i8 b2, i8 b3,
                i8 b4, i8 b5, i8 b6, i8 b7,
                i8 b8, i8 b9, i8 b10, i8 b11,
                i8 b12, i8 b13, i8 b14, i8 b15)
        {
            int128 = _mm_set_epi8(b15, b14, b13, b12,
                                b11, b10, b9, b8,
                                b7, b6, b5, b4,
                                b3, b2, b1, b0);
        }

        /*
        &	bitwise AND
        |	bitwise inclusive OR
        ^	bitwise XOR (exclusive OR)
        <<	left shift
        >>	right shift
        ~	bitwise NOT (ones' complement) (unary)
        */
        INLINE const mut_p128& operator&=(__m128i u) noexcept
        {
            //__m128i _mm_and_si128(__m128i a, __m128i b)
            int128 = _mm_and_si128(int128, u);
        }
        INLINE const mut_p128& operator|=(__m128i u) noexcept
        {
            //__m128i _mm_or_si128(__m128i a, __m128i b)
            int128 = _mm_or_si128(int128, u);
        }
        INLINE const mut_p128& operator^=(__m128i u) noexcept
        {
            //__m128i _mm_xor_si128(__m128i a, __m128i b)
            int128 = _mm_xor_si128(int128, u);
        }
        INLINE const mut_p128& operator<<=(i32 shift_ct) noexcept
        {
            //__m128i _mm_slli_epi32(__m128i, int);
            int128 = _mm_slli_epi32(int128, shift_ct);
        }
        INLINE const mut_p128& operator>>=(i32 shift_ct) noexcept
        {
            //__m128i _mm_srli_epi32(__m128i, int);
            int128 = _mm_srli_epi32(int128, shift_ct);
        }

        INLINE mut_p128 operator-() const noexcept
        {
            const __m128i mask = _mm_set1_epi32(-1);
            return _mm_sign_epi32(int128, mask);
        }
        INLINE const mut_p128& operator+=(__m128i u) noexcept
        {
            int128 = _mm_add_epi32(int128, u);
        }
        INLINE const mut_p128& operator-=(__m128i u) noexcept
        {
            int128 = _mm_sub_epi32(int128, u);
        }
        INLINE const mut_p128& operator*=(__m128i u) noexcept
        {
            int128 = _mm_mullo_epi32(int128, u);
        }

        // TODO(RYAN_2024-09-15): Look into and check if a cast to
        // floating point -> reciprocal -> multiply
        // is faster than this piecewise division.
        //
        //__m256d _mm256_castsi256_pd(__m256i a) -> cast int256 to float256
        //__m256 _mm256_div_ps(__m256 a, __m256 b) -> float, f32
        //__m256i _mm256_castpd_si256(__m256d a)
        INLINE const mut_p128& operator/=(__m128i u) noexcept
        {
            uint32[0] /= u.m128i_u32[0];
            uint32[1] /= u.m128i_u32[1];
            uint32[2] /= u.m128i_u32[2];
            uint32[3] /= u.m128i_u32[3];
        }

        INLINE const mut_p128& operator+=(const mut_p128 p) noexcept
        {
            *this += p.int128;
        }
        INLINE const mut_p128& operator-=(const mut_p128 p) noexcept
        {
            *this -= p.int128;
        }
        INLINE const mut_p128& operator*=(const mut_p128 p) noexcept
        {
            *this *= p.int128;
        }
        INLINE const mut_p128& operator/=(const mut_p128 p) noexcept
        {
            *this /= p.int128;
        }

        INLINE u64 High() const noexcept { return uint64[HIGH]; }
        INLINE u64 Low() const noexcept { return uint64[LOW]; }
        INLINE u64 HighQword() const noexcept { return High(); }
        INLINE u64 LowQword() const noexcept { return Low(); }
        INLINE p64 PackedHigh() const noexcept { return packed64[HIGH]; }
        INLINE p64 PackedLow() const noexcept { return packed64[LOW]; }

        // (~this & b)
        INLINE __m128i AndNot(const __m128i& against) const noexcept
        {
            //__m128i _mm_andnot_si128(__m128i a, __m128i b)
            return _mm_andnot_si128(int128, against);
        }
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

            mut_p16 packed16[sizeof(uint16)];
            mut_p32 packed32[sizeof(uint32)];
            mut_p64 packed64[sizeof(uint64)];
            mut_p128 packed128[sizeof(int128)];
        };

        mut_p256() { int256 = _mm256_setzero_si256(); }

        mut_p256(const __m256i& i256) { int256 = _mm256_loadu_si256(&i256); }

        mut_p256(const __m128i& i128_all)
        {
            int256 = _mm256_set_m128i(i128_all, i128_all);
        }
        mut_p256(const __m128i& high, const __m128i& low)
        {
            int256 = _mm256_set_m128i(high, low);
        }

        mut_p256(i64 i64_all) { int256 = _mm256_set1_epi64x(i64_all); }
        mut_p256(i64 i64_0, i64 i64_1, i64 i64_2, i64 i64_3)
        {
            //__m256i _mm256_set_epi64x(__int64 e3, __int64 e2, __int64 e1, __int64 e0)
            int256 = _mm256_set_epi64x(i64_3, i64_2, i64_1, i64_0);
        }

        mut_p256(i32 i32_all) { int256 = _mm256_set1_epi32(i32_all); }
        mut_p256(i32 i32_0, i32 i32_1, i32 i32_2, i32 i32_3,
                i32 i32_4, i32 i32_5, i32 i32_6, i32 i32_7)
        {
            //__m256i _mm256_set_epi32(int e7, int e6, int e5, int e4,
            //                          int e3, int e2, int e1, int e0)
            int256 = _mm256_set_epi32(i32_7, i32_6, i32_5, i32_4,
                                    i32_3, i32_2, i32_1, i32_0);
        }

        mut_p256(i16 i16_all) { int256 = _mm256_set1_epi16(i16_all); }
        mut_p256(i16 i16_15, i16 i16_14, i16 i16_13, i16 i16_12,
                i16 i16_11, i16 i16_10, i16 i16_9, i16 i16_8,
                i16 i16_7, i16 i16_6, i16 i16_5, i16 i16_4,
                i16 i16_3, i16 i16_2, i16 i16_1, i16 i16_0)
        {
            //__m256i _mm256_set_epi16(short e15, short e14, short e13, short e12, short e11, short e10, short e9, short e8, short e7, short e6, short e5, short e4, short e3, short e2, short e1, short e0)
            int256 = _mm256_set_epi16(i16_15, i16_14, i16_13, i16_12,
                                    i16_11, i16_10, i16_9, i16_8,
                                    i16_7, i16_6, i16_5, i16_4,
                                    i16_3, i16_2, i16_1, i16_0);
        }

        mut_p256(i8 i8_all) { int256 = _mm256_set1_epi8(i8_all); }

        INLINE mut_p256 operator-() const noexcept
        {
            const __m256i mask = _mm256_set1_epi32(-1);
            return _mm256_sign_epi32(int256, mask);
        }
        INLINE const mut_p256& operator+=(__m256i u) noexcept
        {
            int256 = _mm256_add_epi32(int256, u);
        }
        INLINE const mut_p256& operator-=(__m256i u) noexcept
        {
            int256 = _mm256_sub_epi32(int256, u);
        }
        INLINE const mut_p256& operator*=(__m256i u) noexcept
        {
            int256 = _mm256_mullo_epi32(int256, u);
        }

        // TODO(RYAN_2024-09-15): Look into and check if a cast to
        // floating point -> reciprocal -> multiply
        // is faster than this piecewise division.
        //
        //__m256d _mm256_castsi256_pd(__m256i a) -> cast int256 to float256
        //__m256 _mm256_div_ps(__m256 a, __m256 b) -> float, f32
        //__m256i _mm256_castpd_si256(__m256d a)
        INLINE const mut_p256& operator/=(__m256i u) noexcept
        {
            uint64[0] /= u.m256i_u64[0];
            uint64[1] /= u.m256i_u64[1];
            uint64[2] /= u.m256i_u64[2];
            uint64[3] /= u.m256i_u64[3];
        }
        INLINE const mut_p256& operator+=(const mut_p256 p) noexcept
        {
            *this += p.int256;
        }
        INLINE const mut_p256& operator-=(const mut_p256 p) noexcept
        {
            *this -= p.int256;
        }
        INLINE const mut_p256& operator*=(const mut_p256 p) noexcept
        {
            *this *= p.int256;
        }
        INLINE const mut_p256& operator/=(const mut_p256 p) noexcept
        {
            *this /= p.int256;
        }

        INLINE __m128i High() const noexcept { return int128[HIGH]; }
        INLINE __m128i Low() const noexcept { return int128[LOW]; }
        INLINE p128 PackedHigh() const noexcept { return packed128[HIGH]; }
        INLINE p128 PackedLow() const noexcept { return packed128[LOW]; }
    };

    // Packed Types that have floating point data
    class mut_pf32
    {
    public:
        union
        {
            mut_i8 bytes[sizeof(f32)];

            mut_p32 packed;

            mut_f32 float32;
        };

        mut_pf32() { float32 = 0.0f; }
        mut_pf32(i32 i) { float32 = (f32)i; }
        mut_pf32(f32 f) { float32 = f; }
        mut_pf32(i16 high, i16 low)
        {
            packed.uint16[HIGH] = high;
            packed.uint16[LOW] = low;
        }
        mut_pf32(p16 high, p16 low)
        {
            packed.packed16[HIGH] = high.uint16;
            packed.packed16[LOW] = low.uint16;
        }
        mut_pf32(u8 b0, u8 b1, u8 b2, u8 b3)
        {
            bytes[0] = b0;
            bytes[1] = b1;
            bytes[2] = b2;
            bytes[3] = b3;
        }
    };

    class mut_pf64
    {
    public:
        union
        {
            mut_i8 bytes[sizeof(f64)];

            mut_pf32 packedf32[sizeof(p64) / sizeof(p32)];

            mut_f32 float32[sizeof(p64) / sizeof(f32)];
            mut_f64 float64;
        };

        mut_pf64() { float64 = 0.0; }

        mut_pf64(i64 i) { float64 = (f64)i; }
        mut_pf64(f64 d) { float64 = d; }

        mut_pf64(i16 i16_0, i16 i16_1, i16 i16_2, i16 i16_3)
        {
            packedf32[HIGH].packed.int16[HIGH] = i16_0;
            packedf32[HIGH].packed.int16[LOW] = i16_1;
            packedf32[LOW].packed.int16[HIGH] = i16_2;
            packedf32[LOW].packed.int16[LOW] = i16_3;
        }

        mut_pf64(i32 high, i32 low)
        {
            float32[HIGH] = (f32)high;
            float32[LOW] = (f32)low;
        }
        mut_pf64(pf32 high, pf32 low)
        {
            packedf32[HIGH] = high;
            packedf32[LOW] = low;
        }

        mut_pf64(i8 b0, i8 b1, i8 b2, i8 b3, i8 b4, i8 b5, i8 b6, i8 b7)
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

        INLINE f32 High() const noexcept { return float32[HIGH]; }
        INLINE f32 Low() const noexcept { return float32[LOW]; }
        INLINE pf32 PackedHigh() const noexcept { return packedf32[HIGH]; }
        INLINE pf32 PackedLow() const noexcept { return packedf32[LOW]; }
    };

    class mut_pf128
    {
        union
        {
            mut_i8 bytes[sizeof(__m128)];

            mut_f32 float32[sizeof(__m128) / sizeof(f32)];
            mut_f64 float64[sizeof(__m128) / sizeof(f64)];

            mut_pf32 packedf32[sizeof(__m128) / sizeof(f32)];
            mut_pf64 packedf64[sizeof(__m128) / sizeof(f64)];

            __m128 float128;
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
            mut_i8 bytes[sizeof(__m256)];

            mut_f32 float32[sizeof(__m256) / sizeof(f32)];
            mut_f64 float64[sizeof(__m256) / sizeof(f64)];
            __m128 float128[sizeof(__m256) / sizeof(__m128)];

            mut_pf32 packedf32[sizeof(__m256) / sizeof(f32)];
            mut_pf64 packedf64[sizeof(__m256) / sizeof(f64)];
            mut_pf128 packedf128[sizeof(__m256) / sizeof(__m128)];

            __m256 float256;
        };

        INLINE __m128 High() const noexcept { return float128[HIGH]; }
        INLINE __m128 Low() const noexcept { return float128[LOW]; }
        INLINE pf128 PackedHigh() const noexcept { return packedf128[HIGH]; }
        INLINE pf128 PackedLow() const noexcept { return packedf128[LOW]; }
    };
}
