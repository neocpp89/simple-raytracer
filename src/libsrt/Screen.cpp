#include "Screen.hpp"
#include "Vector3.hpp"

namespace simple_raytracer {

void Screen::SetPoint(int i, int j, const Point3 &point)
{
    if (i < 0 || i >= rows_ || j < 0 || j >= columns_) {
        return;
    }
    point_array_[i * columns_ + j] = point;
    return;
}

Point3 Screen::GetPoint(int i, int j) const
{
    if (i < 0 || i >= rows_ || j < 0 || j >= columns_) {
        return Point3(0,0,0);
    }
    return point_array_[i * columns_ + j];
}

void Screen::GeneratePoints()
{
    auto dx = top_right_ - top_left_;
    auto dy = bottom_left_ - top_left_;

    dx *= 1.0 / static_cast<double>(columns_ - 1);
    dy *= 1.0 / static_cast<double>(rows_ - 1);

    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < columns_; j++) {
            SetPoint(i, j, top_left_ + i*dy + j*dx);
        }
    }
    return;
}

} // namespace simple_raytracer
