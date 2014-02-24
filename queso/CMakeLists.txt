cmake_minimum_required(VERSION 2.8)

project(queso)

# Base frameworks
if(APPLE) # sarita's mac

  find_library(COCOA_LIBRARY Cocoa)
  find_library(OpenGL_LIBRARY OpenGL)
  find_library(IOKit_LIBRARY IOKit)
  find_library(QuartzCore_LIBRARY QuartzCore)

  set(QUESO_DEPS ${QUESO_DEPS} ${COCOA_LIBRARY} ${OpenGL_LIBRARY} ${IOKit_LIBRARY} ${QuartzCore_LIBRARY})

elseif(UNIX) # standard ubuntu

  set(FIND_LIBRARY_USE_LIB64_PATHS true)

  find_package(X11 REQUIRED)
  set(QUESO_DEPS ${QUESO_DEPS} ${X11_X11_LIB} ${X11_Xrandr_LIB} ${X11_Xinput_LIB} Xxf86vm)

  find_package(Threads REQUIRED)
  set(QUESO_DEPS ${QUESO_DEPS} ${CMAKE_THREAD_LIBS_INIT})

  find_library(RT_LIBRARY rt)
  set(QUESO_DEPS ${QUESO_DEPS} ${RT_LIBRARY})

  find_library(MATH_LIBRARY m)
  set(QUESO_DEPS ${QUESO_DEPS} ${MATH_LIBRARY})

  # TODO(rgayle): Find some better way of doing this.
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L/usr/lib -L/usr/lib64 -L/usr/local/lib")

endif()

# Prerequisites (works better on MacOS?)
find_package(PkgConfig REQUIRED)

# google-gflags
pkg_search_module(GFLAGS REQURED libgflags)
include_directories(${GFLAGS_INCLUDE_DIRS})
set(QUESO_DEPS ${QUESO_DEPS} ${GFLAGS_LIBRARIES})

# google-glog
pkg_search_module(GLOG REQUIRED libglog)
include_directories(${GLOG_INCLUDE_DIRS})
set(QUESO_DEPS ${QUESO_DEPS} ${GLOG_LIBRARIES})
link_directories(${GLOG_LIBRARY_DIRS})

# glew
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})
set(QUESO_DEPS ${QUESO_DEPS} ${GLEW_LIBRARIES})
link_directories(${GLEW_LIBRARY_DIRS})

# glfw3
# export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /usr/local/lib)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
set(QUESO_DEPS ${QUESO_DEPS} glfw3)

# build it, and they will come
add_library(queso
  common.h
  queso.h           queso.cpp
  shader.h          shader.cpp
  shader_program.h  shader_program.cpp
)

target_link_libraries(queso ${QUESO_DEPS})

install(TARGETS queso
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
