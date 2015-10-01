#include "light.h"

namespace SimpleRaytracer {

double lambertian_factor(const Vector3 &light_direction, const Vector3 &surface_normal)
{
    double factor = light_direction.dot(surface_normal);
    if (factor < 0) {
        factor = 0;
    }
    return factor;
}

Vector3 ScenePointLight::direction_to_light(const Point3 &from) const
{
    Vector3 direction = origin() - from;
    direction.normalize();
    return direction;
}

} // namespace SimpleRaytracer
