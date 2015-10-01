#include <cmath>

#include "Primitives.hpp"
#include "Point3.hpp"
#include "Vector3.hpp"
#include "Ray.hpp"
using Point3 = simple_raytracer::Point3;
using Vector3 = simple_raytracer::Vector3;

#include "catch.hpp"

TEST_CASE("Sphere Intersection Test", "[intersect]") {
    // not important for this test, but constructor needs it
    simple_raytracer::MaterialProperties mp({0,0,0}, 0, 0);

    simple_raytracer::Sphere s1({0, 0, 10}, 1 ,mp);

    simple_raytracer::Ray z({0,0,0}, {0, 0, 1});
    simple_raytracer::Ray x({0,0,0}, {1, 0, 0});

    simple_raytracer::Intersection s1z = s1.Intersect(z);
    simple_raytracer::Intersection s1x = s1.Intersect(x);

    REQUIRE(s1z.hit() == true);
    REQUIRE(s1x.hit() == false);

    REQUIRE(s1z.time() == Approx(9));

    simple_raytracer::Sphere s2({2,2,0}, 1, mp);
    Vector3 dir(1,2,0);
    dir.Normalize();
    simple_raytracer::Ray oblique_ray({0,0,0}, dir);

    simple_raytracer::Intersection s2oblique = s2.Intersect(oblique_ray);
    REQUIRE(s2oblique.hit() == true);
    REQUIRE(s2oblique.time() == Approx(std::sqrt(5.0)));
}

