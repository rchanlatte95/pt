#pragma once
#include <string>

#include "rac.hpp"
#include "rac-tinystr.hpp"
#include "rac-v3.hpp"

namespace rac::static_strings
{
    u64 TARGET_CACHESTR_BYTE_SZ = CACHELINE_SIZE;
    u64 CACHESTR_CAP = TARGET_CACHESTR_BYTE_SZ - sizeof(u16);
    u64 MAX_CACHESTR_LEN = CACHESTR_CAP - NULL_TERMINATOR_LEN;

    class alignas(TARGET_CACHESTR_BYTE_SZ) mut_cachestr
    {
    private:
        mut_u16 Length;
        mut_u8 chars[MAX_CACHESTR_LEN];
        u8 NULL_TERM = NULL_TERMINATOR;

        constexpr void AppendNullTerminator() { *(chars + Length) = NULL_TERMINATOR; }
        INLINE static u16 StrLen(cstr str) { return (u16)strnlen_s(str, MAX_CACHESTR_LEN); }

    public:

        static constexpr u16 ClampLen(u64 inputLength)
        {
            if (inputLength > MAX_CACHESTR_LEN)
            {
                return MAX_CACHESTR_LEN;
            }
            return (u8)inputLength;
        }

        mut_cachestr() { memset(&Length, NULL_TERMINATOR, CACHESTR_CAP); }
        mut_cachestr(u8 c)
        {
            memset(&Length, NULL_TERMINATOR, CACHESTR_CAP);
            chars[Length++] = c;
        }
        mut_cachestr(cstr str)
        {
            Length = StrLen(str);
            memcpy_s(chars, MAX_CACHESTR_LEN, str, Length);
            AppendNullTerminator();
        }
        mut_cachestr(cstr str, u64 startIdx, u64 endIdx = MAX_CACHESTR_LEN)
        {
            if (startIdx >= endIdx)
            {
                memset(&Length, NULL_TERMINATOR, CACHESTR_CAP);
                return;
            }

            Length = ClampLen(endIdx - startIdx);
            memcpy_s(chars, MAX_CACHESTR_LEN, (str + startIdx), Length);
            AppendNullTerminator();
        }

        INLINE i32 Len() const noexcept { return Length; }
        INLINE i32 PenultLen() const noexcept
        {
            return (i32)std::max(Len() - 1, 0);
        }
        INLINE u8 Penultima() const noexcept
        {
            return chars[PenultLen()];
        }
        INLINE i32 SpaceLeft() const noexcept
        {
            return MAX_CACHESTR_LEN - Length;
        }
        INLINE u8ptr ToU8Ptr() const noexcept { return chars; }
        INLINE cstr ToCstr() const noexcept { return (cstr)chars; }
        INLINE mut_cstr ToCharPtr() const noexcept { return (mut_cstr)chars; }
        INLINE ptr Begin() const noexcept { return chars; }
        INLINE mut_ptr MutBegin() const noexcept { return (mut_ptr)(chars); }
        INLINE ptr End() const noexcept { return chars + Length; }
        INLINE mut_ptr MutEnd() const noexcept
        {
            return (mut_ptr)(chars + Length);
        }
        INLINE ptr ToFullPtr() const noexcept { return &Length; }

        INLINE bool Empty() const noexcept { return Length == 0; }
        INLINE bool Full() const noexcept
        {
            return Length >= MAX_CACHESTR_LEN;
        }
        INLINE bool Ample() const noexcept
        {
            return !Empty() && !Full();
        }

        INLINE void Clear()
        {
            memset(&Length, NULL_TERMINATOR, CACHESTR_CAP);
        }
        INLINE void Fill(u8 charToFillWith, u64 count = MAX_CACHESTR_LEN)
        {
            Length = ClampLen(count);
            memset(chars, charToFillWith, Length);
        }

        INLINE u8ref operator[](i32 index) noexcept
        {
            return chars[index];
        }
        INLINE operator cstr() const noexcept { return ToCstr(); }

