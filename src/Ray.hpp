#ifndef SRT_RAY_HPP_
#define SRT_RAY_HPP_
#include "Point3.hpp"
#include "Vector3.hpp"

namespace SimpleRaytracer {

class Ray
{
    public:
        Ray(const Point3 &origin, const Vector3 &direction)
            : origin_(origin), direction_(direction) {}
        Point3 origin() const { return origin_; }
        Vector3 direction() const { return direction_; }
    private:
        const Point3 origin_;
        const Vector3 direction_;
};

} // namespace SimpleRaytracer

#endif //SRT_RAY_HPP_
