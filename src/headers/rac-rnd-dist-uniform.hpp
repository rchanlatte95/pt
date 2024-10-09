#pragma once
#include "rac-packedtypes.hpp"

namespace rac::rnd::SplitMix
{
    class mut_SmRng;
    typedef mut_SmRng* mut_SmRng_ptr;
    typedef mut_SmRng& mut_SmRng_ref;
    typedef const mut_SmRng SmRng;
    typedef const mut_SmRng* SmRng_ptr;
    typedef const mut_SmRng& SmRng_ref;

    class mut_SmRng
    {
    public:
    };
}