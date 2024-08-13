#pragma once
#include "rac.hpp"

namespace rac::static_strings
{
    // https://pvs-studio.com/en/blog/terms/6658/
    u64 TARGET_TINYSTR_BYTE_SZ = 16;
    u64 LEN_VARIABLE_BYTE_SZ = sizeof(u8);

    u64 TINYSTR_CAP = TARGET_TINYSTR_BYTE_SZ - LEN_VARIABLE_BYTE_SZ;
    u64 MAX_TINYSTR_LEN = TINYSTR_CAP - NULL_TERMINATOR_LEN;

    class alignas(TARGET_TINYSTR_BYTE_SZ) mut_tinystr
    {
    private:
        mut_u8 Length;
        mut_u8 chars[MAX_TINYSTR_LEN];
        u8 NULL_TERM = NULL_TERMINATOR;

    public:

        static constexpr u8 ClampLen(u64 inputLength)
        {
            if (inputLength > MAX_TINYSTR_LEN)
            {
                return MAX_TINYSTR_LEN;
            }
            return (u8)inputLength;
        }

        mut_tinystr() { memset(&Length, NULL_TERMINATOR, TINYSTR_CAP); }
        mut_tinystr(cstr str)
        {
            Length = ClampLen(strnlen_s(str, MAX_TINYSTR_LEN));
            memcpy_s(chars, MAX_TINYSTR_LEN, str, Length);
        }
        mut_tinystr(cstr str, u64 strLen)
        {
            Length = ClampLen(strLen);
            memcpy_s(chars, MAX_TINYSTR_LEN, str, Length);
        }

        INLINE i32 Len() const noexcept { return Length; }
        INLINE i32 PenultLen() const noexcept
        {
            return (i32)std::max(Len() - 1, 0);
        }
        INLINE u8 Penultima() const noexcept { return chars[PenultLen()]; }
        INLINE u8 SpaceLeft() const noexcept
        {
            return MAX_TINYSTR_LEN - Length;
        }
        INLINE u8ptr ToU8Ptr() const noexcept { return chars; }
        INLINE cstr ToCstr() const noexcept { return (cstr)chars; }
        INLINE ptr ToPtr() const noexcept { return chars; }
        INLINE bool Empty() const noexcept { return Length == 0; }
        INLINE bool Full() const noexcept { return SpaceLeft() > 0; }
        INLINE bool Ample() const noexcept
        {
            return !Empty() && !Full();
        }

        INLINE void Clear()
        {
            memset(&Length, NULL_TERMINATOR, TINYSTR_CAP);
        }
        INLINE void Fill(u8 charToFillWith, u64 count = MAX_TINYSTR_LEN)
        {
            Length = ClampLen(count);
            memset(chars, charToFillWith, Length);
        }

        INLINE u8ref operator[](i32 index) noexcept { return chars[index]; }
        INLINE operator cstr() const noexcept { return ToCstr(); }

        INLINE mut_tinystr& operator+=(cstr rhs) noexcept
        {
            if (rhs == nullptr || Full())
            {
                return *this;
            }

            u8 rhs_len = (u8)strnlen_s(rhs, MAX_TINYSTR_LEN);
            u8 cpy_ct = std::min(SpaceLeft(), rhs_len);
            memcpy_s(chars, SpaceLeft(), rhs, cpy_ct);
            return *this;
        }
    };

    typedef mut_tinystr* mut_tinystr_ptr;
    typedef mut_tinystr& mut_tinystr_ref;
    typedef const mut_tinystr tinystr;
    typedef const mut_tinystr* tinystr_ptr;
    typedef const mut_tinystr& tinystr_ref;
}