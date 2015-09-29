#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "vec.h"

typedef struct light_s {
	vec_t *origin;
	vec_t *color; /* RGB values from 0-255. */
	double intensity; /* Value from 0.0-1.0. */
} light_t;

double lambertian_factor(vec_t *light_dir, vec_t *sn);
double specular_factor(vec_t *light_dir, vec_t *sn);

#endif