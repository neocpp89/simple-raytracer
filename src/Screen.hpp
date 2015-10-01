#ifndef SRT_SCREEN_HPP_ 
#define SRT_SCREEN_HPP_
#include <vector>
#include "Point3.hpp"

namespace simple_raytracer {

/*
    This class contains the locations of points that we call the screen.

    It does not actually store any pixel data, nor does it specify where the
    camera is. Typically, you would use the camera origin and draw rays to
    each of the screen points, and these would be used as the initial rays.
    The return value of those rays would then be the color of a pixel in the
    resulting image.
*/
class Screen
{
    public:
        Screen(
            const Point3 &top_left, const Point3 &top_right, const Point3 &bottom_left,
            int rows, int columns) :
            top_left_(top_left), top_right_(top_right), bottom_left_(bottom_left),
            rows_(rows), columns_(columns), point_array_(rows*columns, {0, 0, 0})
        {
            GeneratePoints();
        }
        int rows() const { return rows_; }
        int columns() const { return columns_; }

        /*
            SetPoint and GetPoint check their arguments for
            validity. SetPoint doesn't do anything if out of range,
            while GetPoint returns a {0, 0, 0} point.
        */
        void SetPoint(int i, int j, const Point3 &point);
        Point3 GetPoint(int i, int j) const;

    private:
        const Point3 top_left_;
        const Point3 top_right_;
        const Point3 bottom_left_;
        const int rows_;
        const int columns_;
        std::vector<Point3> point_array_;

        void GeneratePoints();
};

} // namespace simple_raytracer

#endif //SRT_SCREEN_HPP_
