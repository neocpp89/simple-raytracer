#include "Scene.hpp"
#include <cstdlib>
#include <cmath>

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

namespace {

// reflect a vector across a place defined by a surface normal.
SimpleRaytracer::Vector3 reflection(
    const SimpleRaytracer::Vector3 &direction,
    const SimpleRaytracer::Vector3 &surface_normal);
SimpleRaytracer::Vector3 reflection(
    const SimpleRaytracer::Vector3 &direction,
    const SimpleRaytracer::Vector3 &surface_normal)
{
    const double f = 2 * direction.dot(surface_normal);
    return (direction - f * surface_normal);
}

} // anonymous namespace

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

/*
    Go through and render each pixel in our screen to compose the image.

    This is actually trivially parallelizable since each pixel is independent.
*/
void Scene::render(int max_depth)
{
    for (int i = 0; i < screen_.rows(); i++) {
        for (int j = 0; j < screen_.columns(); j++) {
            Vector3 direction = screen_.get_point(i, j) - camera_.origin();
            direction.normalize();
            Ray ray(screen_.get_point(i, j), direction);
            pixel_data_[indexof(i, j)] = render(ray, 0, max_depth);
            // std::cout << "("<< i << ", "  << j << "): " << screen_.get_point(i, j) << '\n';
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

    if (lambertian > 0) {
        double total_lambertian_factor = 0;
        
        for (auto const &light : lights_) {
            const Vector3 light_vector = light->origin() - perturbed_point;
            const double light_distance_squared = light_vector.dot(light_vector);
            Vector3 light_direction = light_vector;
            light_direction.normalize();

            Ray shadow(perturbed_point, light_direction);

            double current_lambertian_factor = lambertian_factor(light_direction, closest.surface_normal());
            if (current_lambertian_factor > 0) {
                size_t shadow_min_idx = 0;
                Intersection shadow_closest = find_closest_object_along_ray(shadow, shadow_min_idx);
                if (shadow_closest.hit() == false ||
                    (shadow_closest.time() * shadow_closest.time() >= light_distance_squared)) {
                    total_lambertian_factor += current_lambertian_factor;
                    if (reflectivity > 0) {
                        const Vector3 reflected_light_direction = reflection(light_direction, closest.surface_normal());

                        double specularity = reflected_light_direction.dot(ray.direction());
                        if (specularity > 0) {
                            specularity = std::pow(specularity, 100*reflectivity);
                            specularity *= reflectivity * light->intensity();
                            RGBColor composite_light_color = light->color();
                            composite_light_color.mulitplicative_scale(specularity);
                            composite_light_color.clamp_values();
                            rgb.additive_blend(composite_light_color);
                        }
                    }
                }
            }
        }

        if (total_lambertian_factor > 0) {
            total_lambertian_factor *= lambertian;
            RGBColor composite_color = object_color;
            composite_color.mulitplicative_scale(total_lambertian_factor);
            composite_color.clamp_values();
            rgb.additive_blend(composite_color);
        }
    }

    if (reflectivity > 0) {
        const Vector3 reflected_direction = reflection(ray.direction(), closest.surface_normal());
        const Ray reflect(perturbed_point, reflected_direction);
        RGBColor reflection_rgb = render(reflect, depth+1, max_depth);
        reflection_rgb.mulitplicative_scale(reflectivity);
        rgb.additive_blend(reflection_rgb);
    }
	return rgb;
}

} // namespace SimpleRaytracer
