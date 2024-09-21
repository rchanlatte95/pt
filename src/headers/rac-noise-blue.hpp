#include "rac-rnd-xorshiftroatate.hpp"

namespace rac::noise::blue
{
    class mut_BlueNoise;
    typedef mut_BlueNoise* mut_BlueNoise_ptr;
    typedef mut_BlueNoise& mut_BlueNoise_ref;
    typedef const mut_BlueNoise BlueNoise;
    typedef const mut_BlueNoise* BlueNoise_ptr;
    typedef const mut_BlueNoise& BlueNoise_ref;

    u64 SAMPLE_CT = 32;

    /*
    The algorithm takes as input the extent of the sample domain in
    Rn, the minimum distance r between samples, and a constant k
    as the limit of samples to choose before rejection in the algorithm
    (typically k = 30).

        Step 0.) Initialize an n-dimensional background grid for storing
        samples and accelerating spatial searches. We pick the cell size to
        be bounded by r/√n, so that each grid cell will contain at most
        one sample, and thus the grid can be implemented as a simple n
        dimensional array of integers: the default −1 indicates no sample, a
        non-negative integer gives the index of the sample located in a cell.

        Step 1.) Select the initial sample, x_0, randomly chosen uniformly
        from the domain. Insert it into the background grid, and initialize
        the “active list” (an array of sample indices) with this index (zero).

        Step 2.) While the active list is not empty, choose a random index
        from it (say i). Generate up to k points chosen uniformly from the
        spherical annulus between radius r and 2r around xi. For each
        point in turn, check if it is within distance r of existing samples
        (using the background grid to only test nearby samples). If a point
        is adequately far from existing samples, emit it as the next sample
        and add it to the active list. If after k attempts no such point is
        found, instead remove i from the active list.
    */
    class mut_BlueNoise
    {
    public:
    };
}