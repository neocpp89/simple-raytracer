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

You can also the run the program as

    simple-raytracer scene-file.txt

which will attempt to parse `scene-file.txt` and generate the output as specified in that file.

In either case, the program is not chatty -- that is, if nothing goes wrong, it will not produce any output except the bitmap file itself.

Making Scenes
-------------

There are a small number of example scenes which can be parsed by `simple-raytracer`.
The langage is fairly rigid in structure (and the parser will break easily), but the examples provided show the basic commands.

The coordinate system is oriented such that if the X component goes to the right and the Y component goes up, the Z component goes into the plane XY.
This is reversed from what is usually expected by a right-handed coordinate system.

As an example, if we have a Camera at (0,0,0), and the screen is such that (1,0,0) is a point on the right side of the image, and (0,1,0) is a point on the top of the image, an object (A) with coordinates (0,0,-10) would be behind the Camera.
An object (B) with coordinates (0,0,10) would be in front of the camera, while an object (C) with coordinates (0,0,20) would be even further in front of object (B) (so C would be obscured from the camera perspective by C).
I apologize if this is confusing.

A simple example:

    # Absolute minimum needed to generate a scene.
    # Note that blank lines are ignored, as well as lines starting with '#'
    camera = (0,0,-1000)
    bitmap-file = "simple.bmp"
    bitmap-size = 1024x768
    scene-properties = { bgcolor = (0,0,0) : ambient = 0.1 }
    screen = { top-left = (-50, 37.5, -500) : top-right = (50, 37.5, -500) : bottom-left = (-50, -37.5, -500) }

    # Here we add a sphere, a plane, and a light source
    add-sphere[ origin = (0,0,0) : radius = 10 : material = { color = (255,0,0) : lambertian = 0.2 : reflectivity = 0.8 }]
    add-plane[ normal = (0,1,0) : distance = 55 : material = { color = (0,255,0) : lambertian = 0.9 : reflectivity = 0.1 }]
    add-point-light[ origin = (500,500,-400) : color = (255,255,255) : intensity= 1.0 ]

