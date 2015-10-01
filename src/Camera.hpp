#ifndef SRT_CAMERA_HPP_ 
#define SRT_CAMERA_HPP_
#include <vector>
#include "Point3.hpp"
#include "Vector3.hpp"

namespace simple_raytracer {

/*
    The camera class doesn't do very much right now, it's basically just
    another point. I have plans to expand this later though.
*/
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
