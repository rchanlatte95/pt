#pragma once
#include "rac-color.hpp"
#include "rac-v2.hpp"

namespace rac::img
{
    class alignas(WIN_PAGE_SIZE) PortablePixelMap;
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
    class alignas(WIN_PAGE_SIZE) PortablePixelMap
    {
    public:
        mut_color pixels[HEIGHT][WIDTH];

        PortablePixelMap() { memset(pixels, 0, sizeof(pixels)); }

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
            u64 code = color_code.GetU32();
            u64 packed_code = (code << 32) | code;
            mut_u64ptr pxl = (mut_u64ptr)pixels;
            for (mut_u64 i = 0, ct = (HEIGHT * WIDTH) >> 1; i < ct; ++i)
            {
                *pxl++ = packed_code;
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
    };
}