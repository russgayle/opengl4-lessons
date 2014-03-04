#ifndef _QUESO_COMMON_H_
#define _QUESO_COMMON_H_

// std
#include <math.h>
#include <string>

// google
#include <gflags/gflags.h>    // Google gflags
#include <glog/logging.h>     // Google logging

// opengl
#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

// common queso state
// TODO(rgayle): This really isn't safe.
namespace queso {
  static bool paused;
} // end namespace queso


#endif // _QUESO_COMMON_H_
