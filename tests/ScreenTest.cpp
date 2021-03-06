#include "Screen.hpp"
using Point3 = simple_raytracer::Point3;

#include "catch.hpp"

TEST_CASE("Screen Point Generataion", "[assign]") {
    const Point3 tl(-2, 2, 0);
    const Point3 tr(2, 2, 0);
    const Point3 bl(-2, -2, 0);
    const int r = 5;
    const int c = 5;
    simple_raytracer::Screen screen(tl, tr, bl, r, c);

    REQUIRE(screen.GetPoint(0,0) == tl);
    REQUIRE(screen.GetPoint(1,1) == Point3(-1, 1, 0));
    REQUIRE(screen.GetPoint(4,4) == Point3(2, -2, 0));
}

