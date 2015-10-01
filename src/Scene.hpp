#ifndef SRT_SCENE_HPP_
#define SRT_SCENE_HPP_
#include <vector>
#include <memory>

#include "Camera.hpp"
#include "Primitives.hpp"
#include "Screen.hpp"

#include "Light.hpp"

namespace simple_raytracer {

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
        RGBColor get_pixel(int i, int j) const { return pixel_data_[indexof(i, j)]; }


        /*
            I feel a bit uneasy about this due to the pointer, but I can't
            think of a better way to do it. Something like the below is close
            to what I want, but isn't quite right.

            It gets captured by the unique pointer anyways, so the caller
            doesn't have to worry about memory management.

            This bears repeating: don't worry about manually freeing the objects
            you insert into the scene object; they are freed automatically by
            the unique_ptr.

            // void add_object(std::unique_ptr<SceneObject> object) { objects_.emplace_back(std::move(object)); }
            // void add_light(std::unique_ptr<SceneLight> light) { lights_.emplace_back(std::move(light)); }
        */
        void add_object(SceneObject *object) { objects_.emplace_back(object); }
        void add_light(SceneLight *light) { lights_.emplace_back(light); }

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

} // namespace simple_raytracer

#endif // SRT_SCENE_HPP_
