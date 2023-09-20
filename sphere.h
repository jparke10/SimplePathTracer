#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class Sphere : public Hittable {
    private:
        Point3 center;
        double radius;
    public:
        Sphere(Point3 _center, double _radius) : center(_center), radius(_radius) {}

        bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const override {
            Vec3 oc = r.origin() - center;
            auto a = r.direction().length_squared();
            auto half_b = dot(oc, r.direction());
            auto c = oc.length_squared() - radius * radius;
            auto quadratic = half_b * half_b - a * c;
            if (quadratic < 0) return false;
            auto sqrtq = sqrt(quadratic);
            // find the nearest root in [tmin, tmax] (pos or neg)
            auto root = (-half_b - sqrtq) / a;
            if (!ray_t.surrounds(root)) {
                auto root = (-half_b + sqrtq) / a;
                if (!ray_t.surrounds(root))
                    return false;
            }
            rec.t = root;
            rec.p = r.at(rec.t);
            Vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            return true;
        }
};

#endif