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

        MAY_INLINE bool Hit(ray_ref raycast) const noexcept
        {
            v3 oc = center - raycast.origin;
            f32 a = Dot(raycast.direction, raycast.direction);
            f32 b = -2.0f * Dot(raycast.direction, oc);
            f32 c = Dot(oc, oc) - radius * radius;
            return (b * b - 4.0f * a * c) >= F32_EPSILON;
        }

        MAY_INLINE bool Hit(ray_ref raycast, mut_v3_ref hit_pt) const noexcept
        {
            v3 oc = center - raycast.origin;
            f32 a = Dot(raycast.direction, raycast.direction);
            f32 b = -2.0f * Dot(raycast.direction, oc);
            f32 c = Dot(oc, oc) - radius * radius;

            f32 discrim = (b * b - 4.0f * a * c);
            bool hit = discrim >= F32_EPSILON;
            if (hit)
            {
                hit_pt = raycast.at((-b - std::sqrtf(discrim)) / (2.0f * a));
            }
            return hit;
        }

        INLINE Color NormalColor(v3_ref normal) const noexcept
        {
            v3 offset_normal = (normal + v3::ONE) * 0.5f;
            return Color(offset_normal.x, offset_normal.y, offset_normal.z, 1.0f);
        }

        INLINE v3 Normal(v3_ref pt_on_sphere) const noexcept
        {
            return (pt_on_sphere - center).Norm();
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