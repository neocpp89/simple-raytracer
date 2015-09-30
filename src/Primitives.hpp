#ifndef SRT_PRIMITIVES_HPP_ 
#define SRT_PRIMITIVES_HPP_

#include "Color.hpp"
#include "Point3.hpp"
#include "Vector3.hpp"
#include "Ray.hpp"

namespace SimpleRaytracer {

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
        const bool hit_;
        const double time_;
        const Point3 point_;
        const Vector3 surface_normal_;
};

class MaterialProperties
{
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
*/
class Sphere : public SceneObject
{
    public:
        Sphere(const Point3 &center, const double radius, const MaterialProperties &properties)
            : SceneObject(properties), center_(center), radius_(radius) {}
        Intersection Intersect(const Ray &ray) const;

    private:
        const Point3 center_;
        const double radius_;
};

} // namespace SimpleRaytracer

#endif //SRT_PRIMITIVES_HPP_
