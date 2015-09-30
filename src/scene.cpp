#include "Scene.hpp"
#include <cstdlib>

//<3 functions
double hfn(double x, double y, double z);
double hgradx(double x, double y, double z);
double hgrady(double x, double y, double z);
double hgradz(double x, double y, double z);

double hfn(double x, double y, double z)
{
	double s = (2*z*z + x*x + y*y - 1);
	return (s*s*s + z*z*y*y*y/10 + x*x*y*y*y);
}

double hgradx(double x, double y, double z)
{
	double s = (x*x + y*y + 2*z*z - 1);
	return (6*x*s*s + 2*x*y*y*y);
}

double hgrady(double x, double y, double z)
{
	double s = (x*x + y*y + 2*z*z - 1);
	return (6*y*s*s + 3*x*x*y*y + 3*z*z*y*y/10);
}

double hgradz(double x, double y, double z)
{
	double s = (x*x + y*y + 2*z*z - 1);
	return (12*z*s*s + z*y*y*y/5);
}

vec_t ***screenrays_precomp(vec_t *screen_origin, vec_t *camera_origin, int resx, int resy, double zoom)
{
	vec_t ***s;
	int i, j;
	double nx, ny;

	s = new vec_t **[resx];
	for (i = 0; i < resx; i++) {
		s[i] = new vec_t *[resy];
	}

	for (i = 0 ; i < resx; i++) {
		for (j = 0; j < resy; j++) {
			nx = rand()/RAND_MAX;
			ny = rand()/RAND_MAX;
			s[i][j] = v((1.0f/zoom)*(nx + i - resx/2.0f), (1.0f/zoom)*(ny - j + resy/2.0f), 0);
			VADD(s[i][j], s[i][j], screen_origin);
			VSUB(s[i][j], s[i][j], camera_origin);
			vnormalize(s[i][j]);
		}
	}

	return s;
}

