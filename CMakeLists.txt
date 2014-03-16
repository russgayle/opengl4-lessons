# Top-level CMakeLists

cmake_minimum_required(VERSION 2.8)
project(OpenGL4-Tutorial)

# Install locally, by default
set(CMAKE_INSTALL_PREFIX .)

# Support library
add_subdirectory(queso)

# Lessons/executables
# Note: Lesson 1 and Lesson 2 do not use CMake.
add_subdirectory(lesson2.1)
add_subdirectory(lesson3)
add_subdirectory(lesson4)
add_subdirectory(lesson5)
add_subdirectory(lesson6)

# More adhoc explorations
add_subdirectory(lighting)
