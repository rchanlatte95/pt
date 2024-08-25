#pragma once
// C Headers
#include <assert.h>
#include <complex.h>
#include <ctype.h>
#include <errno.h>
#include <fenv.h>
#include <float.h>
#include <inttypes.h>
#include <iso646.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>
#include <uchar.h>
#include <wchar.h>
#include <wctype.h>
#include <immintrin.h>

// C++ Headers
#include <unordered_map>
#include <vector>
#include <new>
#include <thread>
#include <algorithm>
#include <filesystem>

#ifdef _MSC_VER
#define NOMINMAX 0

#include <io.h>
#include <intrin.h>
#include <Windows.h>
#include <shlobj.h>
#include <objbase.h>
#pragma comment(lib,"Shell32")
#pragma comment(lib,"Ole32")
#else
#include <x86intrin.h>
#endif

#define MAY_INLINE __inline
#define INLINE __forceinline
#define NO_INLINE __declspec(noinline)

namespace rac
{
    typedef void* mut_ptr;
    typedef const void* ptr;

    typedef FILE* mut_FileHandle;
    typedef const FILE* FileHandle;

    typedef char* mut_cstr;
    typedef const char* cstr;
    typedef char** mut_cstrptr;
    typedef const char** cstrptr;

    typedef wchar_t* mut_wstr;
    typedef const wchar_t* wstr;
    typedef wchar_t** mut_wstrptr;
    typedef const wchar_t** wstrptr;

    typedef int8_t mut_i8;
    typedef int8_t* mut_i8ptr;
    typedef int8_t& mut_i8ref;
    typedef const int8_t i8;
    typedef const int8_t* i8ptr;
    typedef const int8_t& i8ref;

    typedef uint8_t mut_u8;
    typedef uint8_t* mut_u8ptr;
    typedef uint8_t& mut_u8ref;
    typedef const uint8_t u8;
    typedef const uint8_t* u8ptr;
    typedef const uint8_t& u8ref;

    typedef int16_t mut_i16;
    typedef int16_t* mut_i16ptr;
    typedef int16_t& mut_i16ref;
    typedef const int16_t i16;
    typedef const int16_t* i16ptr;
    typedef const int16_t& i16ref;

    typedef uint16_t mut_u16;
    typedef uint16_t* mut_u16ptr;
    typedef uint16_t& mut_u16ref;
    typedef const uint16_t u16;
    typedef const uint16_t* u16ptr;
    typedef const uint16_t& u16ref;

    typedef int32_t mut_i32;
    typedef int32_t* mut_i32ptr;
    typedef int32_t& mut_i32ref;
    typedef const int32_t i32;
    typedef const int32_t* i32ptr;
    typedef const int32_t& i32ref;

    typedef uint32_t mut_u32;
    typedef uint32_t* mut_u32ptr;
    typedef uint32_t& mut_u32ref;
    typedef const uint32_t u32;
    typedef const uint32_t* u32ptr;
    typedef const uint32_t& u32ref;

    typedef int64_t mut_i64;
    typedef int64_t* mut_i64ptr;
    typedef int64_t& mut_i64ref;
    typedef const int64_t i64;
    typedef const int64_t* i64ptr;
    typedef const int64_t& i64ref;

    typedef uint64_t mut_u64;
    typedef uint64_t* mut_u64ptr;
    typedef uint64_t& mut_u64ref;
    typedef const uint64_t u64;
    typedef const uint64_t* u64ptr;
    typedef const uint64_t& u64ref;

    typedef float mut_f32;
    typedef float* mut_f32ptr;
    typedef float& mut_f32ref;
    typedef const float f32;
    typedef const float* f32ptr;
    typedef const float& f32ref;

    typedef double mut_f64;
    typedef double* mut_f64ptr;
    typedef double& mut_f64ref;
    typedef const double f64;
    typedef const double* f64ptr;
    typedef const double& f64ref;

    u32 CACHELINE_SIZE = (u32)std::hardware_destructive_interference_size;
    u32 FALSE_SHARE_CACHE_SIZE = (u32)std::hardware_destructive_interference_size;
    u32 TRUE_SHARE_CACHE_SIZE = (u32)std::hardware_constructive_interference_size;
    u32 MAX_THREAD_CT = std::thread::hardware_concurrency();

