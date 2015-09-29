#ifndef __VEC_H__
#define __VEC_H__

typedef struct vec_s {
	double x1;
	double x2;
	double x3;
} vec_t;

vec_t *v(double x1, double x2, double x3);
void vnormalize(vec_t *v);
vec_t *vreflection(vec_t *v, vec_t *sn);

#define VDUP(a) (v(a->x1, a->x2, a->x3))
#define VDUP2(r,a) VSMULT(r,a,1)
#define VCOPY(r,a) \
	(r)->x1 = (a)->x1; \
	(r)->x2 = (a)->x2; \
	(r)->x3 = (a)->x3;
#define VDOT(a,b) ((a)->x1*(b)->x1 + (a)->x2*(b)->x2 + (a)->x3*(b)->x3)
#define VSMULT(r,a,s) \
	(r)->x1 = (s)*(a)->x1; \
	(r)->x2 = (s)*(a)->x2; \
	(r)->x3 = (s)*(a)->x3;
#define VEMULT(r,a,b) \
	(r)->x1 = (b)->x1*(a)->x1; \
	(r)->x2 = (b)->x2*(a)->x2; \
	(r)->x3 = (b)->x3*(a)->x3;
#define VADD(r,a,b) \
	(r)->x1 = (a)->x1 + (b)->x1; \
	(r)->x2 = (a)->x2 + (b)->x2; \
	(r)->x3 = (a)->x3 + (b)->x3;
#define VSUB(r,a,b) \
	(r)->x1 = (a)->x1 - (b)->x1; \
	(r)->x2 = (a)->x2 - (b)->x2; \
	(r)->x3 = (a)->x3 - (b)->x3;

#endif
