#include "headers/rac-ppm.hpp"

namespace rac::img
{
    static u32 PPM_FMT_STR_LEN = sizeof("xxx, xxx, xxx ");
    static u32 _AREA = _WIDTH * _HEIGHT;
    static u32 PPM_FILE_SZ = _AREA * (PPM_FMT_STR_LEN + 1);
    PortablePixelMap::PortablePixelMap()
    {
        memset(pixels, 0, sizeof(pixels));
    }
    PortablePixelMap::PortablePixelMap(u8 color_component_value)
    {
        memset(pixels, color_component_value, sizeof(pixels));
    }
    PortablePixelMap::PortablePixelMap(Color color_code)
    {
        u32 code = color_code.GetU32();
        mut_i32ptr p = (mut_i32ptr)pixels;
        mut_i64 ct = (i64)(HEIGHT * WIDTH) >> 3;
        while (--ct > -1)
        {
            _mm256_set1_epi32(code);
            p += 8;
        }
    }

    INLINE u32 PortablePixelMap::ByteCount() const noexcept
    {
        return sizeof(pixels);
    }
    INLINE u32 PortablePixelMap::PixelCount() const noexcept
    {
        return HEIGHT * WIDTH;
    }
    INLINE mut_Color_ref PortablePixelMap::operator()(i32 x, i32 y) noexcept
    {
        return pixels[y][x];
    }
    INLINE mut_Color_ref PortablePixelMap::operator[](i32 index) noexcept
    {
        return ((mut_Color_ptr)pixels)[index];
    }

    MAY_INLINE void PortablePixelMap::Fill(Color color_code) const noexcept
    {
        u32 code = color_code.GetU32();
        mut_i32ptr p = (mut_i32ptr)pixels;
        mut_i64 ct = (i64)(HEIGHT * WIDTH) >> 3;
        while (--ct > -1)
        {
            _mm256_set1_epi32(code);
            p += 8;
        }
    }

    MAY_INLINE FileSaveResult PortablePixelMap::SaveToDesktop(cstr filename, std::string& desktop_path) const noexcept
    {
        desktop_path = rac::GetDesktopPathStr() + '\\' + filename + PPM_EXT;

        mut_FilePtr file;
        cstr desk_path_cstr = desktop_path.c_str();
        errno_t open_res = fopen_s(&file, desk_path_cstr, "w+");
        if (WIN_FAILED(open_res) || file == nullptr)
        {
            return FileSaveResult(false);
        }

        // ensures result is of the right byte size before mmap
        errno_t resize_res = SetFileSize(file, PPM_FILE_SZ);
        if (WIN_FAILED(resize_res))
        {
            return FileSaveResult(false);
        }

        ptr mmap_file = MapMem(file, PPM_FILE_SZ, 0);

        if (mmap_file == nullptr)
        {
            return FileSaveResult(false);
        }

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

        FileSaveResult saveResult = FileSaveResult(std::filesystem::exists(desktop_path));

        bool unmap_failed = UnmapMem(mmap_file) == false;
        if (unmap_failed)
        {
            printf("\r\n\t*** WARNING: Failed to unmap memory!\r\n");
        }

        return saveResult;
    }

    MAY_INLINE void PortablePixelMap::DrawSquare(i32 center_x, i32 center_y, Color_ref quad_color, i32 width) noexcept
    {
        mut_u32 topleft_x = center_x - width;
        mut_u32 topleft_y = center_y - width;
        for (mut_i32 y = 0;
            y < width && topleft_y < HEIGHT && topleft_y > 0;
            ++y, ++topleft_y)
        {
            for (mut_i32 x = 0, curr_x = topleft_x;
                x < width && topleft_x < WIDTH && topleft_x > 0;
                ++x, ++curr_x)
            {
                pixels[topleft_y][curr_x] = quad_color;
            }
        }
    }

    INLINE ptr PortablePixelMap::ToPtr() const noexcept
    {
        return (ptr)pixels;
    }
    INLINE Color_ptr PortablePixelMap::Begin() const noexcept
    {
        return (Color_ptr)pixels;
    }
    INLINE Color_ptr PortablePixelMap::End() const noexcept
    {
        u32 offset = (HEIGHT * WIDTH) - 1u;
        return (Color_ptr)(pixels + offset);
    }
    INLINE Color PortablePixelMap::First() const noexcept
    {
        return pixels[0][0];
    }
    INLINE Color PortablePixelMap::Last() const noexcept
    {
        return pixels[HEIGHT - 1][WIDTH - 1];
    }

    INLINE bool operator==(ppm_ref lhs, ppm_ref rhs)
    {
        return memcmp(lhs.pixels, rhs.pixels, sizeof(lhs.pixels)) == 0;
    }
    INLINE bool operator!=(ppm_ref lhs, ppm_ref rhs)
    {
        return !(lhs == rhs);
    }

    cstr PortablePixelMap::PPM_EXT = ".ppm";
    u32 PortablePixelMap::HEIGHT = 1024;
    u32 PortablePixelMap::WIDTH = HEIGHT;
    f32 PortablePixelMap::INV_HEIGHT = 1.0f / (f32)HEIGHT;
    f32 PortablePixelMap::INV_WIDTH = 1.0f / (f32)WIDTH;
    f32 PortablePixelMap::ASPECT_RATIO = (f32)WIDTH / (f32)HEIGHT;
}