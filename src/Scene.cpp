#include "Scene.hpp"

#if 0
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
#endif

#if 0
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
#endif

namespace {

// reflect a vector across a plane defined by a surface normal.
simple_raytracer::Vector3 reflection(
    const simple_raytracer::Vector3 &direction,
    const simple_raytracer::Vector3 &surface_normal);
simple_raytracer::Vector3 reflection(
    const simple_raytracer::Vector3 &direction,
    const simple_raytracer::Vector3 &surface_normal)
{
    const double f = 2 * direction.Dot(surface_normal);
    return (direction - f * surface_normal);
}

} // anonymous namespace

namespace simple_raytracer {

constexpr double DELTA = 1e-6;

int Scene::IndexOf(int i, int j) const
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
Intersection Scene::FindClosestObjectAlongRay(const Ray &ray, size_t &index) const
{
    Intersection closest;
    size_t min_idx = 0;
    for (size_t i = 0; i < objects_.size(); i++) {
        auto const &object = objects_[i];
        auto intersection = object->Intersect(ray);
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
void Scene::Render(int max_depth)
{
    for (int i = 0; i < screen_.rows(); i++) {
        for (int j = 0; j < screen_.columns(); j++) {
            const Point3 pixel_point = screen_.GetPoint(i, j);
            Vector3 direction = pixel_point - camera_.origin();
            direction.Normalize();
            Ray ray(pixel_point, direction);
            pixel_data_[IndexOf(i, j)] = Render(ray, 0, max_depth);
        }
    }
    return;
}

/*
    This is the actual recursive raytracing function.

    It's a big one!
*/
RGBColor Scene::Render(const Ray &ray, int depth, int max_depth) const
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
    auto closest = FindClosestObjectAlongRay(ray, min_idx);

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
    color_diff.MultiplicativeScale(properties_.ambient_lighting());
    rgb.AdditiveBlend(color_diff);

    /*
        This code is somewhat large and ugly. Refactor into a function soon.

        The lambertian lighting depends on the cosine of the angle to light
        sources. So we simply iterate through the light and compute these
        dot products. There is also specular lighting, which depends on this
        dot product to a power.

        The only other condition we have to worry about is if an object is
        blocking the path to the light, so we need to run another intersection
        test.
    */
    if (lambertian > 0) {
        double total_lambertian_factor = 0;
        
        for (auto const &light : lights_) {
            const Vector3 light_vector = light->origin() - perturbed_point;
            const double light_distance_squared = light_vector.Dot(light_vector);
            Vector3 light_direction = light_vector;
            light_direction.Normalize();

            Ray shadow(perturbed_point, light_direction);

            double current_lambertian_factor = LambertianFactor(light_direction, closest.surface_normal());
            if (current_lambertian_factor > 0) {
                size_t shadow_min_idx = 0;
                Intersection shadow_closest = FindClosestObjectAlongRay(shadow, shadow_min_idx);
                if (shadow_closest.hit() == false ||
                    (shadow_closest.time() * shadow_closest.time() >= light_distance_squared)) {
                    total_lambertian_factor += current_lambertian_factor;
                    if (reflectivity > 0) {
                        const Vector3 reflected_light_direction = reflection(light_direction, closest.surface_normal());

                        double specularity = reflected_light_direction.Dot(ray.direction());
                        if (specularity > 0) {
                            specularity = std::pow(specularity, 100*reflectivity);
                            specularity *= reflectivity * light->intensity();
                            RGBColor composite_light_color = light->color();
                            composite_light_color.MultiplicativeScale(specularity);
                            rgb.AdditiveBlend(composite_light_color);
                        }
                    }
                }
            }
        }

        if (total_lambertian_factor > 0) {
            total_lambertian_factor *= lambertian;
            RGBColor composite_color = object_color;
            composite_color.MultiplicativeScale(total_lambertian_factor);
            rgb.AdditiveBlend(composite_color);
        }
    }

    /*
        Reflect the ray off the surface, absorbing some of the color properties.
    */
    if (reflectivity > 0) {
        const Vector3 reflected_direction = reflection(ray.direction(), closest.surface_normal());
        const Ray reflect(perturbed_point, reflected_direction);
        RGBColor reflection_rgb = Render(reflect, depth+1, max_depth);
        reflection_rgb.MultiplicativeScale(reflectivity);
        rgb.AdditiveBlend(reflection_rgb);
    }
    return rgb;
}

} // namespace simple_raytracer