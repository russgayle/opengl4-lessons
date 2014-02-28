#include "key_handler.h"

void queso::keyHandler(GLFWwindow* window, int key, int scancode, int action, int mods) {
  static bool wireframe = false;

  if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, 1);
  }

  if (key == GLFW_KEY_W && action == GLFW_PRESS) {
    if (!wireframe) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      VLOG(1) << "Wireframe: ON";
    } else {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      VLOG(1) << "Wireframe: OFF";
    }
    wireframe = !wireframe;
  }
}

