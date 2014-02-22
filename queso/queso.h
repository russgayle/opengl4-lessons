#ifndef _COMMON_H_
#define _COMMON_H_

// std
#include <string>

// google
#include <gflags/gflags.h>    // Google gflags
#include <glog/logging.h>     // Google logging

// opengl
#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

namespace queso {
  
  // Hooks up all the gadgetry for my apps. For GLFW3 (for now?). 
  GLFWwindow* init(int argc, char* argv[]);  

  // The error callback to be used.
  void error_callback(int error, const char* description);
}

#endif
