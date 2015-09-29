#include "light.h"

double lambertian_factor(vec_t *light_dir, vec_t *sn)
{
	double f = VDOT(light_dir, sn);

	if (f < 0) {
		return 0;
	}

	return f;
}
