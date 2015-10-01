// A simple raytracer.

#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <cmath>
#include <cassert>

#include "color.h"
#include "Bitmap.hpp"
#include "intersect.h"
#include "Scene.hpp"

int main(int argc, char **argv)
{
    if (argc != 4) {
        std::cout << "usage: " << argv[0] << " BITMAP-FILE WIDTH HEIGHT";
        return 0;
    }
    const std::string bmp_filename(argv[1]);
    const int width = std::stoi(argv[2]);
    const int height = std::stoi(argv[3]);

    if (width < 0 || height < 0) {
        std::cout << "Need positive sizes for image dimensions.\n";
        return 0;
    }

    SimpleRaytracer::Bitmap bmp(width, height);
	SimpleRaytracer::Camera camera({0, 0, -1000});
    SimpleRaytracer::SceneProperties scene_props({0,0,0}, 0.1);
    SimpleRaytracer::Point3 top_left({-160, 120, -200});
    SimpleRaytracer::Point3 top_right({160, 120, -200});
    SimpleRaytracer::Point3 bottom_left({-160, -120, -200});
    SimpleRaytracer::Screen screen(top_left, top_right, bottom_left, bmp.height(), bmp.width());

    SimpleRaytracer::RGBColor material_rgb(255, 0, 0);
    const double material_lambertian = 0.3;
    const double material_reflectivity = 0.7;
    SimpleRaytracer::MaterialProperties material_props(material_rgb, material_lambertian, material_reflectivity);
    SimpleRaytracer::Point3 sphere_center(0, 0, 0);
    const double sphere_radius = 100;
    SimpleRaytracer::Scene scene(camera, screen, scene_props);

    scene.add_object(new SimpleRaytracer::Sphere(sphere_center, sphere_radius, material_props));
    scene.add_object(new SimpleRaytracer::Sphere({200, 0, 0}, 50, {{103,0,255}, 0.5, 0.5}));
    scene.add_object(new SimpleRaytracer::Sphere({630, 213, 0}, 50, {{103,20,255}, 0.5, 0.5}));
    scene.add_object(new SimpleRaytracer::Sphere({-420, 12, 0}, 50, {{103,60,255}, 0.5, 0.5}));
    scene.add_object(new SimpleRaytracer::Sphere({120, 12, 0}, 50, {{103,70,255}, 0.5, 0.5}));
    scene.add_object(new SimpleRaytracer::Sphere({-110, -12, 0}, 50, {{103,80,255}, 0.5, 0.5}));
    scene.add_object(new SimpleRaytracer::Sphere({520, -162, 0}, 50, {{103,100,255}, 0.5, 0.5}));

    scene.add_light(new SimpleRaytracer::ScenePointLight({500, 500, 0}, {255, 255, 255}, 1.0));
    scene.add_light(new SimpleRaytracer::ScenePointLight({-500, 500, 0}, {255, 200, 255}, 0.5));
    scene.add_light(new SimpleRaytracer::ScenePointLight({-300, 700, 0}, {255, 255, 255}, 1.0));

    const int max_bounces = 16;
    scene.render(max_bounces);
    for (int i = 0; i < bmp.height(); i++) {
        for (int j = 0; j < bmp.width(); j++) {
            bmp.set_pixel_ij(i, j, scene.get_pixel(i, j));
        }
    }

    bmp.write_file(bmp_filename);
	return 0;
}