/*
	Not a generic function, setup specifically for a scene we want to render.
*/
scene_t *scene_init(int x, int y, double zoom)
{
	int i;
	scene_t *s = new scene_t;

	s->camera = v(0, 0, -1000);
	s->screen_origin = v(0, 0, 0);
	s->screenx = x;
	s->screeny = y;
	s->screenrays = screenrays_precomp(s->screen_origin, s->camera, s->screenx, s->screeny, zoom);


	s->nlights = 3;
	s->nobjects = 7;
	s->lights = new light_t *[s->nlights];
	s->objects = new fnobject_t *[s->nobjects];

	i = 0;
	s->lights[i] = new light_t;
	s->lights[i]->origin = v(0, 0, 0);
	s->lights[i]->color = v(0xff, 0xff, 0xff);
	s->lights[i]->intensity = 1.0;
	i++;

	s->lights[i] = new light_t;
	s->lights[i]->origin = v(500, 1000, 0);
	//s->lights[i]->origin = v(300, 150, 0);
	s->lights[i]->color = v(0xff, 0xff, 0xff);
	s->lights[i]->intensity = 1.0;
	i++;

	s->lights[i] = new light_t;
	s->lights[i]->origin = v(1000, 500, 0);
	//s->lights[i]->origin = v(200, 150, 0);
	s->lights[i]->color = v(0xff, 0xff, 0xff);
	s->lights[i]->intensity = 1.0;
	i++;

	s->nlights = i;
	s->ambient = 0.05;

	i = 0;
	s->objects[i] = new fnobject_t;
	s->objects[i]->type = FNSPHERE;
	s->objects[i]->lambertian = 0.3;
	s->objects[i]->reflectivity = 0.7;
	s->objects[i]->color = v(0x20, 0x20, 0xf0);
	s->objects[i]->object.sphere = new sphere_t;
	s->objects[i]->object.sphere->origin = v(-100, 0, 100);
	s->objects[i]->object.sphere->radius = 75;
	i++;

	s->objects[i] = new fnobject_t;
	s->objects[i]->type = FNSPHERE;
	s->objects[i]->lambertian = 0.7;
	s->objects[i]->reflectivity = 0.3;
	s->objects[i]->color = v(0xf0, 0x20, 0x20);
	s->objects[i]->object.sphere = new sphere_t;
	s->objects[i]->object.sphere->origin = v(100, 0, 100);
	s->objects[i]->object.sphere->radius = 75;
	i++;

    /*
	s->objects[i] = new fnobject_t;
	s->objects[i]->type = FNSPHERE;
	s->objects[i]->lambertian = 0.1;
	s->objects[i]->reflectivity = 0.9;
	s->objects[i]->color = v(0x20, 0xf0, 0x20);
	s->objects[i]->object.sphere = new sphere_t;
	s->objects[i]->object.sphere->origin = v(0, 50, 50);
	s->objects[i]->object.sphere->radius = 25;
	i++;
    */

	s->objects[i] = new fnobject_t;
	s->objects[i]->type = FNSPHERE;
	s->objects[i]->lambertian = 0.1;
	s->objects[i]->reflectivity = 0.9;
	s->objects[i]->color = v(0xf0, 0xf0, 0x20);
	s->objects[i]->object.sphere = new sphere_t;
	s->objects[i]->object.sphere->origin = v(-200, 50, 50);
	s->objects[i]->object.sphere->radius = 25;
	i++;

	s->objects[i] = new fnobject_t;
	s->objects[i]->type = FNSPHERE;
	s->objects[i]->lambertian = 0.1;
	s->objects[i]->reflectivity = 0.9;
	s->objects[i]->color = v(0x20, 0x20, 0x20);
	s->objects[i]->object.sphere = new sphere_t;
	s->objects[i]->object.sphere->origin = v(200, 50, 50);
	s->objects[i]->object.sphere->radius = 25;
	i++;

	s->objects[i] = new fnobject_t;
	s->objects[i]->type = FNPLANE;
	s->objects[i]->lambertian = 0.4;
	s->objects[i]->reflectivity = 0.6;
	s->objects[i]->color = v(128, 77, 180);
	//s->objects[i]->color = v(77, 180, 128);
	//s->objects[i]->color = v(38, 90, 64);
	s->objects[i]->object.plane = new plane_t;
	s->objects[i]->object.plane->normal = v(0, 1, 0);
	s->objects[i]->object.plane->distance = 100;
	i++;

	s->objects[i] = new fnobject_t;
	s->objects[i]->type = FNIMPLICIT;
	s->objects[i]->lambertian = 0.1;
	s->objects[i]->reflectivity = 0.9;
	s->objects[i]->color = v(0x20, 0x20, 0x20);
	s->objects[i]->object.implicit = new implicit_t;
	s->objects[i]->object.implicit->origin = v(0, 50, 50);
	s->objects[i]->object.implicit->scale = 20;
	s->objects[i]->object.implicit->bounding_radius= 1.5 * s->objects[i]->object.implicit->scale;
	s->objects[i]->object.implicit->fn = &hfn;
	s->objects[i]->object.implicit->gradx = &hgradx;
	s->objects[i]->object.implicit->grady = &hgrady;
	s->objects[i]->object.implicit->gradz = &hgradz;
	i++;

	s->nobjects = i;

	/*
	s->objects[i] = new fnobject_t;
	s->objects[i]->type = FNPLANE;
	s->objects[i]->lambertian = 0.3;
	s->objects[i]->reflectivity = 0.7;
	s->objects[i]->specularity = 0.7;
	s->objects[i]->color = v(38, 90, 64);
	s->objects[i]->object.plane = new plane_t;
	s->objects[i]->object.plane->normal = v(0, -1, 0);
	s->objects[i]->object.plane->distance = 200;

	i++;
	s->objects[i] = new fnobject_t;
	s->objects[i]->type = FNPLANE;
	s->objects[i]->lambertian = 0.3;
	s->objects[i]->reflectivity = 0.7;
	s->objects[i]->specularity = 0.7;
	s->objects[i]->color = v(38, 90, 64);
	s->objects[i]->object.plane = new plane_t;
	s->objects[i]->object.plane->normal = v(1, 0, 0);
	s->objects[i]->object.plane->distance = 400;

	i++;
	s->objects[i] = new fnobject_t;
	s->objects[i]->type = FNPLANE;
	s->objects[i]->lambertian = 0.3;
	s->objects[i]->reflectivity = 0.7;
	s->objects[i]->specularity = 0.7;
	s->objects[i]->color = v(38, 90, 64);
	s->objects[i]->object.plane = new plane_t;
	s->objects[i]->object.plane->normal = v(-1, 0, 0);
	s->objects[i]->object.plane->distance = 400;

	i++;
	s->objects[i] = new fnobject_t;
	s->objects[i]->type = FNPLANE;
	s->objects[i]->lambertian = 0.3;
	s->objects[i]->reflectivity = 0.7;
	s->objects[i]->specularity = 0.7;
	s->objects[i]->color = v(38, 90, 64);
	s->objects[i]->object.plane = new plane_t;
	s->objects[i]->object.plane->normal = v(0, 0, -1);
	s->objects[i]->object.plane->distance = 400;*/

	/*srand(0x01);

	for (i = 6; i < s->nobjects; i++) {
		s->objects[i] = new fnobject_t;
		s->objects[i]->type = FNSPHERE;
		s->objects[i]->lambertian = 0.1;
		s->objects[i]->reflectivity = 0.9;
		s->objects[i]->specularity = 0.9;
		s->objects[i]->color = v(0xf0, 0xf0, 0xf0);
		s->objects[i]->object.sphere = new sphere_t;
		s->objects[i]->object.sphere->origin = v(rand() % 1000 - 300 , rand() % 384 + 50, 100);
		s->objects[i]->object.sphere->radius = rand() % 30 + 20;
	}*/

	return s;
}

namespace SimpleRaytracer {

int Scene::indexof(int i, int j) const
{
    if (i <= 0 || i >= screen_.rows() || j <= 0 || j >= screen_.columns()) {
        return 0;
    }
    return (i * screen_.columns() + j);
}

} // namespace SimpleRaytracer
