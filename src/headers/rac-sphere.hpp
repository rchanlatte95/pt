#pragma once
#include "rac-v3.hpp"
#include "rac-color.hpp"
#include "rac-ray.hpp"

namespace rac::gfx::primitives
{
    using namespace mth;

    class mut_sphere;
    typedef mut_sphere* mut_sphere_ptr;
    typedef mut_sphere& mut_sphere_ref;
    typedef const mut_sphere sphere;
    typedef const mut_sphere* sphere_ptr;
    typedef const mut_sphere& sphere_ref;
    class mut_sphere
    {
    public:
        mut_color color;
        mut_f32 radius;
        mut_v3 center;

        mut_sphere()
        {
            color = color::PINK;
            radius = 1.0f;
            center = v3::ZERO;
        }
        mut_sphere(v3 pos, f32 radius_ = 1.0f)
        {
            color = color::PINK;
            radius = radius_;
            center = pos;
        }
        mut_sphere(v3 pos, const mut_color sphere_color, f32 radius_ = 1.0f)
        {
            color = sphere_color;
            radius = radius_;
            center = pos;
        }

        MAY_INLINE bool RayHit(ray_ref raycast) const noexcept
        {
            v3 oc = center - raycast.origin;
            f32 a = Dot(raycast.direction, raycast.direction);
            f32 b = -2.0f * Dot(raycast.direction, oc);
            f32 c = Dot(oc, oc) - radius * radius;
            return (b * b - 4.0f * a * c) >= F32_EPSILON;
        }

        INLINE bool Inside(v3_ref pt_to_test) const noexcept
        {
            return Dot(pt_to_test, pt_to_test) < F32_EPSILON;
        }

        INLINE bool Outside(v3_ref pt_to_test) const noexcept
        {
            return !Inside(pt_to_test);
        }

        INLINE bool OnSurface(v3_ref pt_to_test) const noexcept
        {
            return Dot(pt_to_test, pt_to_test) == radius;
        }
    };
}