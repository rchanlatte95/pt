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

    cstr PPM_EXT = ".ppm";
    u32 HEIGHT = 1024;
    u32 WIDTH = HEIGHT;
    class alignas(AVX256_ALIGNMENT_BYTE_SIZE) PortablePixelMap
    {
    public:
        mut_color pixels[HEIGHT][WIDTH];

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
            mut_i64 ct = (HEIGHT * WIDTH) >> 3;
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

        MAY_INLINE void Fill(color color_code) noexcept
        {
            u32 code = color_code.GetU32();
            i32 MASK = 0xFFFFFFFF;
            const __m256i code_vec = _mm256_set_epi32(code, code, code, code, code, code, code, code);
            const __m256i MASK_VEC = _mm256_set_epi32(MASK, MASK, MASK, MASK, MASK, MASK, MASK, MASK);

            mut_i32ptr p = (mut_i32ptr)pixels;
            mut_i64 ct = (HEIGHT * WIDTH) >> 3;
            while (--ct > -1)
            {
                _mm256_maskstore_epi32(p, MASK_VEC, code_vec);
                p += 8;
            }
        }

        MAY_INLINE bool SaveToDesktop(cstr filename) const noexcept
        {
            std::string desk_path = rac::GetDesktopPathStr() + '/' + filename + PPM_EXT;

            mut_FileHandle file;
            errno_t open_result = fopen_s(&file, desk_path.c_str(), "w+");
            if (open_result == EINVAL || file == nullptr)
            {
                return false;
            }

            fprintf(file, "P3\n%lu %lu\n255\n", WIDTH, HEIGHT);

            i32 PENULT_WIDTH = WIDTH - 1;
            mut_color c;
            mut_u64 scanlines_done = 0;
            for (int y = 0; y < HEIGHT; ++y)
            {
                for (int x = 0; x < PENULT_WIDTH; ++x)
                {
                    c = pixels[y][x];
                    fprintf(file, "%3u, %3u, %3u ", c.r, c.g, c.b);
                }
                c = pixels[y][PENULT_WIDTH];
                fprintf(file, "%3u, %3u, %3u\n", c.r, c.g, c.b);

                printf("%4llu / %4lu      \r", ++scanlines_done, HEIGHT);
            }
            return std::filesystem::exists(desk_path);
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
}