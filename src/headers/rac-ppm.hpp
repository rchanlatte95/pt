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

    using namespace rac::color;
    using namespace rac::mth;

    cstr PPM_EXT = ".ppm";
    u32 HEIGHT = WIN_PAGE_SIZE;
    u32 WIDTH = HEIGHT;
    class alignas(WIN_PAGE_SIZE) PortablePixelMap
    {
    public:
        mut_color pixels[HEIGHT][WIDTH];

        PortablePixelMap(u32 color_code = 0)
        {
            memset(pixels, color_code, sizeof(pixels));
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

            i32 PENULT_PG_SIZE = WIN_PAGE_SIZE - 1;
            rac::color::mut_color c;
            mut_u64 scanlines_done = 0;
            for (int y = 0; y < WIN_PAGE_SIZE; ++y)
            {
                for (int x = 0; x < PENULT_PG_SIZE; ++x)
                {
                    c = pixels[y][x];
                    fprintf(file, "(%3u, %3u, %3u) ", c.r, c.g, c.b);
                }
                c = pixels[y][PENULT_PG_SIZE];
                fprintf(file, "(%3u, %3u, %3u)\n", c.r, c.g, c.b);

                printf("%4llu / %4lu      \r", ++scanlines_done, WIN_PAGE_SIZE);
            }
            return std::filesystem::exists(desk_path);
        }
    };
}