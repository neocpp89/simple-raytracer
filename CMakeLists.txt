CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)
PROJECT(simple-raytracer)
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
SET(CMAKE_CXX_FLAGS "-march=native -std=c++11 -O3 -Wall -Wextra")

ENABLE_TESTING()

# default install is to a subdirectory of build dir
# override with `cmake -DCMAKE_INSTALL_PREFIX=/usr/local ..`
IF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    SET(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/installed" CACHE PATH "Default install path" FORCE)
ENDIF()

IF (CMAKE_CONFIGURATION_TYPES)
    ADD_CUSTOM_TARGET(vtest COMMAND ${CMAKE_CTEST_COMMAND}
        --force-new-ctest-process --output-on-failure
        --build-config "$<CONFIGURATION>")
ELSE ()
    ADD_CUSTOM_TARGET(vtest COMMAND ${CMAKE_CTEST_COMMAND}
        --force-new-ctest-process --output-on-failure)
ENDIF ()

INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}/src
)
ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(tests)