    u32 SSE128_ALIGNMENT_BYTE_SIZE = 16;
    u32 AVX256_ALIGNMENT_BYTE_SIZE = 32;
    u32 AVX512_ALIGNMENT_BYTE_SIZE = 64;

    u32 BITS_IN_BYTE = 8;
    u32 KB = 1024;
    u32 WIN_PAGE_SIZE = 4 * KB;
    u32 MB = KB * 1024;
    u32 GB = MB * 1024;

    f32 PI = 3.14159265358979323846f;
    f32 INV_PI = 1.0f / PI;
    f32 SIXTH_PI = PI / 6.0f;
    f32 FOURTH_PI = PI / 4.0f;
    f32 THIRD_PI = PI / 3.0f;
    f32 HALF_PI = PI / 2.0f;
    f32 TAU = 2.0f * PI;

    f32 DEG2RAD = PI / 180.0f;
    f32 RAD2DEG = 180.0f / PI;

    i8 I8_MAX = INT8_MAX;
    i16 I16_MAX = INT16_MAX;
    i32 I32_MAX = INT32_MAX;
    i64 I64_MAX = INT64_MAX;

    u8 U8_MAX = UINT8_MAX;
    u16 U16_MAX = UINT16_MAX;
    u32 U32_MAX = UINT32_MAX;
    u64 U64_MAX = UINT64_MAX;

    f32 INV_U8_MAX = 1.0f / (f32)U8_MAX;
    f32 INV_U16_MAX = 1.0f / (f32)U16_MAX;
    f32 INV_U32_MAX = 1.0f / (f32)U32_MAX;
    f32 INV_U64_MAX = 1.0f / (f32)U64_MAX;

    u8 ABS_I8_MIN = (u8)(-(INT8_MIN));
    u16 ABS_I16_MIN = (u16)(-(INT16_MIN));
    u32 ABS_I32_MIN = (u32)(-(INT32_MIN));
    u64 ABS_I64_MIN = (u64)(-(INT64_MIN));

    f32 F32_EPSILON = FLT_EPSILON;
    f32 F32_MAX = FLT_MAX;
    f32 F32_MIN = FLT_MIN;
    f32 SIGNED_F32_EPSILON = -F32_EPSILON;
    f32 F32_ONE_EPSILON = 1.0f - F32_EPSILON;
    f32 SIGNED_F32_ONE_EPSILON = -F32_ONE_EPSILON;

    f64 F64_EPSILON = DBL_EPSILON;
    f64 F64_MAX = DBL_MAX;
    f64 F64_MIN = DBL_MIN;
    f64 SIGNED_F64_EPSILON = -F64_EPSILON;
    f64 F64_ONE_EPSILON = 1.0 - F64_EPSILON;
    f64 SIGNED_F64_ONE_EPSILON = -F64_ONE_EPSILON;

    u8 NULL_TERMINATOR = '\0';
    u8 NULL_TERMINATOR_LEN = 1;

    // https://en.wikipedia.org/wiki/Whitespace_character
    u8 CHAR_TAB = 0x09;
    u8 LINE_FEED = 0x0A;
    u8 LINE_TAB = 0x0B;
    u8 FORM_FEED = 0x0C;
    u8 CARRIAGE_RETURN = 0x0D;
    u8 SPACE = 0x20;
    u8 NEXT_LINE = 0x85;
    u8 NO_BREAK_SPACE = 0xA0;

    // f => -12345.7890 => 11
    f32 MAX_F32_FOR_FULL_REP = 99999.9999f;
    u64 SIGN_CHAR_CT = 1;
    u64 F32_DELIM_CHAR_CT = 1;
    u64 F32_STR_CHAR_CT = 9 + SIGN_CHAR_CT + F32_DELIM_CHAR_CT;
    u64 PARENTHESES_ENCAP_LEN = 2;
    u64 COMMA_SPACE_LEN = 2;

    MAY_INLINE std::filesystem::path GetDesktopPath()
    {
        wchar_t* p;
        if (S_OK != SHGetKnownFolderPath(FOLDERID_Desktop, 0, NULL, &p)) return "";
        std::filesystem::path result = p;
        CoTaskMemFree(p);
        return result;
    }
    MAY_INLINE std::string GetDesktopPathStr() { return GetDesktopPath().string(); }
}
