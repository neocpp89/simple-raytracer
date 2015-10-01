#ifndef SRT_PRIMITIVES_HPP_ 
#define SRT_PRIMITIVES_HPP_
#include "Color.hpp"
#include "Point3.hpp"
#include "Vector3.hpp"
#include "Ray.hpp"

namespace simple_raytracer {

/*
    Contains the necessary information regarding an intersection, such as if
    a hit even occured in the first place, the time (scaling of a unit
    direction vector), point of intersection, and surface normal at that point.
*/
class Intersection
{
    public:
        Intersection(bool hit = false)
            : hit_(hit), time_(0), point_({0,0,0}), surface_normal_({0,0,0}) {} 
        Intersection(bool hit, double time, const Point3 &point, const Vector3 &surface_normal)
            : hit_(hit), time_(time), point_(point), surface_normal_(surface_normal) {}
        bool hit() const { return hit_; }
        double time() const { return time_; }
        Point3 point() const { return point_; }
        Vector3 surface_normal() const { return surface_normal_; }

    private:
        bool hit_;
        double time_;
        Point3 point_;
        Vector3 surface_normal_;
};

/*
    Contains any interesting properties scene objects should have, such as
    color, reflectivity, and lambertian lighting factor.
*/
class MaterialProperties
{
    public:
        MaterialProperties(const RGBColor &color, double lambertian, double reflectivity)
            : color_(color), lambertian_(lambertian), reflectivity_(reflectivity) {}
        RGBColor color() const { return color_; }
        double lambertian() const { return lambertian_; }
        double reflectivity() const { return reflectivity_; }

    private:
        RGBColor color_;
        double lambertian_;
        double reflectivity_;
};

/*
    Generic scene object from which everything we draw should descend.
*/
class SceneObject
{
    public:
        SceneObject(const MaterialProperties &properties) : properties_(properties) {}
        virtual ~SceneObject() {}
        MaterialProperties properties() const { return properties_; }

        /*
            This is important: the direction should be normalized before
            the intersection code is called.
        */
        virtual Intersection Intersect(const Ray &ray) const = 0;

    private:
        MaterialProperties properties_;
};

/*
    The classic, and very simple to calculate.

    An idea for more complex shapes, inherit from the Sphere and compute a
    bounding sphere for a cheaper intersection test.
*/
class Sphere : public SceneObject
{
    public:
        Sphere(const Point3 &center, double radius, const MaterialProperties &properties)
            : SceneObject(properties), center_(center), radius_(radius) {}

        Intersection Intersect(const Ray &ray) const;

    private:
        Point3 center_;
        double radius_;
};

/*
    Another classic object, and also simple to calculate.

    The definition is a bit strange compared to what is normally done.

    The plane is defined by a unit normal and a distance from the origin.
    This is where the plane would be if you followed the unit vector BACK
    from the origin.

    So a plane which is facing upwards on Z (0,1,0) with a distance of 100
    is 100 units BELOW the origin. If the distance is -100, it still faces
    upwards, but is now 100 units ABOVE the origin.
*/
class Plane : public SceneObject
{
    public:
        Plane(const Vector3 &normal, double distance_from_origin, const MaterialProperties &properties)
            : SceneObject(properties), normal_(normal),
            distance_from_origin_(distance_from_origin) {}

        Intersection Intersect(const Ray &ray) const;

    private:
        Vector3 normal_;
        double distance_from_origin_;
};

} // namespace simple_raytracer

#endif //SRT_PRIMITIVES_HPP_
