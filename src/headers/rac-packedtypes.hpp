#pragma once
#include "rac.hpp"

namespace rac
{
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


    // Packed Types that have floating point data
    struct pf32
    {
        union
        {
            p32 packed;

            mut_f32 float32;
        };
    };

    struct pf64
    {
        union
        {
            p32 packed32[sizeof(p64) / sizeof(p32)];
            p64 packed64;

            mut_f32 float32[sizeof(p64) / sizeof(f32)];
            mut_f64 float64;
        };
    };

    struct pf128
    {
        union
        {
            p32 packed32[sizeof(__m128) / sizeof(p32)];
            p64 packed64[sizeof(__m128) / sizeof(p64)];
            p128 packed128;

            pf32 packedf32[sizeof(__m128) / sizeof(pf32)];
            pf64 packedf64[sizeof(__m128) / sizeof(pf64)];

            mut_f32 float32[sizeof(__m128) / sizeof(f32)];
            mut_f64 float64[sizeof(__m128) / sizeof(f64)];

            __m128 f128;
        };
    };

    struct pf256
    {
        union
        {
            p32 packed32[sizeof(__m256) / sizeof(p32)];
            p64 packed64[sizeof(__m256) / sizeof(p64)];
            p128 packed128[sizeof(__m256) / sizeof(p128)];

            pf32 packedf32[sizeof(__m256) / sizeof(pf32)];
            pf64 packedf64[sizeof(__m256) / sizeof(pf64)];
            pf128 packedf128[sizeof(__m256) / sizeof(pf128)];

            mut_f32 float32[sizeof(__m256) / sizeof(f32)];
            mut_f64 float64[sizeof(__m256) / sizeof(f64)];

            __m128 f128[sizeof(__m256) / sizeof(__m128)];
            __m256 f256;
        };
    };
}
