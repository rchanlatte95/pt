#pragma once
#include <string>
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

        constexpr void AppendNullTerminator() { *(chars + Length) = NULL_TERMINATOR; }
        INLINE static u8 StrLen(cstr str) { return (u8)strnlen_s(str, MAX_TINYSTR_LEN); }

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
        mut_tinystr(u8 c)
        {
            memset(&Length, NULL_TERMINATOR, TINYSTR_CAP);
            chars[Length++] = c;
        }
        mut_tinystr(cstr str)
        {
            Length = StrLen(str);
            memcpy_s(chars, MAX_TINYSTR_LEN, str, Length);
            AppendNullTerminator();
        }
        mut_tinystr(cstr str, u64 startIdx, u64 endIdx = MAX_TINYSTR_LEN)
        {
            if (startIdx >= endIdx)
            {
                memset(&Length, NULL_TERMINATOR, TINYSTR_CAP);
                return;
            }

            Length = ClampLen(endIdx - startIdx);
            memcpy_s(chars, MAX_TINYSTR_LEN, (str + startIdx), Length);
            AppendNullTerminator();
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
        INLINE ptr Begin() const noexcept { return chars; }
        INLINE mut_ptr MutBegin() const noexcept { return (mut_ptr)(chars); }
        INLINE ptr End() const noexcept { return chars + Length; }
        INLINE mut_ptr MutEnd() const noexcept { return (mut_ptr)(chars + Length); }

        INLINE bool Empty() const noexcept { return Length == 0; }
        INLINE bool Full() const noexcept { return Length >= MAX_TINYSTR_LEN; }
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

        INLINE void Concat(u8 c) noexcept
        {
            if (Full()) { return; }
            chars[Length++] = c;
            AppendNullTerminator();
        }
        INLINE void Concat(cstr str) noexcept
        {
            if (str == nullptr || Full()) { return; }

            u8 rhs_len = StrLen(str);
            if (rhs_len <= 0) { return; }

            u8 left = SpaceLeft();
            u8 cpy_ct = std::min(left, rhs_len);
            memcpy_s(MutEnd(), left, str, cpy_ct);
            Length += cpy_ct;
            chars[Length] = NULL_TERMINATOR;
        }
        INLINE void Concat(const mut_tinystr& str) noexcept
        {
            if (Full() || str == nullptr || str.Empty()) { return; }

            u8 left = SpaceLeft();
            u8 cpy_ct = std::min(left, (u8)str.Len());
            memcpy_s(MutEnd(), left, str.Begin(), cpy_ct);
            Length += cpy_ct;
            chars[Length] = NULL_TERMINATOR;
        }
        INLINE void Concat(const std::string& str) noexcept
        {
            if (Full() || str.empty()) { return; }

            u8 left = SpaceLeft();
            u8 cpy_ct = std::min(left, (u8)str.length());
            memcpy_s(MutEnd(), left, str.c_str(), cpy_ct);
            Length += cpy_ct;
            chars[Length] = NULL_TERMINATOR;
        }

        MAY_INLINE mut_tinystr& operator=(cstr rhs) noexcept
        {
            if (rhs == nullptr)
            {
                return *this;
            }
            Length = StrLen(rhs);
            memcpy_s(chars, MAX_TINYSTR_LEN, rhs, Length);
            AppendNullTerminator();
            return *this;
        }
        MAY_INLINE mut_tinystr& operator=(u8 rhs) noexcept
        {
            chars[0] = rhs;
            Length = 1;
            AppendNullTerminator();
            return *this;
        }
        MAY_INLINE mut_tinystr& operator=(const std::string& rhs) noexcept
        {
            if (rhs.empty())
            {
                return *this;
            }
            Length = ClampLen(rhs.length());
            memcpy_s(chars, MAX_TINYSTR_LEN, rhs.c_str(), Length);
            AppendNullTerminator();
            return *this;
        }
        MAY_INLINE mut_tinystr& operator=(std::string&& rhs) noexcept
        {
            if (rhs.empty())
            {
                return *this;
            }
            Length = ClampLen(rhs.length());
            memcpy_s(chars, MAX_TINYSTR_LEN, rhs.c_str(), Length);
            AppendNullTerminator();
            return *this;
        }

        MAY_INLINE mut_tinystr& operator+=(mut_tinystr& rhs) noexcept
        {
            if (rhs == nullptr || Full())
            {
                return *this;
            }
            Concat(rhs);
            return *this;
        }
        MAY_INLINE mut_tinystr& operator+=(cstr rhs) noexcept
        {
            if (rhs == nullptr || Full())
            {
                return *this;
            }
            Concat(rhs);
            return *this;
        }
        MAY_INLINE mut_tinystr& operator+=(u8 rhs) noexcept
        {
            Concat(rhs);
            return *this;
        }
        MAY_INLINE mut_tinystr& operator+=(const std::string& rhs) noexcept
        {
            if (rhs.empty())
            {
                return *this;
            }
            Concat(rhs.c_str());
            return *this;
        }
        MAY_INLINE mut_tinystr& operator+=(std::string&& rhs) noexcept
        {
            if (rhs.empty())
            {
                return *this;
            }
            Length = ClampLen(rhs.length());
            memcpy_s(chars, MAX_TINYSTR_LEN, rhs.c_str(), Length);
            AppendNullTerminator();
            return *this;
        }
    };

    typedef mut_tinystr* mut_tinystr_ptr;
    typedef mut_tinystr& mut_tinystr_ref;
    typedef const mut_tinystr tinystr;
    typedef const mut_tinystr* tinystr_ptr;
    typedef const mut_tinystr& tinystr_ref;

    INLINE tinystr operator+(tinystr_ref lhs, tinystr_ref rhs)
    {
        mut_tinystr res = mut_tinystr(lhs);
        res.Concat(rhs);
        return res;
    }
    INLINE tinystr operator+(tinystr_ref lhs, cstr rhs)
    {
        mut_tinystr res = mut_tinystr(lhs);
        res.Concat(rhs);
        return res;
    }
    INLINE tinystr operator+(cstr lhs, tinystr_ref rhs)
    {
        mut_tinystr res = mut_tinystr(lhs);
        res.Concat(rhs);
        return res;
    }
    INLINE tinystr operator+(tinystr_ref lhs, const std::string& rhs)
    {
        mut_tinystr res = mut_tinystr(lhs);
        res.Concat(rhs);
        return res;
    }
    INLINE tinystr operator+(const std::string& lhs, tinystr_ref rhs)
    {
        mut_tinystr res = mut_tinystr(lhs.c_str());
        res.Concat(rhs);
        return res;
    }
    INLINE tinystr operator+(tinystr_ref lhs, const char rhs)
    {
        mut_tinystr res = mut_tinystr(lhs);
        res.Concat(rhs);
        return res;
    }
    INLINE tinystr operator+(const char lhs, tinystr_ref rhs)
    {
        mut_tinystr res = mut_tinystr(lhs);
        res.Concat(rhs);
        return res;
    }

    INLINE bool operator== (const mut_tinystr& lhs, tinystr_ref rhs) noexcept
    {
        ptr lhs_top = lhs.Begin() - 1;
        ptr rhs_top = rhs.Begin() - 1;
        u64 cmp_ct = TARGET_TINYSTR_BYTE_SZ * 2;
        return memcmp(lhs_top, rhs_top, cmp_ct) == 0;
    }

    // f => 1234567.1234 => 12
    // (f, f, f, f)
    /*
    bool operator== (const string& lhs, const string& rhs) noexcept;bool operator== (const char*   lhs, const string& rhs);bool operator== (const string& lhs, const char*   rhs);
    bool operator!= (const string& lhs, const string& rhs) noexcept;bool operator!= (const char*   lhs, const string& rhs);bool operator!= (const string& lhs, const char*   rhs);
    bool operator<  (const string& lhs, const string& rhs) noexcept;bool operator<  (const char*   lhs, const string& rhs);bool operator<  (const string& lhs, const char*   rhs);
    bool operator<= (const string& lhs, const string& rhs) noexcept;bool operator<= (const char*   lhs, const string& rhs);bool operator<= (const string& lhs, const char*   rhs);
    bool operator>  (const string& lhs, const string& rhs) noexcept;bool operator>  (const char*   lhs, const string& rhs);bool operator>  (const string& lhs, const char*   rhs);
    bool operator>= (const string& lhs, const string& rhs) noexcept;bool operator>= (const char*   lhs, const string& rhs);bool operator>= (const string& lhs, const char*   rhs);
    */
}