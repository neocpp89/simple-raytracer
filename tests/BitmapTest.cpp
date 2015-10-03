#include <stdexcept>
#include "Color.hpp"
#include "Bitmap.hpp"

#include "catch.hpp"

TEST_CASE("Bitmap Out of Bounds Access", "[out-of-range]") {
    const int width = 100;
    const int height = 200;
    simple_raytracer::Bitmap bmp(width, height);

    SECTION("Image Coordinate Tests") {
        REQUIRE_NOTHROW(bmp.SetPixelImageCoordinates(199,0,{0,0,0}));
        REQUIRE_NOTHROW(bmp.SetPixelImageCoordinates(0,99,{0,0,0}));

        REQUIRE_THROWS_AS(bmp.SetPixelImageCoordinates(-1, 99, {0,0,0}), std::out_of_range);
        REQUIRE_THROWS_AS(bmp.SetPixelImageCoordinates(199, -1, {0,0,0}), std::out_of_range);
        REQUIRE_THROWS_AS(bmp.SetPixelImageCoordinates(200, 0, {0,0,0}), std::out_of_range);
        REQUIRE_THROWS_AS(bmp.SetPixelImageCoordinates(0, 100, {0,0,0}), std::out_of_range);
    }

    SECTION("Cartesian Coordinate Tests") {
        REQUIRE_NOTHROW(bmp.SetPixel(0,199,{0,0,0}));
        REQUIRE_NOTHROW(bmp.SetPixel(99,0,{0,0,0}));

        REQUIRE_THROWS_AS(bmp.SetPixel(99, -1, {0,0,0}), std::out_of_range);
        REQUIRE_THROWS_AS(bmp.SetPixel(-1, 199, {0,0,0}), std::out_of_range);
        REQUIRE_THROWS_AS(bmp.SetPixel(0, 200, {0,0,0}), std::out_of_range);
        REQUIRE_THROWS_AS(bmp.SetPixel(100, 0, {0,0,0}), std::out_of_range);
    }
}

TEST_CASE("Bitmap Assignment", "[assign]") {
    const int width = 100;
    const int height = 100;
    simple_raytracer::Bitmap bmp(width, height);

    bmp.SetPixelImageCoordinates(0,0,{32,240,255});
    simple_raytracer::RGBColor rgb = bmp.GetPixelImageCoordinates(0,0);
    REQUIRE(rgb.r() == 32);
    REQUIRE(rgb.g() == 240);
    REQUIRE(rgb.b() == 255);

    bmp.SetPixelImageCoordinates(0,0,{21,61,112});
    rgb = bmp.GetPixelImageCoordinates(0,0);
    REQUIRE(rgb.r() == 21);
    REQUIRE(rgb.g() == 61);
    REQUIRE(rgb.b() == 112);
}

