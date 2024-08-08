#pragma once
#include "rac.hpp"

namespace rac::img
{
    class alignas(WIN_PAGE_SIZE) PortablePixelMap
    {

    };

    typedef PortablePixelMap mut_ppm;
    typedef PortablePixelMap* mut_ppm_ptr;
    typedef PortablePixelMap& mut_ppm_ref;
    typedef const PortablePixelMap ppm;
    typedef const PortablePixelMap* ppm_ptr;
    typedef const PortablePixelMap& ppm_ref;
}