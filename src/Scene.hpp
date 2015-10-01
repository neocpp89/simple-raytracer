#ifndef SRT_SCENE_HPP_
#define SRT_SCENE_HPP_
#include <vector>
#include <memory>

#include "Camera.hpp"
#include "Primitives.hpp"
#include "Screen.hpp"

#include "fnobject.h"
#include "light.h"
#include "ray.h"

typedef struct scene_s {
	int nobjects;
	int nlights;
	fnobject_t **objects;
	light_t **lights;

	int screenx;
	int screeny;
	vec_t *camera;
	vec_t *screen_origin;
	vec_t ***screenrays;

	double ambient;
} scene_t;

vec_t ***screenrays_precomp(vec_t *screen_origin, vec_t *camera_origin, int resx, int resy, double zoom);
scene_t *scene_init(int x, int y, double zoom);

namespace SimpleRaytracer {

class SceneProperties
{
    public:
        // Some reasonable default values.
        SceneProperties() : bgcolor_({0,0,0}), ambient_lighting_(0.05) {}

        SceneProperties(const RGBColor &bgcolor, double ambient_lighting):
            bgcolor_(bgcolor), ambient_lighting_(ambient_lighting) {}
        RGBColor bgcolor() const { return bgcolor_; }
        double ambient_lighting() const { return ambient_lighting_; }

    private:
        RGBColor bgcolor_;
        double ambient_lighting_;
};

class Scene
{
    public:
        Scene(const Camera &camera, const Screen &screen, const SceneProperties &properties) :
            camera_(camera), screen_(screen), 
            pixel_data_(screen.rows() * screen.columns(), properties.bgcolor()),
            properties_(properties) {}

        void render(int max_depth = 8);
        RGBColor get_pixel(int i, int j) { return pixel_data_[indexof(i, j)]; }

        void add_object(std::unique_ptr<SceneObject> object) { objects_.push_back(std::move(object)); }
        void add_light(std::unique_ptr<SceneLight> light) { lights_.push_back(std::move(light)); }

    private:
        const Camera camera_;
        const Screen screen_;
        std::vector<std::unique_ptr<SceneObject>> objects_;
        std::vector<std::unique_ptr<SceneLight>> lights_;

        std::vector<RGBColor> pixel_data_;

        SceneProperties properties_;

        RGBColor render(const Ray &ray, int depth, int max_depth) const;
        Intersection find_closest_object_along_ray(const Ray &ray, size_t &index) const;
        int indexof(int i, int j) const;

};

} // namespace SimpleRaytracer

#endif // SRT_SCENE_HPP_
