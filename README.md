simple-raytracer
================

`simple-raytracer` is a small raytracing program that I wrote around 2009/2010 while at Caltech.
It's your traditional sphere-and-plane rendering program.

I am currently (Sep 2015) updating the program to use more modern C++, and have also moved it to the [CMake][0] build system.

[0]: http://www.cmake.org/

Build and Install
-----------------

`simple-raytracer` doesn't have any external dependencies, and there is an included Makefile in the top-level directory which should generate the `simple-raytracer` executable.

However, for out-of-tree builds you can run the usual cmake build sequence from the top-level directory:

    mkdir build
    cd build
    cmake ..
    make

Running a `make install` in the build directory will produce the executable `simple-raytracer` under the `installed/bin` directory.
This is tunable by setting `CMAKE_INSTALL_PREFIX` during the cmake step, e.g. `cmake -DCMAKE_INSTALL_PREFIX=/usr` to install under `/usr/bin/simple-raytracer`.

Other Components
----------------

I wrote most of the code contained within this repository; the main exception is the unit testing framework [catch][1], which I did not write.

[1]: https://github.com/philsquared/Catch

Running
-------

The driver program `simple-raytracer` has a compiled-in demo scene.
Calling the program as

    simple-raytracer demo.bmp 3200 2400

will create a 3200x2400 pixel file called `demo.bmp`.

It takes about 11 seconds to do this with the builtin demo scene on my laptop with an i5-4200U running Xubuntu 15.04.
It takes about 5.5 seconds on my desktop with an i5-2500k running Xubuntu 15.04.

You can change the filename, and the vertical and horizontal dimensions.
The aspect ratio of the demo screen is 4:3, so picking other aspect ratios will cause the scene to look skewed when viewing the bitmap unless the pixels are not square.
