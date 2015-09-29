#ifndef SRT_VECTOR3_HPP_
#define SRT_VECTOR3_HPP_
#include <iostream>
#include <string>
#include <cmath>

namespace SimpleRaytracer {

/*
    3D Vector class.
*/
class Vector3
{
    public:
        /*
            Constructors
        */
        Vector3(double x, double y, double z) : x_(x), y_(y), z_(z) { return; }

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
            Functions.
        */
        double magnitude() const
        {
            return std::sqrt(this->dot(*this));
        }
        void normalize()
        {
            const double m = magnitude();
            // Zero vector will NOT be normalized.
            if (m != 0) {
                (*this) /= m;
            }
            return;
        }

        /*
            Operators.
        */
        bool operator==(const Vector3 &rhs) const
        {
            const Vector3 &lhs = *this;
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
        bool operator!=(const Vector3 &rhs) const
        {
            const Vector3 &lhs = *this;
            return !(lhs == rhs);
        }
        Vector3 &operator+=(const Vector3 &rhs)
        {
            Vector3 &lhs = *this;
            lhs.x_ += rhs.x_;
            lhs.y_ += rhs.y_;
            lhs.z_ += rhs.z_;
            return lhs;
        }
        Vector3 &operator-=(const Vector3 &rhs)
        {
            Vector3 &lhs = *this;
            lhs.x_ -= rhs.x_;
            lhs.y_ -= rhs.y_;
            lhs.z_ -= rhs.z_;
            return lhs;
        }
        Vector3 &operator*=(const double rhs)
        {
            Vector3 &lhs = *this;
            lhs.x_ *= rhs;
            lhs.y_ *= rhs;
            lhs.z_ *= rhs;
            return lhs;
        }
        Vector3 &operator/=(const double rhs)
        {
            Vector3 &lhs = *this;
            lhs.x_ /= rhs;
            lhs.y_ /= rhs;
            lhs.z_ /= rhs;
            return lhs;
        }

        // inner product of two vectors
        inline double dot(const Vector3 &rhs) const
        {
            return (x_*rhs.x() + y_*rhs.y() + z_*rhs.z());
        }

        // cross product of two vectors
        inline Vector3 cross(const Vector3 &rhs) const
        {
            const Vector3 &lhs = *this;
            const double x = (lhs.y_ * rhs.z_) - (lhs.z_ * rhs.y_);
            const double y = (-lhs.x_ * rhs.z_) + (lhs.z_ * rhs.x_);
            const double z = (lhs.x_ * rhs.y_) - (lhs.y_ * rhs.x_);
            
            return Vector3(x, y, z);
        }

    private:
        double x_;
        double y_;
        double z_;

};


/*
    Use operators for unambiguous operations.

    Specifically, note the we don't use the * for dot product, since the cross
    product is also a multiplication operation. Call a.dot(b) or a.cross(b)
    explicitly.
*/
inline Vector3 operator+(Vector3 lhs, const Vector3 &rhs) //copy LHS
{
    return (lhs += rhs);
}
inline Vector3 operator-(Vector3 lhs, const Vector3 &rhs) //copy LHS
{
    return (lhs -= rhs);
}
inline Vector3 operator*(Vector3 lhs, const double rhs) //copy LHS
{
    return (lhs *= rhs);
}
inline Vector3 operator/(Vector3 lhs, const double rhs) //copy LHS
{
    return (lhs /= rhs);
}

inline Vector3 operator*(const double lhs, Vector3 rhs) //flip order
{
    return (rhs *= lhs);
}

inline std::ostream &operator<<(std::ostream &os, const Vector3 &vector)
{
    os << vector.x() << ' ';
    os << vector.y() << ' ';
    os << vector.z();
    return os;
}

} // namespace SimpleRaytracer

#endif // SRT_VECTOR3_HPP_
