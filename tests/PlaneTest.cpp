#include <cmath>

#include "Primitives.hpp"
#include "Point3.hpp"
#include "Vector3.hpp"
#include "Ray.hpp"
using Point3 = simple_raytracer::Point3;
using Vector3 = simple_raytracer::Vector3;

#include "catch.hpp"

TEST_CASE("Plane Intersection Test", "[intersect]") {
    // not important for this test, but constructor needs it
    simple_raytracer::MaterialProperties mp({0,0,0}, 0, 0);
    // 10 below z (points forward)
    simple_raytracer::Plane z({0, 0, 1}, 10, mp);
    // 10 below y (points down)
    simple_raytracer::Plane y({0, -1, 0}, 10, mp);
    // 10 left x (points right)
    simple_raytracer::Plane x({1, 0, 0}, 10, mp);

    simple_raytracer::Ray rx({0,0,0}, {-1, 0, 0});
    simple_raytracer::Ray ry({0,0,0}, {0, -1, 0});
    simple_raytracer::Ray rz({0,0,0}, {0, 0, -1});

    simple_raytracer::Intersection xrx = x.Intersect(rx);
    simple_raytracer::Intersection xry = x.Intersect(ry);
    simple_raytracer::Intersection xrz = x.Intersect(rz);
    simple_raytracer::Intersection yrx = y.Intersect(rx);
    simple_raytracer::Intersection yry = y.Intersect(ry);
    simple_raytracer::Intersection yrz = y.Intersect(rz);
    simple_raytracer::Intersection zrx = z.Intersect(rx);
    simple_raytracer::Intersection zry = z.Intersect(ry);
    simple_raytracer::Intersection zrz = z.Intersect(rz);

    REQUIRE(xrx.hit() == true);
    REQUIRE(xry.hit() == false);
    REQUIRE(xrz.hit() == false);
    REQUIRE(yrx.hit() == false);
    REQUIRE(yry.hit() == false); // wrong direction
    REQUIRE(yrz.hit() == false);
    REQUIRE(zrx.hit() == false);
    REQUIRE(zry.hit() == false);
    REQUIRE(zrz.hit() == true);

    REQUIRE(xrx.time() == Approx(10));
    REQUIRE(zrz.time() == Approx(10));

    Vector3 rxry({-1, -1, 0});
    rxry.Normalize();
    simple_raytracer::Ray oblique_ray({0,0,0}, rxry);

    simple_raytracer::Intersection oblique_intersection = x.Intersect(oblique_ray);
    REQUIRE(oblique_intersection.hit() == true);
    REQUIRE(oblique_intersection.time() == Approx(std::sqrt(2) * 10));
}

