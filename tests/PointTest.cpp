#include "Point3.hpp"
using Point3 = SimpleRaytracer::Point3;
using Vector3 = SimpleRaytracer::Vector3;

#include "catch.hpp"

TEST_CASE("Point3 Assignment", "[assign]") {
    Point3 A = {100, 24, 23.2};
    REQUIRE(A.x() == 100);
    REQUIRE(A.y() == 24);
    REQUIRE(A.z() == 23.2);
}

TEST_CASE("Point3 Operators", "[operators]") {
    Point3 A = {100, 24, 23.2};
    Vector3 B = {100, 24, 23.2};
    Point3 C = {0, 0, 0};

    SECTION("Equality") {
        REQUIRE(A == Point3({100, 24, 23.2}));
        REQUIRE(C == Point3({0, 0, 0}));
        REQUIRE(C != A);
    }

    SECTION("Addition") {
        Point3 D = A+B;
        REQUIRE(D.x() == (A.x() + B.x()));
        REQUIRE(D.y() == (A.y() + B.y()));
        REQUIRE(D.z() == (A.z() + B.z()));
    }

    SECTION("Subtraction") {
        REQUIRE(B == (A-C));
    }
}
