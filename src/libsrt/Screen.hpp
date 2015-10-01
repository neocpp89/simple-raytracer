#ifndef SRT_SCREEN_HPP_ 
#define SRT_SCREEN_HPP_
#include <vector>
#include "Point3.hpp"
#include "Vector3.hpp"

namespace simple_raytracer {

/*
    This class contains the locations of points that we call the screen.

    It does not actually store any pixel data, nor does it specify where the
    camera is. Typically, you would use the camera origin and draw rays to
    each of the screen points, and these would be used as the initial rays.
    The return value of those rays would then be the color of a pixel in the
    resulting image.

    The divide by a possible zero makes me uneasy, I'll think about what to do
    with this later.
*/
class Screen
{
    public:
        Screen(
            const Point3 &top_left, const Point3 &top_right, const Point3 &bottom_left,
            int rows, int columns) :
            top_left_(top_left), top_right_(top_right), bottom_left_(bottom_left),
            rows_(rows), columns_(columns),
            dx_((top_right_ - top_left_) / static_cast<double>(columns - 1)),
            dy_((bottom_left_ - top_left_) / static_cast<double>(rows - 1)) {}
        int rows() const { return rows_; }
        int columns() const { return columns_; }

        /*
            GetPoint checks its arguments for validity. If out of range,
            GetPoint returns a {0, 0, 0} point.
        */
        Point3 GetPoint(int i, int j) const;

    private:
        Point3 top_left_;
        Point3 top_right_;
        Point3 bottom_left_;
        int rows_;
        int columns_;
        Vector3 dx_;
        Vector3 dy_;
};

} // namespace simple_raytracer

#endif //SRT_SCREEN_HPP_
