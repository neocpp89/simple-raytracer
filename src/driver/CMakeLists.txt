SET(SOURCES
        main.cpp
        Parser.cpp
    )
ADD_EXECUTABLE(simple-raytracer ${SOURCES})
TARGET_INCLUDE_DIRECTORIES(simple-raytracer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../libsrt/)
TARGET_INCLUDE_DIRECTORIES(simple-raytracer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
TARGET_LINK_LIBRARIES(simple-raytracer srt)
install(TARGETS simple-raytracer RUNTIME DESTINATION bin)
