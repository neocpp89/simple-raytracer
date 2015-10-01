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

constexpr double DELTA = 1e-6;

int Scene::indexof(int i, int j) const
{
    if (i <= 0 || i >= screen_.rows() || j <= 0 || j >= screen_.columns()) {
        return 0;
    }
    return (i * screen_.columns() + j);
}

/*
    Try to intersect the ray with all scene objects.

    Find the object which is closest to the camera, so we can bounce off that.
*/
Intersection Scene::find_closest_object_along_ray(const Ray &ray, size_t &index) const
{
    Intersection closest;
    size_t min_idx = 0;
	for (size_t i = 0; i < objects_.size(); i++) {
        auto const &object = objects_[i];
        auto intersection = object->intersect(ray);
        if (intersection.hit()) {
            if (closest.hit() == false || intersection.time() < closest.time()) {
                closest = intersection;
                min_idx = i;
            }
        }
	}
    index = min_idx;
    return closest;
}

void Scene::render(int max_depth)
{
    for (int i = 0; i < screen_.rows(); i++) {
        for (int j = 0; j < screen_.columns(); j++) {
            Vector3 direction = screen_.get_point(i, j) - camera_.origin();
            direction.normalize();
            Ray ray(screen_.get_point(i, j), direction);
            pixel_data_[indexof(i, j)] = render(ray, 0, max_depth);
        }
    }
    return;
}

RGBColor Scene::render(const Ray &ray, int depth, int max_depth) const
{
    /*
        Ray has bounced too many times, return the background color.
    */
    if (depth >= max_depth) {
        return properties_.bgcolor();
    }

    /*
        Find the closest object.

        If no objects are in the way, we just return the background color.
    */
    size_t min_idx = 0;
    auto closest = find_closest_object_along_ray(ray, min_idx);

    if (closest.hit() == false) {
        return properties_.bgcolor();
    }

    RGBColor rgb = properties_.bgcolor();
    const double lambertian = objects_[min_idx]->properties().lambertian();
    const double reflectivity = objects_[min_idx]->properties().reflectivity();
    RGBColor object_color = objects_[min_idx]->properties().color();

    /*
        Perturb the point slightly to lift it off the actual surface.

        We do this so the reflected ray doesn't immediately register a hit
        on the same object, but there's probably a smarter way to do this.
    */
    Point3 perturbed_point = closest.point() + DELTA * closest.surface_normal();

    RGBColor color_diff = object_color;
    color_diff.mulitplicative_scale(properties_.ambient_lighting());
    rgb.additive_blend(color_diff); 

    /*
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
    */

    if (reflectivity > 0) {
        auto const direction = ray.direction();
        const double f = 2 * direction.dot(closest.surface_normal());
        const Vector3 reflected_direction = direction - f * closest.surface_normal();
        const Ray reflect(perturbed_point, reflected_direction);
        RGBColor reflection_rgb = render(reflect, depth+1, max_depth);
        reflection_rgb.mulitplicative_scale(reflectivity);
        rgb.additive_blend(reflection_rgb);
    }
	return rgb;
}

} // namespace SimpleRaytracer
