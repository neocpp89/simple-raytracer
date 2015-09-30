#include "light.h"

const double lambertian_factor(vec_t *light_dir, vec_t *sn)
{
	const double f = VDOT(light_dir, sn);

	if (f < 0) {
		return 0;
	}

	return f;
}
