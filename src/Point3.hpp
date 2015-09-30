#ifndef SRT_POINT3_HPP_
#define SRT_POINT3_HPP_
#include <iostream>
#include <string>
#include <cmath>

#include "Vector3.hpp"

namespace SimpleRaytracer {

/*
    3D Point class.
*/
class Point3
{
    public:
        /*
            Constructors
        */
        Point3(double x, double y, double z) : x_(x), y_(y), z_(z) { return; }

        /*
            Accessors/Mutators
        */
        inline double x() const { return x_; }
        inline double y() const { return y_; }
        inline double z() const { return z_; }
        inline void set_x(const double x) { x_ = x; }
        inline void set_y(const double y) { y_ = y; }
        inline void set_z(const double z) { z_ = z; }

        /*
            Operators.
        */
        bool operator==(const Point3 &rhs) const
        {
            const Point3 &lhs = *this;
            if (lhs.x_ != rhs.x_) {
                return false;
            }
            if (lhs.y_ != rhs.y_) {
                return false;
            }
            if (lhs.z_ != rhs.z_) {
                return false;
            }
            return true;
        }
        bool operator!=(const Point3 &rhs) const
        {
            const Point3 &lhs = *this;
            return !(lhs == rhs);
        }

    private:
        double x_;
        double y_;
        double z_;

};


/*
    Use operators for unambiguous operations.

    Addition of a point and a vector is a point.
    Subtraction of two points is a vector.

    None of the other operations really make sense.
*/
inline Point3 operator+(const Point3 &lhs, const Vector3 &rhs)
{
    return Point3(lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z());
}
inline Vector3 operator-(const Point3 &lhs, const Point3 &rhs)
{
    return Vector3(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z());
}

inline std::ostream &operator<<(std::ostream &os, const Point3 &point)
{
    os << point.x() << ' ';
    os << point.y() << ' ';
    os << point.z();
    return os;
}

} // namespace SimpleRaytracer

#endif // SRT_POINT3_HPP_
