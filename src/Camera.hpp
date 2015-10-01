#ifndef SRT_CAMERA_HPP_ 
#define SRT_CAMERA_HPP_
#include <vector>
#include "Point3.hpp"
#include "Vector3.hpp"

namespace simple_raytracer {

class Camera
{
    public:
        Camera(const Point3 &origin) : origin_(origin) {}
        Point3 origin() const { return origin_; }

    private:
        Point3 origin_;
};

} // namespace simple_raytracer

#endif //SRT_CAMERA_HPP_
