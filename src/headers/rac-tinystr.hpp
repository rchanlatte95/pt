#pragma once
#include "rac.hpp"

namespace rac::static_strings
{
    u8 TARGET_BYTE_SZ = 16;
    u8 LEN_VARIABLE_BYTE_SZ = SIZEOF(u8);
    u8 TINYSTR_CHAR_CT = TARGET_BYTE_SZ - NULL_TERMINATOR_LEN - LEN_VARIABLE_BYTE_SZ;

    class alignas(16) mut_tinystr
    {
    private:
        mut_u8 Length;

    public:
        mut_u8 characters[TINYSTR_CHAR_CT];

    private:
        u8 NULL_TERM = NULL_TERMINATOR;

    };

    typedef mut_tinystr* mut_tinystr_ptr;
    typedef mut_tinystr& mut_tinystr_ref;
    typedef const mut_tinystr tinystr;
    typedef const mut_tinystr* tinystr_ptr;
    typedef const mut_tinystr& tinystr_ref;
}