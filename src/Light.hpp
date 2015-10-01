#ifndef SRT_LIGHT_HPP_
#define SRT_LIGHT_HPP_
#include "Color.hpp"
#include "Point3.hpp"
#include "Vector3.hpp"

namespace simple_raytracer {

double LambertianFactor(const Vector3 &light_direction, const Vector3 &surface_normal);

/*
    The generic class for a light in the scene.

    All lights should derive from this.
*/
class SceneLight
{
    public:
        SceneLight(const Point3 &origin, const RGBColor &color, const double intensity) :
            origin_(origin), color_(color), intensity_(intensity) {}
        virtual ~SceneLight() {}

        virtual Vector3 DirectionToLight(const Point3 &from) const = 0;

        Point3 origin() const { return origin_; }
        RGBColor color() const { return color_; }
        double intensity() const { return intensity_; }

    private:
        Point3 origin_;
        RGBColor color_;
        double intensity_;
};

/*
    I've only implemented point light sources. I have to think about how to do
    it for area/object lights.
*/
class ScenePointLight : public SceneLight
{
    public:
        ScenePointLight(const SceneLight &sl) : SceneLight(sl) {}
        ScenePointLight(const Point3 &origin, const RGBColor &color, const double intensity) :
            SceneLight(origin, color, intensity) {}
        Vector3 DirectionToLight(const Point3 &from) const;

    private:

};

} // namespace simple_raytracer

#endif // SRT_LIGHT_HPP_
