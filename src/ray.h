#ifndef __RAY_H__
#define __RAY_H__

#include "vec.h"

typedef struct ray_s {
	vec_t *origin;
	vec_t *direction;
} ray_t;

ray_t *ray(vec_t *origin, vec_t *direction);


#endif