        INLINE void Concat(u8 c) noexcept
        {
            if (Full()) { return; }
            chars[Length++] = c;
            AppendNullTerminator();
        }
        INLINE void Concat(cstr str) noexcept
        {
            if (str == nullptr || Full()) { return; }

            u64 rhs_len = (u64)StrLen(str);
            if (rhs_len == 0) { return; }

            u64 left = (u64)SpaceLeft();
            u16 cpy_ct = (u16)std::min(left, rhs_len);
            memcpy_s(MutEnd(), left, str, cpy_ct);
            Length += cpy_ct;
            chars[Length] = NULL_TERMINATOR;
        }
        INLINE void Concat(tinystr_ref str) noexcept
        {
            if (Full() || str.Empty()) { return; }

            i32 left = SpaceLeft();
            u16 cpy_ct = (u16)std::min(left, str.Len());
            memcpy_s(MutEnd(), left, str.Begin(), cpy_ct);
            Length += cpy_ct;
            chars[Length] = NULL_TERMINATOR;
        }
        INLINE void Concat(const mut_cachestr& str) noexcept
        {
            if (Full() || str.Empty()) { return; }

            i32 left = SpaceLeft();
            u16 cpy_ct = (u16)std::min(left, str.Len());
            memcpy_s(MutEnd(), left, str.Begin(), cpy_ct);
            Length += cpy_ct;
            chars[Length] = NULL_TERMINATOR;
        }
        INLINE void Concat(const std::string& str) noexcept
        {
            if (Full() || str.empty()) { return; }

            u64 left = (u64)SpaceLeft();
            u16 cpy_ct = (u16)std::min(left, str.length());
            memcpy_s(MutEnd(), left, str.c_str(), cpy_ct);
            Length += cpy_ct;
            chars[Length] = NULL_TERMINATOR;
        }

        MAY_INLINE mut_cachestr& operator=(cstr rhs) noexcept
        {
            if (rhs == nullptr)
            {
                return *this;
            }
            Length = StrLen(rhs);
            memcpy_s(chars, MAX_CACHESTR_LEN, rhs, Length);
            AppendNullTerminator();
            return *this;
        }
        MAY_INLINE mut_cachestr& operator=(u8 rhs) noexcept
        {
            chars[0] = rhs;
            Length = 1;
            AppendNullTerminator();
            return *this;
        }
        MAY_INLINE mut_cachestr& operator=(tinystr_ref rhs) noexcept
        {
            if (rhs.Empty())
            {
                return *this;
            }
            Length = ClampLen(rhs.Len());
            memcpy_s(chars, MAX_CACHESTR_LEN, rhs, Length);
            AppendNullTerminator();
            return *this;
        }
        MAY_INLINE mut_cachestr& operator=(const std::string& rhs) noexcept
        {
            if (rhs.empty())
            {
                return *this;
            }
            Length = ClampLen(rhs.length());
            memcpy_s(chars, MAX_CACHESTR_LEN, rhs.c_str(), Length);
            AppendNullTerminator();
            return *this;
        }
        MAY_INLINE mut_cachestr& operator=(std::string&& rhs) noexcept
        {
            if (rhs.empty())
            {
                return *this;
            }
            Length = ClampLen(rhs.length());
            memcpy_s(chars, MAX_CACHESTR_LEN, rhs.c_str(), Length);
            AppendNullTerminator();
            return *this;
        }

        MAY_INLINE mut_cachestr& operator+=(const mut_cachestr& rhs) noexcept
        {
            if (Full())
            {
                return *this;
            }
            Concat(rhs);
            return *this;
        }
        MAY_INLINE mut_cachestr& operator+=(tinystr_ref rhs) noexcept
        {
            if (Full())
            {
                return *this;
            }
            Concat(rhs);
            return *this;
        }
        MAY_INLINE mut_cachestr& operator+=(cstr rhs) noexcept
        {
            if (rhs == nullptr || Full())
            {
                return *this;
            }
            Concat(rhs);
            return *this;
        }
        MAY_INLINE mut_cachestr& operator+=(u8 rhs) noexcept
        {
            Concat(rhs);
            return *this;
        }
        MAY_INLINE mut_cachestr& operator+=(const std::string& rhs) noexcept
        {
            if (rhs.empty())
            {
                return *this;
            }
            Concat(rhs.c_str());
            return *this;
        }
        MAY_INLINE mut_cachestr& operator+=(std::string&& rhs) noexcept
        {
            if (rhs.empty())
            {
                return *this;
            }
            Length = ClampLen(rhs.length());
            memcpy_s(chars, MAX_CACHESTR_LEN, rhs.c_str(), Length);
            AppendNullTerminator();
            return *this;
        }
    };

