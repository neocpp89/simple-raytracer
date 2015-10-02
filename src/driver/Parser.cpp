#include <istream>
#include <iostream>
#include <regex>
#include <string>
#include <stdexcept>
#include <vector>

#include "Parser.hpp"

namespace driver {

const std::regex kCameraRegex(
    R"raw(\s*camera\s*=\s*(\(.*\)))raw",
    std::regex_constants::icase);
const std::regex kFilenameRegex(
    R"raw(\s*bitmap-file\s*=\s*['"](.*)['"])raw",
    std::regex_constants::icase);
const std::regex kBitmapSizeRegex(
    R"raw(\s*bitmap-size\s*=\s*(\d+)x(\d+))raw",
    std::regex_constants::icase);
const std::regex kScenePropertiesRegex(
    R"raw(\s*scene-properties\s*=\s*(\{.*\}))raw",
    std::regex_constants::icase);
const std::regex kScenePropertiesInnerRegex(
    R"raw(\s*\{\s*bgcolor\s*=\s*(\(.*\))\s*:\s*ambient\s*=\s*([^\s]*)\s*\}\s*)raw",
    std::regex_constants::icase);
const std::regex kScreenRegex(
    R"raw(\s*screen\s*=\s*(\{.*\}))raw",
    std::regex_constants::icase);
const std::regex kScreenInnerRegex(
    R"raw(\s*\{\s*top-left\s*=\s*(\(.*\))\s*:\s*top-right\s*=\s*(\(.*\))\s*:\s*bottom-left\s*=\s*(\(.*\))\s*\}\s*)raw",
    std::regex_constants::icase);
const std::regex kSphereRegex(
    R"raw(\s*add-sphere\s*(\[.*\])\s*)raw",
    std::regex_constants::icase);
const std::regex kMaterialPropertiesRegex(
    R"raw(\s*\{\s*color\s*=\s*(\(.*\))\s*:\s*lambertian\s*=\s*([^\s]*)\s*:\s*reflectivity\s*=\s*([^\s]*)\s*\}\s*)raw",
    std::regex_constants::icase);
const std::regex kTripletRegex(
    R"raw(\s*\(([^,]*),([^,]*),([^,]*)\))raw",
    std::regex_constants::icase);

/*
    Helper function since a lot of things take points or triplets...
*/
template <typename T, typename Member = double>
T ParseTriplet(const std::string &triplet_string);

/*
    Other helpers for parsing portions of the scene file.
*/
simple_raytracer::SceneProperties ParseSceneProperties(const std::string &scene_property_string);
simple_raytracer::MaterialProperties ParseMaterialProperties(const std::string &material_properties_string);
simple_raytracer::Sphere ParseSphere(const std::string &sphere_string);

template <typename T, typename Member>
T ParseTriplet(const std::string &triplet_string)
{
    std::smatch result;
    std::regex_search(triplet_string, result, kTripletRegex);

    if (result.size() != 4) {
        throw ParsingError("Can't process triplet string : ["+triplet_string+"].\n");
    }

    Member x = 0;
    Member y = 0;
    Member z = 0;
    std::istringstream iss(result[1]);
    iss >> x;
    iss.str(result[2]);
    iss.clear();
    iss >> y;
    iss.str(result[3]);
    iss.clear();
    iss >> z;

    return T({x, y, z});
}

simple_raytracer::SceneProperties ParseSceneProperties(const std::string &scene_property_string)
{
    std::smatch result;
    std::regex_search(scene_property_string, result, kScenePropertiesInnerRegex);
    if (result.size() != 3) {
    }

    simple_raytracer::RGBColor bgcolor = ParseTriplet<simple_raytracer::RGBColor, int>(result[1]);
    double ambient = 0;
    std::istringstream iss(result[2]);
    iss >> ambient;

    return simple_raytracer::SceneProperties(bgcolor, ambient);
}

simple_raytracer::MaterialProperties ParseMaterialProperties(const std::string &material_properties_string)
{
    std::smatch result;
    std::regex_search(material_properties_string, result, kMaterialPropertiesRegex);
    if (result.size() != 4) {
    }

    simple_raytracer::RGBColor color = ParseTriplet<simple_raytracer::RGBColor, int>(result[1]);
    double lambertian = 0;
    double reflectivity = 0;
    std::istringstream iss(result[2]);
    iss >> lambertian;
    iss.str(result[3]);
    iss.clear();
    iss >> reflectivity;

    return simple_raytracer::MaterialProperties(color, lambertian, reflectivity);
}

simple_raytracer::Sphere ParseSphere(const std::string &sphere_string)
{
    std::smatch result;
    std::regex_search(sphere_string, result, kSphereRegex);
    if (result.size() != 3) {
    }

    simple_raytracer::Point3 origin = ParseTriplet<simple_raytracer::Point3>(result[1]);
    double radius = 0;
    std::istringstream iss(result[2]);
    iss >> radius;
    simple_raytracer::MaterialProperties material_properties = ParseMaterialProperties(result[3]);

    return simple_raytracer::Sphere(origin, radius, material_properties);
}


/*
    Ugly, large, and fragile parsing function. Refactor later.
*/
simple_raytracer::Scene SceneFileParser::GetScene()
{
    /*
        At minimum we need these to create the scene.
    */
    bool got_dimensions = false;
    bool got_filename = false;
    bool got_camera = false;
    bool got_screen = false;
    bool got_scene_properties = false;

    simple_raytracer::Point3 camera_origin({0,0,0});

    simple_raytracer::Point3 screen_top_left({0,0,0});
    simple_raytracer::Point3 screen_top_right({0,0,0});
    simple_raytracer::Point3 screen_bottom_left({0,0,0});

    std::string filename("output.bmp");
    int bitmap_width = 1;
    int bitmap_height = 1;

    simple_raytracer::SceneProperties scene_properties;

    std::string line;
    while (std::getline(is_, line)) {
        // blank line or comment
        if (line.size() == 0 || line[0] == '#') {
            continue;
        }

        std::smatch result;

        if (std::regex_search(line, result, kCameraRegex))
        {
            if (result.size() != 2) {
                throw ParsingError("Can't process camera line: ["+line+"].\n");
            }
            camera_origin = ParseTriplet<simple_raytracer::Point3>(result[1]);
            std::cout << camera_origin << '\n';
            got_camera = true;
        } else if (std::regex_search(line, result, kFilenameRegex)) {
            if (result.size() != 2) {
                throw ParsingError("Can't process filename line: ["+line+"].\n");
            }
            filename = result[1];
            got_filename = true;
        } else if (std::regex_search(line, result, kBitmapSizeRegex)) {
            if (result.size() != 3) {
                throw ParsingError("Can't process bitmap size line: ["+line+"].\n");
            }
            std::istringstream iss(result[1]);
            iss >> bitmap_width;
            iss.str(result[2]);
            iss.clear();
            iss >> bitmap_height;
            got_screen = true;
        } else if (std::regex_search(line, result, kScenePropertiesRegex)) {
            if (result.size() != 2) {
                throw ParsingError("Can't process scene properties: ["+line+"].\n");
            }
            scene_properties = ParseSceneProperties(result[1]);
            got_scene_properties = true;
        } else if (std::regex_search(line, result, kScreenRegex)) {
            if (result.size() != 2) {
                throw ParsingError("Can't process screen: ["+line+"].\n");
            }
            std::string inner_string(result[1]);
            std::smatch inner_result;
            std::regex_search(inner_string, inner_result, kScreenInnerRegex);
            if (inner_result.size() != 4) {
                throw ParsingError("Can't process screen internals: ["+inner_string+"].\n");
            }
            screen_top_left = ParseTriplet<simple_raytracer::Point3>(inner_result[1]);
            screen_top_right = ParseTriplet<simple_raytracer::Point3>(inner_result[2]);
            screen_bottom_left = ParseTriplet<simple_raytracer::Point3>(inner_result[3]);
            got_screen = true;
        } else {
            throw ParsingError("Unknown line: ["+line+"].\n");
        }

        std::cout << line << '\n';
    }

    if (bitmap_width < 1 || bitmap_height < 1) {
        throw ParsingError("Bitmap Dimensions must be >= 1 each.\n");
    }

    std::cout << "Parsed:\n";
    std::cout << "  Camera: " << camera_origin << '\n';
    std::cout << "  Bitmap File: \"" << filename << "\"\n";
    std::cout << "  Bitmap Dimensions: (" << bitmap_width << ", " << bitmap_height << ")\n";

    simple_raytracer::Camera camera(camera_origin);
    simple_raytracer::Screen screen(screen_top_left, screen_top_right, screen_bottom_left, bitmap_height, bitmap_width);
    simple_raytracer::Scene scene(camera_origin, screen, scene_properties);

    return scene;
}

} // namespace driver
