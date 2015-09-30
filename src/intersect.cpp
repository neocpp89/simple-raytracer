#include <cmath>
#include <cstdio>

#include "intersect.h"

#include "Point3.hpp"
#include "Vector3.hpp"

#define MIN(x,y) (x > y)?(y):(x)
#define MAX(x,y) (x > y)?(x):(y)

void intersect_sphere(intersection_t *result, ray_t *ray, sphere_t *sphere);
void intersect_plane(intersection_t *result, ray_t *ray, plane_t *plane);
void intersect_implict_function(intersection_t *result, ray_t *ray, implicit_t *implicit);

void intersect_all_objects(intersection_t *result, ray_t *ray, scene_t *scene)
{
    int i;
    intersection_t r;
    r.p = v(0,0,0);
    r.sn = v(0,0,0);

    result->t = -1;
    result->hit = 0;
    for (i = 0; i < scene->nobjects; i++) {
        intersect_object(&r, ray, scene->objects[i]);
        if ((r.hit == 1) && (r.t < result->t || result->t == -1)) {
            result->t = r.t;
            result->hit = 1;
            result->inside = r.inside;
            VDUP2(result->p, r.p);
            VDUP2(result->sn, r.sn);
            result->object_index = i;
        }
    }

    delete r.p;
    delete r.sn;

    return;
}

void intersect_object(intersection_t *result, ray_t *ray, fnobject_t *obj)
{
    if (obj->type == FNSPHERE) {
        intersect_sphere(result, ray, obj->object.sphere);
    } else if (obj->type == FNPLANE) {
        intersect_plane(result, ray, obj->object.plane);
    } else if (obj->type == FNIMPLICIT) {
        intersect_implict_function(result, ray, obj->object.implicit);
    }

    return;
}

void intersect_sphere(intersection_t *result, ray_t *ray, sphere_t *sphere)
{
    const SimpleRaytracer::Point3 origin(ray->origin->x1, ray->origin->x2, ray->origin->x3);
    const SimpleRaytracer::Vector3 direction(ray->direction->x1, ray->direction->x2, ray->direction->x3);
    const SimpleRaytracer::Point3 center(sphere->origin->x1, sphere->origin->x2, sphere->origin->x3);
    const auto vp = origin - center;
    const double a = direction.dot(direction);
    const double b = 2*direction.dot(vp);
    const double c = vp.dot(vp) - sphere->radius*sphere->radius;

    const double discriminant = b*b - 4*a*c;

    if ((a == 0) || (discriminant < 0)) {
        result->hit = 0;
        return;
    }

    const double sd = sqrt(discriminant);
    double t = (-b - sd) / (2*a);
    result->inside = 0;

    if (t < 0) {
        t = (2 * c) / (-b - sd);
        result->inside = 1;
    }

    if (t < 0) {
        result->hit = 0;
        return;
    }

    result->hit = 1;
    result->t = t;
    SimpleRaytracer::Point3 point = origin + (t * direction);
    const double s = 1.0/((double)sphere->radius);
    SimpleRaytracer::Vector3 surface_normal = s * (point - center);

    result->p->x1 = point.x();
    result->p->x2 = point.y();
    result->p->x3 = point.z();

    result->sn->x1 = surface_normal.x();
    result->sn->x2 = surface_normal.y();
    result->sn->x3 = surface_normal.z();

    return;
}

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

void intersect_implict_function(intersection_t *result, ray_t *ray, implicit_t *implicit)
{
    sphere_t s;
    double t;
    double lb, ub;
    vec_t v;
    vec_t *vp = &v;

    s.origin = implicit->origin;
    s.radius = implicit->bounding_radius;

    result->hit = 0;
    intersect_sphere(result, ray, &s);

    /*
        Did not hit bounding sphere, avoid numerical root finding.
    */
    if (result->hit != 1) {
        return;
    }

    lb = result->t;
    ub = result->t + 2 * implicit->bounding_radius;
    t = -1;

    if (t < 0) {
        result->hit = 0;
        return;
    }

    result->hit = 1;
    result->t = t;
    VSMULT(vp, ray->direction, t);
    VADD(result->p, ray->origin, vp);
    VDUP2(result->sn, implicit->origin);
    vnormalize(result->sn);
    /*
        Have some fun perturbing the normal vector.
    */
    //VDUP2(result->sn, plane->normal);
    //result->sn->x1 += sin((1.0/20)*(result->p->x1 + result->p->x3));
    //result->sn->x3 += cos((1.0/20)*(result->p->x1 + result->p->x3));
    //vnormalize(result->sn);

    return;
}