    typedef mut_cachestr* mut_cachestr_ptr;
    typedef mut_cachestr& mut_cachestr_ref;
    typedef const mut_cachestr cachestr;
    typedef const mut_cachestr* cachestr_ptr;
    typedef const mut_cachestr& cachestr_ref;

    INLINE tinystr operator+(cachestr_ref lhs, cachestr_ref rhs)
    {
        mut_tinystr res = mut_tinystr(lhs);
        res.Concat(rhs);
        return res;
    }
    INLINE tinystr operator+(cachestr_ref lhs, cstr rhs)
    {
        mut_tinystr res = mut_tinystr(lhs);
        res.Concat(rhs);
        return res;
    }
    INLINE tinystr operator+(cstr lhs, cachestr_ref rhs)
    {
        mut_tinystr res = mut_tinystr(lhs);
        res.Concat(rhs);
        return res;
    }
    INLINE tinystr operator+(cachestr_ref lhs, const std::string& rhs)
    {
        mut_tinystr res = mut_tinystr(lhs);
        res.Concat(rhs);
        return res;
    }
    INLINE tinystr operator+(const std::string& lhs, cachestr_ref rhs)
    {
        mut_tinystr res = mut_tinystr(lhs.c_str());
        res.Concat(rhs);
        return res;
    }
    INLINE tinystr operator+(cachestr_ref lhs, const char rhs)
    {
        mut_tinystr res = mut_tinystr(lhs);
        res.Concat(rhs);
        return res;
    }
    INLINE tinystr operator+(const char lhs, cachestr_ref rhs)
    {
        mut_tinystr res = mut_tinystr(lhs);
        res.Concat(rhs);
        return res;
    }

    // cachestr comparisons
    INLINE bool operator==(cachestr_ref lhs, cachestr_ref rhs) noexcept
    {
        return memcmp(lhs.ToFullPtr(), rhs.ToFullPtr(), TARGET_CACHESTR_BYTE_SZ) == 0;
    }
    INLINE bool operator!=(cachestr_ref lhs, cachestr_ref rhs) noexcept
    {
        return !(lhs == rhs);
    }
    INLINE bool operator<(cachestr_ref lhs, cachestr_ref rhs) noexcept
    {
        return memcmp(lhs.ToFullPtr(), rhs.ToFullPtr(), TARGET_CACHESTR_BYTE_SZ) < 0;
    }
    INLINE bool operator>(cachestr_ref lhs, cachestr_ref rhs) noexcept
    {
        return rhs < lhs;
    }
    INLINE bool operator<=(cachestr_ref lhs, cachestr_ref rhs) noexcept
    {
        return !(lhs > rhs);
    }
    INLINE bool operator>=(cachestr_ref lhs, cachestr_ref rhs) noexcept
    {
        return !(lhs < rhs);
    }

    // tinystr comparisons
    INLINE bool operator==(cachestr_ref lhs, tinystr_ref rhs) noexcept
    {
        return rhs.Len() == lhs.Len() &&
            memcmp(lhs.ToU8Ptr(), rhs.ToU8Ptr(), TARGET_TINYSTR_BYTE_SZ) == 0;
    }
    INLINE bool operator==(tinystr_ref lhs, cachestr_ref rhs) noexcept
    {
        return rhs == lhs;
    }
    INLINE bool operator!=(cachestr_ref lhs, tinystr_ref rhs) noexcept
    {
        return !(lhs == rhs);
    }
    INLINE bool operator!=(tinystr_ref lhs, cachestr_ref rhs) noexcept
    {
        return !(rhs == lhs);
    }
    INLINE bool operator<(cachestr_ref lhs, tinystr_ref rhs) noexcept
    {
        return rhs.Len() < lhs.Len() ||
            memcmp(lhs.ToU8Ptr(), rhs.ToU8Ptr(), TARGET_TINYSTR_BYTE_SZ) < 0;
    }
    INLINE bool operator<(tinystr_ref lhs, cachestr_ref rhs) noexcept
    {
        return rhs < lhs;
    }
    INLINE bool operator>(cachestr_ref lhs, tinystr_ref rhs) noexcept
    {
        return rhs < lhs;
    }
    INLINE bool operator>(tinystr_ref lhs, cachestr_ref rhs) noexcept
    {
        return lhs < rhs;
    }
    INLINE bool operator<=(cachestr_ref lhs, tinystr_ref rhs) noexcept
    {
        return !(lhs > rhs);
    }
    INLINE bool operator<=(tinystr_ref lhs, cachestr_ref rhs) noexcept
    {
        return !(rhs > lhs);
    }
    INLINE bool operator>=(cachestr_ref lhs, tinystr_ref rhs) noexcept
    {
        return !(lhs < rhs);
    }
    INLINE bool operator>=(tinystr_ref lhs, cachestr_ref rhs) noexcept
    {
        return !(rhs < lhs);
    }

