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
  bool moveCamera = action == GLFW_PRESS || action == GLFW_REPEAT;
  static double previousTime = glfwGetTime();
  double currTime = glfwGetTime();
  double elapsedTime = currTime - previousTime;

  static bool cameraMoved = false;
  if (key == GLFW_KEY_A && moveCamera) {
    queso::camPos[0] -= camSpeed * elapsedTime; cameraMoved = true;
  }
  if (key == GLFW_KEY_D && moveCamera) {
    queso::camPos[0] += camSpeed * elapsedTime; cameraMoved = true;
  }
  if (key == GLFW_KEY_PAGE_UP && moveCamera) {
    queso::camPos[1] += camSpeed * elapsedTime; cameraMoved = true;
  }
  if (key == GLFW_KEY_PAGE_DOWN && moveCamera) {
    queso::camPos[1] -= camSpeed * elapsedTime; cameraMoved = true;
  }
  if (key == GLFW_KEY_W && moveCamera) {
    queso::camPos[2] -= camSpeed * elapsedTime; cameraMoved = true;
  }
  if (key == GLFW_KEY_S && moveCamera) {
    queso::camPos[2] += camSpeed * elapsedTime; cameraMoved = true;
  }
  if (key == GLFW_KEY_LEFT && moveCamera) {
    queso::camYaw += camRotSpeed * elapsedTime; cameraMoved = true;
  }
  if (key == GLFW_KEY_RIGHT && moveCamera) {
    queso::camYaw -= camRotSpeed * elapsedTime; cameraMoved = true;
  }

  if (cameraMoved && action == GLFW_RELEASE) {
    previousTime = currTime;
    cameraMoved = false;
  }
}


