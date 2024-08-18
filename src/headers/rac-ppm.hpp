#pragma once
#include "rac-color.hpp"
#include "rac-v2.hpp"

namespace rac::img
{
    using namespace rac::color;
    using namespace rac::mth;

    class alignas(WIN_PAGE_SIZE) PortablePixelMap
    {
    public:
        mut_color pixels[WIN_PAGE_SIZE][WIN_PAGE_SIZE];

        public bool SaveToDesktop()
        {

        }
    };

    typedef PortablePixelMap mut_ppm;
    typedef PortablePixelMap* mut_ppm_ptr;
    typedef PortablePixelMap& mut_ppm_ref;
    typedef const PortablePixelMap ppm;
    typedef const PortablePixelMap* ppm_ptr;
    typedef const PortablePixelMap& ppm_ref;
}