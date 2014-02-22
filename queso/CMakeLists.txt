cmake_minimum_required(VERSION 2.8)

project(queso)

# Base frameworks
if(APPLE)
  find_library(COCOA_LIBRARY Cocoa)
  find_library(OpenGL_LIBRARY OpenGL)
  find_library(IOKit_LIBRARY IOKit)
  find_library(QuartzCore_LIBRARY QuartzCore)
  
  set(EXTRA_DEPS ${EXTRA_DEPS} ${COCOA_LIBRARY} ${OpenGL_LIBRARY} ${IOKit_LIBRARY} ${QuartzCore_LIBRARY})
endif()

# Prerequisites
find_package(PkgConfig REQUIRED)

# google-gflags
pkg_search_module(GFLAGS REQURED libgflags)
include_directories(${GFLAGS_INCLUDE_DIRS})

# google-glog
pkg_search_module(GLOG REQUIRED libglog)
include_directories(${GLOG_INCLUDE_DIRS})

# glew
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})

# glfw3
# export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /usr/local/lib)
pkg_search_module(GLFW REQUIRED glfw3)

# set includes
include_directories(${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})

# build it, and they will come
add_library(queso 
  common.h          common.cpp
  shader.h          shader.cpp
  shader_program.h  shader_program.cpp
)

#target_link_libraries(lesson3 ${GLEW_LIBRARIES} ${GLFW_LIBARIES} ${MACOS_LIBS})
target_link_libraries(queso ${GLEW_LIBRARIES} glfw3 ${GFLAGS_LIBRARIES} ${GLOG_LIBRARIES} ${EXTRA_DEPS})
