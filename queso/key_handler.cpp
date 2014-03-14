#include "key_handler.h"

void queso::keyHandler(GLFWwindow* window, int key, int scancode, int action, int mods) {
  static bool wireframe = false;

  // Exit
  if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, 1);
  }

  // Toggle wireframe
  if (key == GLFW_KEY_M && action == GLFW_PRESS) {
    if (!wireframe) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      VLOG(1) << "Wireframe: ON";
    } else {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      VLOG(1) << "Wireframe: OFF";
    }
    wireframe = !wireframe;
  }

  // Toggle pause
  if (key == GLFW_KEY_P && action == GLFW_PRESS) {
    queso::paused = !queso::paused;

    if (queso::paused) VLOG(1) << "Paused.";
    else VLOG(1) << "Playing.";
  }

  // Camera
  if (key == GLFW_KEY_A && action == GLFW_PRESS) 
    queso::camPos[0] -= camSpeed;
  if (key == GLFW_KEY_D && action == GLFW_PRESS)
    queso::camPos[0] += camSpeed;
  if (key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS)
    queso::camPos[1] += camSpeed;
  if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS)
    queso::camPos[1] -= camSpeed;
  if (key == GLFW_KEY_W && action == GLFW_PRESS)
    queso::camPos[2] -= camSpeed;
  if (key == GLFW_KEY_S && action == GLFW_PRESS)
    queso::camPos[2] += camSpeed;

  if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
    queso::camYaw += camRotSpeed;
  if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    queso::camYaw -= camRotSpeed;
}

