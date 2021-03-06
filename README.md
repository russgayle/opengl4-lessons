opengl4-lessons
===============

**Note**
--------
This project is being discontinued. Instead, I'm migrating most of the relevant library parts to another project to build that up. I'm keeping this around just for reference at this point in time. Thanks! 

Exercises with OpenGL 4 (on Mac and Ubuntu 12.04LTS)

* Lesson 1: Simple program with setup.
* Lesson 2: More robust initialization.
* Lesson 3: Infrastructure for sustainable shader / OpenGL development! 
* Lesson 4: VBOs, VAOs...
* Lesson 5: Basic transforms
* Lesson 6: Virtual camera

Moving on in a random order now. 

* March 17, 2014: Added a simple phong-blinn shader.

See http://antongerdelan.net/opengl/ for details.

My long ways away to do...

* [OpenSceneGraph](http://www.openscenegraph.org/) based solutions/
* [Qt5](http://qt-project.org/wiki/Qt_5.0) based solutions.
* Shaders
  * Gooch
  * Screen-Space Ambiet Occlusion shaders
  * Shadows
* Variants:
  * iOS 
  * Android
  * WebGL (three.js?)
  * Also, decouple rendering and scene/simulation libraries
* Unit testing. I probably need to start that now.
* Make things more modular. Be able to run some modules as threads or separate processes. (Perhaps use protobuf to pass data around?)
* More in-depth on GLSL? [DINDINX](http://dindinx.net/OpenGL/index.php?menu=exemples&submenu=shaders).
* Other GLSL tutorials (e.g. [Lighthouse3d](http://www.lighthouse3d.com/))
* Embedded python interpreter? 

This may migrate to a entirely different project as it grows.

Platforms
---------

Mac OSX Mavericks
Ubuntu 12.04

Dependencies
------------

* GLEW
* GLFW
* google-gflags
* google-glog

Build
-----

    mkdir build
    cd build
    cmake ..
    make install

Run
---

From your build directory: 

    cd lesson{2.1,3,4,5,6}
    ./lesson{2,3,4,5,6}
    
Flags aren't always working quite right. So, use the environment variable appraoch if it complains. For example: 

    GLOG_v=1 ./lesson5   # show extra logging
    GLOG_logtostderr ./lesson4 # log to standard error instead of to files
