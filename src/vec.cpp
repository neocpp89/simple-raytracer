#include "vec.h"
#include <cmath>

vec_t *v(double x1, double x2, double x3)
{
	vec_t *nv = new vec_t;
	nv->x1 = x1;
	nv->x2 = x2;
	nv->x3 = x3;
	return nv;
}

void vnormalize(vec_t *v)
{
	double m = sqrt(VDOT(v,v));
	double s;

	if (m == 0) {
		return;
	}

	s = 1/m;

	VSMULT(v,v,s);

	return;
}

vec_t *vreflection(vec_t *v, vec_t *sn)
{
	vec_t *r = new vec_t;
	double f = 2*VDOT(v, sn);
	VSMULT(r, sn, f);
	VSUB(r, v, r);
	
	return r;
}

