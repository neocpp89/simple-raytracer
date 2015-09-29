// 214rt.cpp : Defines the entry point for the console application.
//

#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>

#include "bitmap.hpp"
#include "intersect.h"
#include "scene.h"
#include <cmath>
#include <cassert>

#define MIN(x,y) (x > y)?(y):(x)
#define MAX(x,y) (x > y)?(x):(y)

using namespace std;

double delta = 0.00001;

void rt(vec_t *color, int depth, int mdepth, scene_t *scene, ray_t *sr);

void rt(vec_t *color, int depth, int mdepth, scene_t *scene, ray_t *sr)
{
	int i;
	intersection_t r;
	intersection_t rs;

	int imin;
	double tmin;

	double lam, ref;

	vec_t tmp_storage[5];

	vec_t *ip;
	vec_t *cv;
	vec_t *cvl;

	/*
		Saved intersection point and surface normal.
	*/
	vec_t *saved_point;
	vec_t *saved_surface_normal;

	/*
		For general lambertian lighting.
	*/
	vec_t *light_dir;
	double light_distance_sq;	//square of distance to light
	double lam_factor;
	double total_lam_factor;
	ray_t *shadow;

	/*
		For specular reflection.
	*/
	vec_t *reflected_light_dir;
	double spec_factor;

	/*
		For reflected rays.
	*/
	vec_t *reflected_dir;
	ray_t *reflect;

	vec_t rcolor;

	if (depth >= mdepth) {
		return;
	}

	tmin = -1;

	r.p = &tmp_storage[0];
	r.sn = &tmp_storage[1];
	rs.p = &tmp_storage[2];
	rs.sn = &tmp_storage[3];
	cvl = &tmp_storage[4];

	saved_point = v(0, 0, 0);
	saved_surface_normal = v(0, 0, 0);

	for (i = 0; i < scene->nobjects; i++) {
		intersect_object(&r, sr, scene->objects[i]);
		if (r.hit == 1) {
			if (r.t < tmin || tmin == -1) {
				tmin = r.t;
				VDUP2(saved_surface_normal, r.sn);
				VDUP2(saved_point, r.p);
				imin = i;
			}
		}
	}

	if (tmin != -1) {
		lam = scene->objects[imin]->lambertian;
		ref = scene->objects[imin]->reflectivity;
		cv = VDUP(scene->objects[imin]->color);

		ip = VDUP(saved_surface_normal);
		VSMULT(ip, ip, delta);
		VADD(ip, saved_point, ip);

		color->x1 += (scene->ambient * cv->x1);
		color->x2 += (scene->ambient * cv->x2);
		color->x3 += (scene->ambient * cv->x3);

		if (lam > 0) {
			total_lam_factor = 0;
			for (i = 0; i < scene->nlights; i++) {
				light_dir = VDUP(scene->lights[i]->origin);
				VSUB(light_dir, light_dir, ip);
				light_distance_sq = VDOT(light_dir, light_dir);
				vnormalize(light_dir);
				assert(abs(VDOT(light_dir, light_dir) - 1) < delta || abs(VDOT(light_dir, light_dir)) > delta);
				assert(abs(VDOT(saved_surface_normal, saved_surface_normal) - 1) < delta || abs(VDOT(saved_surface_normal, saved_surface_normal)) > delta);
				shadow = ray(ip, light_dir);

				lam_factor = lambertian_factor(light_dir, saved_surface_normal);
				if (lam_factor > 0) {
					intersect_all_objects(&rs, shadow, scene);
					if (rs.hit == 0 || (rs.t * rs.t >= light_distance_sq)) {
						total_lam_factor += lam_factor;
						if (ref > 0) {
							reflected_light_dir = vreflection(light_dir, saved_surface_normal);
							assert(abs(VDOT(reflected_light_dir, reflected_light_dir) - 1) < delta || abs(VDOT(reflected_light_dir, reflected_light_dir)) > delta);

							spec_factor = VDOT(reflected_light_dir, sr->direction);
							if (spec_factor > 0) {
								spec_factor = pow(spec_factor, 100*ref);
								spec_factor = spec_factor*ref*scene->lights[i]->intensity;
								VSMULT(cvl, scene->lights[i]->color, spec_factor);
								assert(cvl->x1 >= 0 && cvl->x2 >= 0 && cvl->x3 >= 0);
								color->x1 += (cvl->x1);
								color->x2 += (cvl->x2);
								color->x3 += (cvl->x3);
							}

							delete reflected_light_dir;
						}

					}
				}

				delete light_dir;
				delete shadow;
			}

			if (total_lam_factor > 0) {
				total_lam_factor *= lam;
				VSMULT(cvl, cv, total_lam_factor);
				assert(cvl->x1 >= 0 && cvl->x2 >= 0 && cvl->x3 >= 0);
				color->x1 += (cvl->x1);
				color->x2 += (cvl->x2);
				color->x3 += (cvl->x3);
			}
		}

		if (ref > 0) {
			reflected_dir = vreflection(sr->direction, saved_surface_normal);
			reflect = ray(ip, reflected_dir);
			rcolor.x1 = 0;
			rcolor.x2 = 0;
			rcolor.x3 = 0;
			rt(&rcolor, depth+1, mdepth, scene, reflect);
			color->x1 += ref*rcolor.x1;
			color->x2 += ref*rcolor.x2;
			color->x3 += ref*rcolor.x3;

			delete reflected_dir;
			delete reflect;
		}

		delete ip;
		delete cv;
	}

	delete saved_surface_normal;
	delete saved_point;

	return;
}

int main(int argc, char **argv)
{
	bitmap *bmp = new bitmap(3200, 2400);
	color *clr = new color();
	rgb_t *rgb = new rgb_t;
	vec_t rt_color;
	ray_t *sr;


	const int bx = bmp->getwidth();
	const int by = bmp->getheight();
	scene_t *scene = scene_init(bx, by, 8);

	const int total_pixels = (bx*by);

	for (int y = 0; y < by; y++) {
		for (int x = 0; x < bx; x++) {
			rt_color.x1 = 0;
			rt_color.x2 = 0;
			rt_color.x3 = 0;
			sr = ray(scene->camera, scene->screenrays[x][y]);
			rt(&rt_color, 0, 8, scene, sr);
			rgb->red = (int)(rt_color.x1);
			rgb->green = (int)(rt_color.x2);
			rgb->blue = (int)(rt_color.x3);
			if (rgb->red > 255) {
				rgb->red = 255;
			}
			if (rgb->green > 255) {
				rgb->green = 255;
			}
			if (rgb->blue > 255) {
				rgb->blue = 255;
			}
			clr->setrgb(rgb->red, rgb->green, rgb->blue);
			bmp->setpixel(x, y, clr);
			delete sr;
		}
		const int current_pixel = (bx*y + bx);
		printf("Completed %d of %d pixels.\t\t(%-6.4g%%)\r", current_pixel, total_pixels, ((double)100*current_pixel)/total_pixels);
	}
    printf("\n");

	bmp->writefile("output.bmp");

	delete rgb;
	delete clr;
	delete bmp;

	return 0;
}

