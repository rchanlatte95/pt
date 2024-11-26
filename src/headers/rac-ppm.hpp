#pragma once
#include "rac-color.hpp"
#include "rac-v2.hpp"
#include "rac-winmem.hpp"
#include "rac-io.hpp"

namespace rac::img
{
    class alignas(AVX256_ALIGNMENT_BYTE_SIZE) PortablePixelMap;
    typedef PortablePixelMap mut_ppm;
    typedef PortablePixelMap* mut_ppm_ptr;
    typedef PortablePixelMap& mut_ppm_ref;
    typedef const PortablePixelMap ppm;
    typedef const PortablePixelMap* ppm_ptr;
    typedef const PortablePixelMap& ppm_ref;

    using namespace rac::io;
    using namespace rac::gfx;
    using namespace rac::mth;
    using namespace rac::mem::windows;

    static u32 _HEIGHT = 1024;
    static u32 _WIDTH = _HEIGHT;
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

        PortablePixelMap();
        PortablePixelMap(u8 color_component_value);
        PortablePixelMap(Color color_code);

        INLINE u32 ByteCount() const noexcept;
        INLINE u32 PixelCount() const noexcept;
        INLINE mut_Color_ref operator()(i32 x, i32 y) noexcept;
        INLINE mut_Color_ref operator[](i32 index) noexcept;

        MAY_INLINE void Fill(Color color_code) const noexcept;
        MAY_INLINE void DrawSquare(i32 center_x, i32 center_y, Color_ref quad_color, i32 width = 4) noexcept;
        MAY_INLINE FileSaveResult SaveToDesktop(cstr filename, std::string& desktop_path) const noexcept;

        INLINE ptr ToPtr() const noexcept;
        INLINE Color_ptr Begin() const noexcept;
        INLINE Color_ptr End() const noexcept;
        INLINE Color First() const noexcept;
        INLINE Color Last() const noexcept;
    };

    INLINE bool operator==(ppm_ref lhs, ppm_ref rhs);
    INLINE bool operator!=(ppm_ref lhs, ppm_ref rhs);
}