#ifndef __INTERSECT_H__
#define __INTERSECT_H__

#include "fnobject.h"
#include "scene.h"
#include "ray.h"

typedef struct intersection_s {
	int hit;
	int inside;
	double t;
	vec_t *p;
	vec_t *sn;
	int object_index;
} intersection_t;

void intersect_all_objects(intersection_t *result, ray_t *ray, scene_t *scene);
void intersect_object(intersection_t *result, ray_t *ray, fnobject_t *obj);

#endif