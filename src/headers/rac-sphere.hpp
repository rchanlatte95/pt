#pragma once
#include "rac-v3.hpp"
#include "rac-color.hpp"

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
        mut_Color color;
        mut_f32 radius;
        mut_v3 center;

        mut_sphere()
        {
            color = Color::PINK;
            radius = 1.0f;
            center = v3::ZERO;
        }
        mut_sphere(v3 center_pos, f32 radius_ = 1.0f)
        {
            color = Color::PINK;
            radius = radius_;
            center = center_pos;
        }
        mut_sphere(v3 center_pos, Color sphere_color, f32 r = 1.0f)
        {
            color = sphere_color;
            radius = r;
            center = center_pos;
        }

        INLINE v3 Normal(v3_ref pt_on_sphere) const noexcept
        {
            return (pt_on_sphere - center) / radius;
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

        MAY_INLINE bool Hit(ray_ref raycast) const noexcept
        {
            v3 oc = center - raycast.origin;
            f32 a = raycast.direction.SqrMag();
            f32 h = Dot(raycast.direction, oc);
            f32 c = oc.SqrMag() - radius * radius;
            f32 discrim = h * h - a * c;
            return discrim >= F32_EPSILON;
        }

        MAY_INLINE bool Hit(ray_ref raycast, mut_rayhit_ref hit_info) const noexcept
        {
            v3 oc = center - raycast.origin;
            f32 a = raycast.direction.SqrMag();
            f32 h = Dot(raycast.direction, oc);
            f32 c = oc.SqrMag() - radius * radius;

            f32 discrim = h * h - a * c;
            bool missed = discrim < F32_EPSILON;
            if (missed)
            {
                return false;
            }

            f32 sqrt_discrim = std::sqrtf(discrim);
            f32 root_1 = (h - sqrt_discrim) / a;
            if (root_1 <= 0.0f || root_1 )
            hit_info.pos = raycast.At((h - std::sqrtf(discrim)) / a);
            hit_info.normal = Normal(hit_info.pos);

            return true;
        }
    };
}