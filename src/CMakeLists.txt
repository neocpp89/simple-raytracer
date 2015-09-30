SET(DRIVER_SOURCES 214rt.cpp)
SET(LIB_SOURCES
        Bitmap.cpp
        Color.cpp
        Camera.cpp
        Primitives.cpp
        intersect.cpp
        light.cpp
        numeric.cpp
        ray.cpp
        scene.cpp
        vec.cpp)
ADD_LIBRARY(srt ${LIB_SOURCES})
ADD_EXECUTABLE(simple-raytracer ${DRIVER_SOURCES})
TARGET_INCLUDE_DIRECTORIES(simple-raytracer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
TARGET_LINK_LIBRARIES(simple-raytracer srt)
install(TARGETS simple-raytracer RUNTIME DESTINATION bin)
