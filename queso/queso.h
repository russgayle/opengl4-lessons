#ifndef _COMMON_H_
#define _COMMON_H_

#include "common.h"

namespace queso {
  
  // Hooks up all the gadgetry for my apps. For GLFW3 (for now?). 
  GLFWwindow* init(int argc, char* argv[]);  

  // The error callback to be used.
  void error_callback(int error, const char* description);
}

#endif