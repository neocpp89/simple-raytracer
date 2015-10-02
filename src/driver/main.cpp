// A simple raytracer.

#include <string>

#include "Bitmap.hpp"
#include "Camera.hpp"
#include "Color.hpp"
#include "Point3.hpp"
#include "Primitives.hpp"
#include "Scene.hpp"
#include "Screen.hpp"

#include "Parser.hpp"

/*
    This is a builtin demo scene.
*/
simple_raytracer::Scene DemoScene(int width, int height);
simple_raytracer::Scene DemoScene(int width, int height)
{
    simple_raytracer::Camera camera({0, 0, -1000});
    simple_raytracer::SceneProperties scene_props({0,0,0}, 0.1);
    simple_raytracer::Point3 top_left({-160, 120, -200});
    simple_raytracer::Point3 top_right({160, 120, -200});
    simple_raytracer::Point3 bottom_left({-160, -120, -200});
    simple_raytracer::Screen screen(top_left, top_right, bottom_left, height, width);

    simple_raytracer::Scene scene(camera, screen, scene_props);

    scene.AddObject(new simple_raytracer::Sphere({-160, 120, 5}, 100, {{32,120,32}, 0.5, 0.5}));
    scene.AddObject(new simple_raytracer::Sphere({200, 0, 3}, 77, {{103,0,255}, 0.5, 0.5}));
    scene.AddObject(new simple_raytracer::Sphere({30, 143, 61}, 50, {{32,32,255}, 0.3, 0.7}));
    scene.AddObject(new simple_raytracer::Sphere({-20, -70, -12}, 55, {{255,32,32}, 0.7, 0.3}));
    scene.AddObject(new simple_raytracer::Sphere({100, 52, 5}, 23, {{103,70,255}, 0.5, 0.5}));
    scene.AddObject(new simple_raytracer::Sphere({-110, -12, 12}, 40, {{240,240,32}, 0.1, 0.9}));
    scene.AddObject(new simple_raytracer::Sphere({80, -105, 63}, 12, {{32,240,32}, 0.8, 0.2}));
    scene.AddObject(new simple_raytracer::Plane({0, 1, 0}, 125, {{128,77,180}, 0.4, 0.6}));

    scene.AddLight(new simple_raytracer::ScenePointLight({1000, 1000, -400}, {255, 255, 255}, 1.0));
    scene.AddLight(new simple_raytracer::ScenePointLight({-500, 500, 0}, {255, 255, 255}, 1.0));
    scene.AddLight(new simple_raytracer::ScenePointLight({-700, 700, 400}, {255, 255, 255}, 1.0));
    return scene;
}

void DoDemo(const std::string &filename, int width, int height)
{
    simple_raytracer::Bitmap bmp(width, height);
    simple_raytracer::Scene scene = DemoScene(width, height);

    const int max_bounces = 32;
    scene.Render(max_bounces);
    for (int i = 0; i < bmp.height(); i++) {
        for (int j = 0; j < bmp.width(); j++) {
            bmp.SetPixelImageCoordinates(i, j, scene.GetPixel(i, j));
        }
    }

    bmp.WriteFile(filename);
    return;
}

void RenderSceneFile(const std::string &filename)
{
    std::cout << filename;
    std::ifstream ifs(filename);
    driver::SceneFileParser parser(ifs);
    /*
        Somewhat of a misnomer, this actually will do the rendering too.
    */
    simple_raytracer::Scene scene = parser.GetScene();
    return;
}

int main(int argc, char **argv)
{
    if (argc != 2 && argc != 4) {
        std::cout << "usage: " << argv[0] << " [CONFIG] or [BITMAP-FILE WIDTH HEIGHT]";
        return 0;
    }

    if (argc == 4) {
        std::string bmp_filename(argv[1]);
        int width = std::stoi(argv[2]);
        int height = std::stoi(argv[3]);
        DoDemo(bmp_filename, width, height);
    } else if (argc == 2) {
        std::string scene_filename(argv[1]);
        RenderSceneFile(scene_filename);
    }
    return 0;
}

