#include "Vector3.hpp"
using Vector3 = SimpleRaytracer::Vector3;

#include "catch.hpp"

TEST_CASE("Assignment", "[assign]") {
    Vector3 A = {100, 24, 23.2};
    REQUIRE(A.x() == 100);
    REQUIRE(A.y() == 24);
    REQUIRE(A.z() == 23.2);
}

TEST_CASE("Operators", "[operators]") {
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


TEST_CASE("Normalization", "[operators]") {
    Vector3 A = {3, 4, 0};
    Vector3 B = {5, 12, 0};
    Vector3 C = {0.5, 0, 0};
    Vector3 D = {24, 8, 6};
    Vector3 E = {0, 0, 0};

    SECTION("Magnitude") {
        REQUIRE(A.magnitude() == 5);
        REQUIRE(B.magnitude() == 13);
        REQUIRE(C.magnitude() == 0.5);
        REQUIRE(D.magnitude() == 26);
        REQUIRE(E.magnitude() == 0);
    }

    SECTION("Normalization") {
        A.normalize();
        B.normalize();
        C.normalize();
        D.normalize();
        E.normalize();
        REQUIRE(A.magnitude() == Approx(1));
        REQUIRE(B.magnitude() == Approx(1));
        REQUIRE(C.magnitude() == Approx(1));
        REQUIRE(D.magnitude() == Approx(1));
        REQUIRE(E.magnitude() == 0);

        D *= 26;
        REQUIRE(D.x() == Approx(24));
        REQUIRE(D.y() == Approx(8));
        REQUIRE(D.z() == Approx(6));
    }
}

TEST_CASE("Dot Product", "[operators]") {
    Vector3 A = {3, 4, 0};
    Vector3 B = {5, 12, 0};

    Vector3 e1 = {1, 0, 0};
    Vector3 e2 = {0, 1, 0};
    Vector3 e3 = {0, 0, 1};

    REQUIRE(e1.dot(e1) == 1);
    REQUIRE(e2.dot(e2) == 1);
    REQUIRE(e3.dot(e3) == 1);
    REQUIRE(e1.dot(e2) == 0);
    REQUIRE(e1.dot(e3) == 0);
    REQUIRE(e2.dot(e3) == 0);
    REQUIRE(e1.dot(A) == 3);
    REQUIRE(e2.dot(A) == 4);
    REQUIRE(e1.dot(B) == 5);
    REQUIRE(e2.dot(B) == 12);
    REQUIRE(A.dot(A) == 25);
    REQUIRE(B.dot(B) == 169);
}
