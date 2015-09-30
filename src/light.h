#ifndef SRT_LIGHT_HPP_
#define SRT_LIGHT_HPP_
#include "Color.hpp"
#include "Point3.hpp"
#include "Vector3.hpp"
#include "vec.h"

typedef struct light_s {
	vec_t *origin;
	vec_t *color; /* RGB values from 0-255. */
	double intensity; /* Value from 0.0-1.0. */
} light_t;

double lambertian_factor(const vec_t *light_dir, const vec_t *sn);

namespace SimpleRaytracer {

double lambertian_factor(const Vector3 &light_direction, const Vector3 &surface_normal);

/*
    The generic class for a light in the scene.

    All lights should derive from this.
*/
class SceneLight
{
    public:
        SceneLight(const Point3 &origin, const RGBColor &rgb, const double intensity) :
            origin_(origin), rgb_(rgb), intensity_(intensity) {}
        virtual ~SceneLight() {}

        virtual Vector3 direction_to_light(const Point3 &from) const = 0;

        Point3 origin() const { return origin_; }
        RGBColor rgb() const { return rgb_; }
        double intensity() const { return intensity_; }

    private:
        Point3 origin_;
        RGBColor rgb_;
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
        ScenePointLight(const Point3 &origin, const RGBColor &rgb, const double intensity) :
            SceneLight(origin, rgb, intensity) {}
        Vector3 direction_to_light(const Point3 &from) const;

    private:

};

} // namespace SimpleRaytracer

#endif // SRT_LIGHT_HPP_
