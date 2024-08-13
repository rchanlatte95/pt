#pragma once
#include "rac.hpp"

namespace rac::static_strings
{
    // https://pvs-studio.com/en/blog/terms/6658/
    u8 TARGET_TINYSTR_BYTE_SZ = 16;
    u8 LEN_VARIABLE_BYTE_SZ = sizeof(u8);

    u8 TINYSTR_CAP = TARGET_TINYSTR_BYTE_SZ - LEN_VARIABLE_BYTE_SZ;
    u8 MAX_TINYSTR_LEN = TINYSTR_CAP - NULL_TERMINATOR_LEN;

    class alignas(TARGET_TINYSTR_BYTE_SZ) mut_tinystr
    {
    private:
        mut_u8 Length;
        mut_u8 characters[MAX_TINYSTR_LEN];
        u8 NULL_TERM = NULL_TERMINATOR;

    public:

        mut_tinystr() { memset(&Length, NULL_TERMINATOR, TINYSTR_CAP); }

    };

    typedef mut_tinystr* mut_tinystr_ptr;
    typedef mut_tinystr& mut_tinystr_ref;
    typedef const mut_tinystr tinystr;
    typedef const mut_tinystr* tinystr_ptr;
    typedef const mut_tinystr& tinystr_ref;
}