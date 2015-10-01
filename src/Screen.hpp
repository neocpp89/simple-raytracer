#ifndef SRT_SCREEN_HPP_ 
#define SRT_SCREEN_HPP_
#include <vector>
#include "Point3.hpp"

namespace simple_raytracer {

class Screen
{
    public:
        Screen(
            const Point3 &top_left, const Point3 &top_right, const Point3 &bottom_left,
            int rows, int columns) :
            top_left_(top_left), top_right_(top_right), bottom_left_(bottom_left),
            rows_(rows), columns_(columns), point_array_(rows*columns, {0, 0, 0})
        {
            generate_points_();
        }
        int rows() const { return rows_; }
        int columns() const { return columns_; }

        void set_point(int i, int j, const Point3 &point);
        Point3 get_point(int i, int j) const;

    private:
        const Point3 top_left_;
        const Point3 top_right_;
        const Point3 bottom_left_;
        const int rows_;
        const int columns_;
        std::vector<Point3> point_array_;

        void generate_points_();
};

} // namespace simple_raytracer

#endif //SRT_SCREEN_HPP_