    // cstr comparisons
    INLINE bool operator==(cachestr_ref lhs, cstr rhs) noexcept
    {
        return strnlen_s(rhs, TARGET_CACHESTR_BYTE_SZ) == lhs.Len() &&
            memcmp(lhs.ToFullPtr(), rhs, TARGET_CACHESTR_BYTE_SZ) == 0;
    }
    INLINE bool operator==(cstr lhs, cachestr_ref rhs) noexcept
    {
        return rhs == lhs;
    }
    INLINE bool operator!=(cachestr_ref lhs, cstr rhs) noexcept
    {
        return !(lhs == rhs);
    }
    INLINE bool operator!=(cstr lhs, cachestr_ref rhs) noexcept
    {
        return !(rhs == lhs);
    }
    INLINE bool operator<(cachestr_ref lhs, cstr rhs) noexcept
    {
        return strnlen_s(rhs, TARGET_CACHESTR_BYTE_SZ) < lhs.Len() ||
            memcmp(lhs.ToFullPtr(), rhs, TARGET_CACHESTR_BYTE_SZ) < 0;
    }
    INLINE bool operator<(cstr lhs, cachestr_ref rhs) noexcept
    {
        return rhs < lhs;
    }
    INLINE bool operator>(cachestr_ref lhs, cstr rhs) noexcept
    {
        return rhs < lhs;
    }
    INLINE bool operator>(cstr lhs, cachestr_ref rhs) noexcept
    {
        return lhs < rhs;
    }
    INLINE bool operator<=(cachestr_ref lhs, cstr rhs) noexcept
    {
        return !(lhs > rhs);
    }
    INLINE bool operator<=(cstr lhs, cachestr_ref rhs) noexcept
    {
        return !(rhs > lhs);
    }
    INLINE bool operator>=(cachestr_ref lhs, cstr rhs) noexcept
    {
        return !(lhs < rhs);
    }
    INLINE bool operator>=(cstr lhs, cachestr_ref rhs) noexcept
    {
        return !(rhs < lhs);
    }

    // std::string comparisons
    INLINE bool operator==(cachestr_ref lhs, const std::string& rhs) noexcept
    {
        return rhs.length() == lhs.Len() &&
            memcmp(lhs.ToFullPtr(), rhs.c_str(), TARGET_CACHESTR_BYTE_SZ) == 0;
    }
    INLINE bool operator==(const std::string& lhs, cachestr_ref rhs) noexcept
    {
        return rhs == lhs;
    }
    INLINE bool operator!=(cachestr_ref lhs, const std::string& rhs) noexcept
    {
        return !(lhs == rhs);
    }
    INLINE bool operator!=(const std::string& lhs, cachestr_ref rhs) noexcept
    {
        return !(rhs == lhs);
    }
    INLINE bool operator<(cachestr_ref lhs, const std::string& rhs) noexcept
    {
        return rhs.length() < lhs.Len() ||
            memcmp(lhs.ToFullPtr(), rhs.c_str(), TARGET_CACHESTR_BYTE_SZ) < 0;
    }
    INLINE bool operator<(const std::string& lhs, cachestr_ref rhs) noexcept
    {
        return rhs < lhs;
    }
    INLINE bool operator>(cachestr_ref lhs, const std::string& rhs) noexcept
    {
        return rhs < lhs;
    }
    INLINE bool operator>(const std::string& lhs, cachestr_ref rhs) noexcept
    {
        return lhs < rhs;
    }
    INLINE bool operator<=(cachestr_ref lhs, const std::string& rhs) noexcept
    {
        return !(lhs > rhs);
    }
    INLINE bool operator<=(const std::string& rhs, cachestr_ref lhs) noexcept
    {
        return !(rhs > lhs);
    }
    INLINE bool operator>=(cachestr_ref lhs, const std::string& rhs) noexcept
    {
        return !(lhs < rhs);
    }
    INLINE bool operator>=(const std::string& rhs, cachestr_ref lhs) noexcept
    {
        return !(rhs < lhs);
    }
}