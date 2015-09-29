#include "ray.h"

ray_t *ray(vec_t *origin, vec_t *direction)
{
	ray_t *r = new ray_t;
	r->origin = origin;
	r->direction = direction;

	return r;
}
