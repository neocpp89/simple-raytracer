#ifndef __SCENE_H__
#define __SCENE_H__

#include "fnobject.h"
#include "light.h"
#include "ray.h"

typedef struct scene_s {
	int nobjects;
	int nlights;
	fnobject_t **objects;
	light_t **lights;

	int screenx;
	int screeny;
	vec_t *camera;
	vec_t *screen_origin;
	vec_t ***screenrays;

	double ambient;
} scene_t;

vec_t ***screenrays_precomp(vec_t *screen_origin, vec_t *camera_origin, int resx, int resy, double zoom);
scene_t *scene_init(int x, int y, double zoom);

#endif
