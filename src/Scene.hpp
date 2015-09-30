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

class Scene
{
    public:
        Scene(const Camera &camera, const Screen &screen) :
            camera_(camera), screen_(screen),
            pixel_data_(screen.rows() * screen.columns(), {0, 0, 0}) {}

        void render();
        RGBColor get_pixel(int i, int j) { return pixel_data_[indexof(i, j)]; }

    private:
        const Camera camera_;
        const Screen screen_;
        std::vector<std::unique_ptr<SceneObject>> objects_;
        std::vector<std::unique_ptr<SceneLight>> lights_;

        std::vector<RGBColor> pixel_data_;

        RGBColor render(const Vector3 &direction);
        int indexof(int i, int j) const;
};

} // namespace SimpleRaytracer

#endif // SRT_SCENE_HPP_
