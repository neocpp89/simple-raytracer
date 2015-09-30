#include "light.h"

double lambertian_factor(const vec_t *light_dir, const vec_t *sn)
{
	const double f = VDOT(light_dir, sn);

	if (f < 0) {
		return 0;
	}

	return f;
}

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
