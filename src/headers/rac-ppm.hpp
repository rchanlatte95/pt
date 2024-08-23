#pragma once
#include "rac-color.hpp"
#include "rac-v2.hpp"

namespace rac::img
{
    class alignas(AVX256_ALIGNMENT_BYTE_SIZE) PortablePixelMap;
    typedef PortablePixelMap mut_ppm;
    typedef PortablePixelMap* mut_ppm_ptr;
    typedef PortablePixelMap& mut_ppm_ref;
    typedef const PortablePixelMap ppm;
    typedef const PortablePixelMap* ppm_ptr;
    typedef const PortablePixelMap& ppm_ref;

    using namespace rac::gfx;
    using namespace rac::mth;

    static u32 _HEIGHT = 1024;
    static u32 _WIDTH = _HEIGHT;
    class alignas(AVX256_ALIGNMENT_BYTE_SIZE) PortablePixelMap
    {
    public:
        static cstr PPM_EXT;
        static u32 HEIGHT;
        static u32 WIDTH;

        mut_color pixels[_HEIGHT][_WIDTH];

        PortablePixelMap(u8 color_component_value = 0)
        {
            memset(pixels, color_component_value, sizeof(pixels));
        }
        PortablePixelMap(color color_code)
        {
            u32 code = color_code.GetU32();
            i32 MASK = 0xFFFFFFFF;
            const __m256i code_vec = _mm256_set_epi32(code, code, code, code, code, code, code, code);
            const __m256i MASK_VEC = _mm256_set_epi32(MASK, MASK, MASK, MASK, MASK, MASK, MASK, MASK);

            mut_i32ptr p = (mut_i32ptr)pixels;
            mut_i64 ct = (i64)(HEIGHT * WIDTH) >> 3;
            while (--ct > -1)
            {
                _mm256_maskstore_epi32(p, MASK_VEC, code_vec);
                p += 8;
            }
        }

        INLINE u32 ByteCount() const noexcept { return sizeof(pixels); }
        INLINE u32 PixelCount() const noexcept { return HEIGHT * WIDTH; }
        INLINE mut_color_ref operator()(i32 x, i32 y) noexcept
        {
            return pixels[y][x];
        }
        INLINE mut_color_ref operator[](i32 index) noexcept
        {
            return ((mut_color_ptr)pixels)[index];
        }

        MAY_INLINE void Fill(color color_code) const noexcept
        {
            u32 code = color_code.GetU32();
            i32 MASK = 0xFFFFFFFF;
            const __m256i code_vec = _mm256_set_epi32(code, code, code, code, code, code, code, code);
            const __m256i MASK_VEC = _mm256_set_epi32(MASK, MASK, MASK, MASK, MASK, MASK, MASK, MASK);

            mut_i32ptr p = (mut_i32ptr)pixels;
            mut_i64 ct = (i64)(HEIGHT * WIDTH) >> 3;
            while (--ct > -1)
            {
                _mm256_maskstore_epi32(p, MASK_VEC, code_vec);
                p += 8;
            }
        }

        MAY_INLINE bool SaveToDesktop(cstr filename) const noexcept
        {
            std::string desk_path = rac::GetDesktopPathStr() + '\\' + filename + PPM_EXT;

            mut_FileHandle file;
            cstr desk_path_cstr = desk_path.c_str();
            errno_t open_result = fopen_s(&file, desk_path_cstr, "w+");
            if (open_result == EINVAL || file == nullptr)
            {
                return false;
            }

            fprintf(file, "P3\n%lu %lu\n255\n", WIDTH, HEIGHT);

            u32 PENULT_WIDTH = WIDTH - 1;
            mut_color c;
            mut_u64 scanlines_done = 0;
            f32 invScanlineCt = 100.0f / (f32)HEIGHT;
            for (mut_u32 y = 0; y < HEIGHT; ++y)
            {
                for (mut_u32 x = 0; x < PENULT_WIDTH; ++x)
                {
                    c = pixels[y][x];
                    fprintf(file, "%u, %u, %u ", c.r, c.g, c.b);
                }
                c = pixels[y][PENULT_WIDTH];
                fprintf(file, "%u, %u, %u\n", c.r, c.g, c.b);

                f32 pct_done = (f32)(++scanlines_done) * invScanlineCt;
                printf("\r\tSERIALIZING:\t%4llu / %4lu scanlines (%.2f%% SERIALIZED).          ", scanlines_done, HEIGHT, pct_done);
            }

            bool saved_successfully = std::filesystem::exists(desk_path);
            if (saved_successfully)
            {
                printf("\r\n\tPath tracer result saved to: %s\r\n\r\n", desk_path_cstr);
            }
            else
            {
                printf("\r\n\tPath tracer result unable to save to: %s\r\n\r\n", desk_path_cstr);
            }

            return saved_successfully;
        }

        INLINE ptr ToPtr() const noexcept { return (ptr)pixels; }
        INLINE color_ptr Begin() const noexcept
        {
            return (color_ptr)pixels;
        }
        INLINE color_ptr End() const noexcept
        {
            u32 offset = (HEIGHT * WIDTH) - 1u;
            return (color_ptr)(pixels + offset);
        }
        INLINE color First() const noexcept
        {
            return pixels[0][0];
        }
        INLINE color Last() const noexcept
        {
            return pixels[HEIGHT - 1][WIDTH - 1];
        }

    };

    INLINE bool operator==(ppm_ref lhs, ppm_ref rhs)
    {
        return memcmp(lhs.pixels, rhs.pixels, sizeof(lhs.pixels)) == 0;
    }
    INLINE bool operator!=(ppm_ref lhs, ppm_ref rhs)
    {
        return !(lhs==rhs);
    }

    cstr PortablePixelMap::PPM_EXT = ".ppm";
    u32 PortablePixelMap::HEIGHT = 1024;
    u32 PortablePixelMap::WIDTH = HEIGHT;
}