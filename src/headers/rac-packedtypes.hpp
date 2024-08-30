#pragma once
#include "rac.hpp"

namespace rac
{
    /*
    typedef void* mut_ptr;
    typedef const void* ptr;

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
    */

    static i32 HIGH = 0;
    static i32 LOW = 1;

    struct p16
    {
        union
        {
            mut_i8 bytes[sizeof(u16)];
            mut_i16 int16;

            mut_u8 ubytes[sizeof(u16)];
            mut_u16 uint16;
        };
    };

    struct p32
    {
        union
        {
            mut_i8 bytes[sizeof(u32)];
            mut_i16 int16[sizeof(u32) / sizeof(u16)];
            mut_i32 int32;

            mut_u8 ubytes[sizeof(u32)];
            mut_u16 uint16[sizeof(u32) / sizeof(u16)];
            mut_u32 uint32;

            p16 packed16[sizeof(u32) / sizeof(p16)];
        };
    };

    struct p64
    {
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

            p16 packed16[sizeof(u64) / sizeof(p16)];
            p32 packed32[sizeof(u64) / sizeof(p32)];
        };
    };

    struct p128
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

            __m128i simd128;

            p16 packed16[sizeof(__m128i) / sizeof(p16)];
            p32 packed32[sizeof(__m128i) / sizeof(p32)];
            p64 packed64[sizeof(__m128i) / sizeof(p64)];
        };
    };

    struct p256
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

            __m128i simd128[sizeof(__m256i) / sizeof(__m128i)];
            __m256i simd256;

            p16 packed16[sizeof(__m256i) / sizeof(p16)];
            p32 packed32[sizeof(__m256i) / sizeof(p32)];
            p64 packed64[sizeof(__m256i) / sizeof(p64)];
            p64 packed128[sizeof(__m256i) / sizeof(p128)];
        };
    };
}
