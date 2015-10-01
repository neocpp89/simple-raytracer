#include "Screen.hpp"
#include "Vector3.hpp"

namespace simple_raytracer {

Point3 Screen::GetPoint(int i, int j) const
{
    if (i < 0 || i >= rows_ || j < 0 || j >= columns_) {
        return Point3(0,0,0);
    }
    return (top_left_ + i*dy_ + j*dx_);
}

} // namespace simple_raytracer
