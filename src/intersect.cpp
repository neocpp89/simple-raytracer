#if 0
/*
typedef struct plane_s {
	vec_t *normal;
	double distance;
} plane_t;
*/

void intersect_plane(intersection_t *result, ray_t *ray, plane_t *plane)
{
    double vd, v0, t;
    vec_t v;
    vec_t *vp = &v;

    vd = VDOT(plane->normal, ray->direction);
    if (vd == 0) {
        result->hit = 0;
        return;
    }

    v0 = -(VDOT(plane->normal, ray->origin) + plane->distance);
    t = v0/vd;

    if (t < 0) {
        result->hit = 0;
        return;
    }

    result->hit = 1;
    result->t = t;
    VSMULT(vp, ray->direction, t);
    VADD(result->p, ray->origin, vp);
    VDUP2(result->sn, plane->normal);
    /*
        Have some fun perturbing the normal vector.
    */
    //VDUP2(result->sn, plane->normal);
    //result->sn->x1 += sin((1.0/20)*(result->p->x1 + result->p->x3));
    //result->sn->x3 += cos((1.0/20)*(result->p->x1 + result->p->x3));
    //vnormalize(result->sn);

    return;
}
#endif

