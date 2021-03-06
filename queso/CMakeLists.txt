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

# glew
if(APPLE)
  find_package(GLEW REQUIRED)
  include_directories(${GLEW_INCLUDE_DIR})
  set(QUESO_DEPS ${QUESO_DEPS} ${GLEW_LIBRARIES})
elseif(UNIX)
  pkg_search_module(GLEW REQUIRED glew)
  include_directories(${GLEW_INCLUDE_DIRS})
  set(QUESO_DEPS ${QUESO_DEPS} ${GLEW_LIBRARIES})
endif()

# glfw3
# export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /usr/local/lib)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
set(QUESO_DEPS ${QUESO_DEPS} glfw3)

# glm -- by design it's in this location
include_directories(${OpenGL4-Tutorial_SOURCE_DIR}/glm)

# build it, and they will come
add_library(queso
  app.h             app.cpp
  common.h          common.cpp
  drawable.h        drawable.cpp
  key_handler.h     key_handler.cpp
  queso.h           
  shader.h          shader.cpp
  shader_program.h  shader_program.cpp
  utils.h           utils.cpp
)

target_link_libraries(queso ${QUESO_DEPS})

file(GLOB shaders "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*")
install(FILES ${shaders} DESTINATION shaders)

install(TARGETS queso
  RUNTIME DESTINATION ${CMAKE_BINARY_DIR}
  LIBRARY DESTINATION ${CMAKE_BINARY_DIR}
  ARCHIVE DESTINATION ${CMAKE_BINARY_DIR}
)
