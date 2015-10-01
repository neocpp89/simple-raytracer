#include "Light.hpp"
#include "Point3.hpp"
#include "Vector3.hpp"

namespace simple_raytracer {

double LambertianFactor(const Vector3 &light_direction, const Vector3 &surface_normal)
{
    double factor = light_direction.Dot(surface_normal);
    if (factor < 0) {
        factor = 0;
    }
    return factor;
}

Vector3 ScenePointLight::DirectionToLight(const Point3 &from) const
{
    Vector3 direction = origin() - from;
    direction.Normalize();
    return direction;
}

} // namespace simple_raytracer
