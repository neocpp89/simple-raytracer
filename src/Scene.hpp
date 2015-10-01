#ifndef SRT_SCENE_HPP_
#define SRT_SCENE_HPP_
#include <vector>
#include <memory>

#include "Camera.hpp"
#include "Color.hpp"
#include "Primitives.hpp"
#include "Screen.hpp"
#include "Light.hpp"

namespace simple_raytracer {

/*
    Manager class for overall properties of the scene, such as
    ambient lighting level (double from 0.0 to 1.0) and background color
    (specified as an RGBColor).
*/
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

/*
    The main scene class.

    After setting up a Camera and Screen (and SceneProperties), you can create
    one of these objects.

    Call AddObject(new DerivedFromSceneObject(...)) and
    AddLight(new DerivedFromSceneLight(...)) to actually populate the scene.

    After this is done, call Render() to compute the image pixel data.

    This contains the main recursive raytracing function.
*/
class Scene
{
    public:
        Scene(const Camera &camera, const Screen &screen, const SceneProperties &properties) :
            camera_(camera), screen_(screen), 
            pixel_data_(screen.rows() * screen.columns(), properties.bgcolor()),
            properties_(properties) {}

        void Render(int max_depth = 8);
        RGBColor GetPixel(int i, int j) const { return pixel_data_[IndexOf(i, j)]; }

        /*
            I feel a bit uneasy about this due to the pointer, but I can't
            think of a better way to do it. Something like the below is close
            to what I want, but isn't quite right.

            It gets captured by the unique pointer anyways, so the caller
            doesn't have to worry about memory management.

            This bears repeating: don't worry about manually freeing the objects
            you insert into the scene object; they are freed automatically by
            the unique_ptr.

            // void AddObject(std::unique_ptr<SceneObject> object) { objects_.emplace_back(std::move(object)); }
            // void AddLight(std::unique_ptr<SceneLight> light) { lights_.emplace_back(std::move(light)); }
        */
        void AddObject(SceneObject *object) { objects_.emplace_back(object); }
        void AddLight(SceneLight *light) { lights_.emplace_back(light); }

    private:
        const Camera camera_;
        const Screen screen_;
        std::vector<std::unique_ptr<SceneObject>> objects_;
        std::vector<std::unique_ptr<SceneLight>> lights_;
        std::vector<RGBColor> pixel_data_;
        SceneProperties properties_;

        RGBColor Render(const Ray &ray, int depth, int max_depth) const;
        Intersection FindClosestObjectAlongRay(const Ray &ray, size_t &index) const;
        int IndexOf(int i, int j) const;
};

} // namespace simple_raytracer

#endif // SRT_SCENE_HPP_
