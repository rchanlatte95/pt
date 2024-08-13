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
        mut_u8 characters[MAX_TINYSTR_LEN];
        u8 NULL_TERM = NULL_TERMINATOR;

    public:

        static constexpr u8 ClampToLen(u64 inputLength)
        {
            return (u8)std::min(inputLength, MAX_TINYSTR_LEN);
        }

        mut_tinystr() { memset(&Length, NULL_TERMINATOR, TINYSTR_CAP); }
        mut_tinystr(cstr str)
        {
            Length = strnlen_s(str, MAX_TINYSTR_LEN);
            memcpy_s(characters, MAX_TINYSTR_LEN, str, Length);
        }
        mut_tinystr(cstr str, u64 strLen)
        {
            Length = ClampToLen(strLen);
            memcpy_s(characters, MAX_TINYSTR_LEN, str, Length);
        }

        INLINE void Clear()
        {
            memset(&Length, NULL_TERMINATOR, TINYSTR_CAP);
        }
        INLINE void Fill(u8 charToFillWith, u64 count = MAX_TINYSTR_LEN)
        {
            Length = ClampToLen(count);
            memset(characters, charToFillWith, Length);
        }
    };

    typedef mut_tinystr* mut_tinystr_ptr;
    typedef mut_tinystr& mut_tinystr_ref;
    typedef const mut_tinystr tinystr;
    typedef const mut_tinystr* tinystr_ptr;
    typedef const mut_tinystr& tinystr_ref;
}