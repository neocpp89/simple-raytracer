SET(SOURCES
        214rt.cpp
        bitmap.cpp
        color.cpp
        intersect.cpp
        light.cpp
        numeric.cpp
        ray.cpp
        scene.cpp
        vec.cpp)
ADD_EXECUTABLE(simple-raytracer ${SOURCES})
TARGET_INCLUDE_DIRECTORIES(simple-raytracer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
install(TARGETS simple-raytracer RUNTIME DESTINATION bin)
