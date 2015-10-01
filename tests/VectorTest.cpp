#include "Vector3.hpp"
using Vector3 = simple_raytracer::Vector3;

#include "catch.hpp"

TEST_CASE("Vector 3Assignment", "[assign]") {
    Vector3 A = {100, 24, 23.2};
    REQUIRE(A.x() == 100);
    REQUIRE(A.y() == 24);
    REQUIRE(A.z() == 23.2);
}

TEST_CASE("Vector3 Operators", "[operators]") {
    Vector3 A = {100, 24, 23.2};
    Vector3 B = {100, 24, 23.2};
    Vector3 C = {0, 0, 0};

    SECTION("Equality") {
        REQUIRE(C == Vector3({0, 0, 0}));
        REQUIRE(A == B);
        REQUIRE(C != A);
    }

    SECTION("Addition") {
        Vector3 D = A+B;
        REQUIRE(D.x() == (A.x() + B.x()));
        REQUIRE(D.y() == (A.y() + B.y()));
        REQUIRE(D.z() == (A.z() + B.z()));
    }

    SECTION("Subtraction") {
        REQUIRE(Vector3({0,0,0}) == (A-B));
    }

    SECTION("Multiplication") {
        Vector3 E = 2*A;
        Vector3 F = B*2;
        REQUIRE(E == F);
        REQUIRE(E == (A+A));
        E *= 2;
        REQUIRE(E == (A+A+A+A));
    }

    SECTION("Division") {
        Vector3 F = A*8;
        REQUIRE((F/8) == A);
        F /= 8;
        REQUIRE(F == A);
    }
}


TEST_CASE("Vector3 Normalization", "[operators]") {
    Vector3 A = {3, 4, 0};
    Vector3 B = {5, 12, 0};
    Vector3 C = {0.5, 0, 0};
    Vector3 D = {24, 8, 6};
    Vector3 E = {0, 0, 0};

    SECTION("Magnitude") {
        REQUIRE(A.Magnitude() == 5);
        REQUIRE(B.Magnitude() == 13);
        REQUIRE(C.Magnitude() == 0.5);
        REQUIRE(D.Magnitude() == 26);
        REQUIRE(E.Magnitude() == 0);
    }

    SECTION("Normalization") {
        A.Normalize();
        B.Normalize();
        C.Normalize();
        D.Normalize();
        E.Normalize();
        REQUIRE(A.Magnitude() == Approx(1));
        REQUIRE(B.Magnitude() == Approx(1));
        REQUIRE(C.Magnitude() == Approx(1));
        REQUIRE(D.Magnitude() == Approx(1));
        REQUIRE(E.Magnitude() == 0);

        D *= 26;
        REQUIRE(D.x() == Approx(24));
        REQUIRE(D.y() == Approx(8));
        REQUIRE(D.z() == Approx(6));
    }
}

TEST_CASE("Vector3 Dot Product", "[operators]") {
    Vector3 A = {3, 4, 0};
    Vector3 B = {5, 12, 0};

    Vector3 e1 = {1, 0, 0};
    Vector3 e2 = {0, 1, 0};
    Vector3 e3 = {0, 0, 1};

    REQUIRE(e1.Dot(e1) == 1);
    REQUIRE(e2.Dot(e2) == 1);
    REQUIRE(e3.Dot(e3) == 1);
    REQUIRE(e1.Dot(e2) == 0);
    REQUIRE(e1.Dot(e3) == 0);
    REQUIRE(e2.Dot(e3) == 0);
    REQUIRE(e1.Dot(A) == 3);
    REQUIRE(e2.Dot(A) == 4);
    REQUIRE(e1.Dot(B) == 5);
    REQUIRE(e2.Dot(B) == 12);
    REQUIRE(A.Dot(A) == 25);
    REQUIRE(B.Dot(B) == 169);
}
