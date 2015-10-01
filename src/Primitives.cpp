#include <iostream>
#include "Primitives.hpp"

namespace simple_raytracer {

/*
    Simple collision detection of a ray and a sphere.

    Basically, we know the vector between the origin and the center of
    the sphere. Since we know the direction the ray is travelling,
    we can also figure which point is closest to the center of the
    sphere at any given scalar multiple of the direction.

    If this time is nonimaginary, we are either inside the sphere, or
    we are hitting it from the outside. If the time is negative, we are
    inside the sphere.
*/
Intersection Sphere::Intersect(const Ray &ray) const
{
    const Point3 origin = ray.origin();
    const Vector3 direction = ray.direction();

    const Vector3 vp = origin - center_;
    const double a = direction.Dot(direction);
    const double b = 2*direction.Dot(vp);
    const double c = vp.Dot(vp) - radius_*radius_;

    const double discriminant = b*b - 4*a*c;
    bool hit = true;

    if ((a == 0) || (discriminant < 0)) {
        hit = false;
        return Intersection(hit);
    }

    const double sd = sqrt(discriminant);
    double t = (-b - sd) / (2*a);

    /*
        At some point I was going to use the fact that we could be inside an
        object, but I never got around to it.
    */
    // bool inside = false;

    if (t < 0) {
        t = (2 * c) / (-b - sd);
        // inside = true;
    }

    if (t < 0) {
        hit = false;
        return Intersection(hit);
    }

    hit = true;
    Point3 point = origin + (t * direction);
    const double s = 1.0/radius_;
    Vector3 surface_normal = s * (point - center_);

    return Intersection(hit, t, point, surface_normal);
}

} // namespace simple_raytracer
