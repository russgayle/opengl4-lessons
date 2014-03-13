#ifndef _QUESO_COMMON_H_
#define _QUESO_COMMON_H_

// std
#include <map>
#include <math.h>
#include <string>
#include <vector>

// google
#include <gflags/gflags.h>    // Google gflags
#include <glog/logging.h>     // Google logging

// opengl and related
#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// Let apps use queso's globals
namespace queso {

  // Play/pause
  extern bool paused;

  // Camera settings
  extern float camPos[];
  extern float camYaw;
  extern float camSpeed;
  extern float camRotSpeed;
}

#endif // _QUESO_COMMON_H_
