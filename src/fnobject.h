#ifndef __FNOBJECT_H__
#define __FNOBJECT_H__

#include "vec.h"

#define FNSPHERE	1
#define FNPLANE		2
#define FNIMPLICIT	3

typedef struct common_object_properties_s {
} common_object_properties_t;

typedef struct sphere_s {
	double radius;
	vec_t *origin;
} sphere_t;

typedef struct plane_s {
	vec_t *normal;
	double distance;
} plane_t;

typedef struct implicit_s {
	double bounding_radius;
	double (*fn)(double x, double y, double z);
	double (*gradx)(double x, double y, double z);
	double (*grady)(double x, double y, double z);
	double (*gradz)(double x, double y, double z);
	double scale;
	vec_t *origin;
} implicit_t;

typedef struct fnobject_s {
	union object_s {
		sphere_t *sphere;
		plane_t *plane;
		implicit_t *implicit;
	} object;
	int type;

	/*
		Common properties below.
	*/
	vec_t *color; /* RGB values from 0-255. */
	double lambertian;
	double reflectivity;
} fnobject_t;

#endif