#pragma once
#include "rac-color.hpp"
#include "rac-v2.hpp"
#include "rac-winmem.hpp"

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
    using namespace rac::mem::windows;

    static u32 PPM_FMT_STR_LEN = sizeof("xxx, xxx, xxx ");
    static u32 _HEIGHT = 1024;
    static u32 _WIDTH = _HEIGHT;
    static u32 _AREA = _WIDTH * _HEIGHT;
    static u32 PPM_FILE_SZ = _AREA * (PPM_FMT_STR_LEN + 1);
    class alignas(AVX256_ALIGNMENT_BYTE_SIZE) PortablePixelMap
    {
    public:
        static cstr PPM_EXT;
        static u32 HEIGHT;
        static u32 WIDTH;
        static f32 INV_HEIGHT;
        static f32 INV_WIDTH;
        static f32 ASPECT_RATIO;

        mut_Color pixels[_HEIGHT][_WIDTH];

        PortablePixelMap(u8 color_component_value = 0)
        {
            memset(pixels, color_component_value, sizeof(pixels));
        }
        PortablePixelMap(Color color_code)
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
        INLINE mut_Color_ref operator()(i32 x, i32 y) noexcept
        {
            return pixels[y][x];
        }
        INLINE mut_Color_ref operator[](i32 index) noexcept
        {
            return ((mut_Color_ptr)pixels)[index];
        }

        MAY_INLINE void Fill(Color color_code) const noexcept
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

            mut_FilePtr file;
            cstr desk_path_cstr = desk_path.c_str();
            errno_t open_res = fopen_s(&file, desk_path_cstr, "w+");
            if (WIN_FAILED(open_res) || file == nullptr)
            {
                return false;
            }

            // ensures result is of the right byte size before mmap
            errno_t resize_res = SetFileSize(file, PPM_FILE_SZ);
            if (WIN_FAILED(resize_res))
            {
                return false;
            }

            //dst = mmap(0, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fdout, 0)) == (caddr_t)-1;

            fprintf(file, "P3\n%lu %lu\n255\n", WIDTH, HEIGHT);

            u32 PENULT_WIDTH = WIDTH - 1;
            mut_u64 scanlines_done = 0;
            f32 invScanlineCt = 100.0f / (f32)HEIGHT;

            u64 SCANLINE_BUFFER_MAX = (PPM_FMT_STR_LEN * (u64)_WIDTH) + 1;
            mut_cstr BUFFER_HEAD;
            char SCANLINE_BUFFER[SCANLINE_BUFFER_MAX];
            for (mut_u32 y = 0; y < HEIGHT; ++y)
            {
                BUFFER_HEAD = SCANLINE_BUFFER;
                for (mut_u32 x = 0; x < PENULT_WIDTH; ++x)
                {
                    BUFFER_HEAD += snprintf(BUFFER_HEAD, PPM_FMT_STR_LEN, "%u, %u, %u ",
                                                                        pixels[y][x].r,
                                                                        pixels[y][x].g,
                                                                        pixels[y][x].b);
                }
                BUFFER_HEAD += snprintf(BUFFER_HEAD, PPM_FMT_STR_LEN, "%u, %u, %u\n",
                                                                    pixels[y][PENULT_WIDTH].r,
                                                                    pixels[y][PENULT_WIDTH].g,
                                                                    pixels[y][PENULT_WIDTH].b);
                *BUFFER_HEAD = NULL_TERMINATOR;
                fprintf(file, "%s", SCANLINE_BUFFER);

                f32 pct_done = (f32)(++scanlines_done) * invScanlineCt;
                printf("\r\tSERIALIZING:\t%4llu / %4lu scanlines (%.2f%% SERIALIZED).          ", scanlines_done, HEIGHT, pct_done);
            }

            bool saved_successfully = std::filesystem::exists(desk_path);
            if (saved_successfully)
            {
                printf("\r\n\tPath tracer result saved to: %s\r\n", desk_path_cstr);
            }
            else
            {
                printf("\r\n\tPath tracer result unable to save to: %s\r\n", desk_path_cstr);
            }

            return saved_successfully;
        }

        INLINE ptr ToPtr() const noexcept { return (ptr)pixels; }
        INLINE Color_ptr Begin() const noexcept
        {
            return (Color_ptr)pixels;
        }
        INLINE Color_ptr End() const noexcept
        {
            u32 offset = (HEIGHT * WIDTH) - 1u;
            return (Color_ptr)(pixels + offset);
        }
        INLINE Color First() const noexcept
        {
            return pixels[0][0];
        }
        INLINE Color Last() const noexcept
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
    f32 PortablePixelMap::INV_HEIGHT = 1.0f / (f32)HEIGHT;
    f32 PortablePixelMap::INV_WIDTH = 1.0f / (f32)WIDTH;
    f32 PortablePixelMap::ASPECT_RATIO = (f32)WIDTH / (f32)HEIGHT;
}