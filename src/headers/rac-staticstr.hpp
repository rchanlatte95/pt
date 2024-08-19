#pragma once
#include "rac.hpp"

namespace rac::static_strings
{
    u64 STATICSTR_VARIABLE_BYTE_CT = (sizeof(u64) * 2) + 1;

    class mut_staticstr
    {
    private:
        mut_i32 Length;
        mut_i32 Capacity;
        mut_u8ptr chars;

    public:

        INLINE constexpr i32 ClampLen(u64 inputLength) const noexcept
        {
            if (inputLength > Length)
            {
                return Length;
            }
            return (i32)inputLength;
        }
        INLINE constexpr i32 MaxLen() const noexcept
        {
            if (Capacity <= 0)
            {
                return 0;
            }
            return Capacity - 1;
        }

        mut_staticstr()
        {
            Capacity = CACHELINE_SIZE - STATICSTR_VARIABLE_BYTE_CT;
            memset(&Length, NULL_TERMINATOR, Capacity);
        }

        INLINE i32 Len() const noexcept { return Length; }
        INLINE i32 PenultLen() const noexcept
        {
            return (i32)std::max(Len() - 1, 0);
        }
        INLINE i32 Penultima() const noexcept { return chars[PenultLen()]; }
        INLINE i32 SpaceLeft() const noexcept
        {
            return Capacity - Length;
        }
        INLINE u8ptr ToU8Ptr() const noexcept { return chars; }
        INLINE cstr ToCstr() const noexcept { return (cstr)chars; }
        INLINE ptr ToPtr() const noexcept { return chars; }
        INLINE mut_ptr ToMutPtr() const noexcept { return (mut_ptr)chars; }
        INLINE ptr Last() const noexcept { return chars + Length; }
        INLINE mut_ptr MutLast() const noexcept { return (mut_ptr)(chars + Length); }
        INLINE bool Empty() const noexcept { return Length == 0; }
        INLINE bool Full() const noexcept { return SpaceLeft() <= 0; }
        INLINE bool Ample() const noexcept
        {
            return !Empty() && !Full();
        }

        INLINE void Clear()
        {
            memset(&Length, NULL_TERMINATOR, Capacity);
        }
        INLINE void Fill(u8 charToFillWith, u64 count = U64_MAX)
        {
            u64 safeCount = count == U64_MAX ? Capacity : ClampLen(count);
            Length = ClampLen(safeCount);
            memset(chars, charToFillWith, Length);
        }

        INLINE u8ref operator[](i32 index) noexcept { return chars[index]; }
        INLINE operator cstr() const noexcept { return ToCstr(); }

        INLINE void Concat(cstr str) noexcept
        {
            i32 left = SpaceLeft();
            i32 rhs_len = (u8)strnlen_s(str, Capacity);
            i32 cpy_ct = std::min(left, rhs_len);
            memcpy_s(MutLast(), left, str, cpy_ct);
            Length += cpy_ct;
            chars[Length] = NULL_TERMINATOR;
        }

        INLINE void Concat(mut_staticstr& str) noexcept
        {
            i32 left = SpaceLeft();
            i32 cpy_ct = std::min(left, str.Len());
            memcpy_s(MutLast(), left, str.ToPtr(), cpy_ct);
            Length += cpy_ct;
            chars[Length] = NULL_TERMINATOR;
        }

        MAY_INLINE mut_staticstr& operator+=(cstr rhs) noexcept
        {
            if (rhs == nullptr || Full())
            {
                return *this;
            }
            Concat(rhs);
            return *this;
        }
    };

    typedef mut_staticstr* mut_staticstr_ptr;
    typedef mut_staticstr& mut_staticstr_ref;
    typedef const mut_staticstr staticstr;
    typedef const mut_staticstr* staticstr_ptr;
    typedef const mut_staticstr& staticstr_ref;
}