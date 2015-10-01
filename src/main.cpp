// A simple raytracer.

#include <string>

#include "Bitmap.hpp"
#include "Camera.hpp"
#include "Point3.hpp"
#include "Primitives.hpp"
#include "Scene.hpp"
#include "Screen.hpp"

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

    simple_raytracer::RGBColor material_rgb(255, 0, 0);
    const double material_lambertian = 0.3;
    const double material_reflectivity = 0.7;
    simple_raytracer::MaterialProperties material_props(material_rgb, material_lambertian, material_reflectivity);
    simple_raytracer::Point3 sphere_center(0, 0, 0);
    const double sphere_radius = 100;
    simple_raytracer::Scene scene(camera, screen, scene_props);

    scene.AddObject(new simple_raytracer::Sphere(sphere_center, sphere_radius, material_props));
    scene.AddObject(new simple_raytracer::Sphere({200, 0, 0}, 50, {{103,0,255}, 0.5, 0.5}));
    scene.AddObject(new simple_raytracer::Sphere({630, 213, 0}, 50, {{103,20,255}, 0.5, 0.5}));
    scene.AddObject(new simple_raytracer::Sphere({-420, 12, 0}, 50, {{103,60,255}, 0.5, 0.5}));
    scene.AddObject(new simple_raytracer::Sphere({120, 12, 0}, 50, {{103,70,255}, 0.5, 0.5}));
    scene.AddObject(new simple_raytracer::Sphere({-110, -12, 0}, 50, {{103,80,255}, 0.5, 0.5}));
    scene.AddObject(new simple_raytracer::Sphere({520, -162, 0}, 50, {{103,100,255}, 0.5, 0.5}));
    scene.AddObject(new simple_raytracer::Plane({0, 1, 0}, 125, {{180,120,255}, 0.2, 0.8}));

    scene.AddLight(new simple_raytracer::ScenePointLight({500, 500, 0}, {255, 255, 255}, 1.0));
    scene.AddLight(new simple_raytracer::ScenePointLight({-500, 500, 0}, {255, 200, 255}, 0.5));
    scene.AddLight(new simple_raytracer::ScenePointLight({-300, 700, 0}, {255, 255, 255}, 1.0));
    return scene;
}

int main(int argc, char **argv)
{
    if (argc != 2 && argc != 4) {
        std::cout << "usage: " << argv[0] << " [CONFIG] or [BITMAP-FILE WIDTH HEIGHT]";
        return 0;
    }
    const std::string bmp_filename(argv[1]);
    const int width = std::stoi(argv[2]);
    const int height = std::stoi(argv[3]);

    if (width < 0 || height < 0) {
        std::cout << "Need positive sizes for image dimensions.\n";
        return 0;
    }

    simple_raytracer::Bitmap bmp(width, height);
    simple_raytracer::Scene scene = DemoScene(width, height);

    const int max_bounces = 16;
    scene.Render(max_bounces);
    for (int i = 0; i < bmp.height(); i++) {
        for (int j = 0; j < bmp.width(); j++) {
            bmp.SetPixelImageCoordinates(i, j, scene.GetPixel(i, j));
        }
    }

    bmp.WriteFile(bmp_filename);
	return 0;
}

