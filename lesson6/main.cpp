// Lesson 2: http://antongerdelan.net/opengl/glcontext2.html

#include <fstream>

// Setup GLM
#define GLM_FORCE_RADIANS

// Queso!
#include "queso.h"

// GLM extras
#include <glm/gtc/matrix_transform.hpp>   // glm::translate, glm::rotate, glm::scale
#include <glm/gtc/type_ptr.hpp>           // glm::value_ptr

// Globals
int width = 640;
int height = 480;
bool wireframe = false;
GLFWwindow* window;

void framebuffer_callback(GLFWwindow* window, int p_width, int p_height) {
  width = p_width;
  height = p_height;
}

int main(int argc, char* argv[]) {

  window = queso::init(argc, argv, "Lesson 6: Virtual Camera");

  // TODO(rgayle): Move this logic into queso.
  // Fix for retina displays
  glfwGetFramebufferSize(window, &width, &height);

  // Register callbacks
  glfwSetFramebufferSizeCallback(window, framebuffer_callback);

  // Setup OpenGL
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);  // TODO(rgayle): Is this necessary?

  // Set up a triangle.
  queso::Drawable triangle;

  float points[] = {
     0.0f,   0.5f, 0.0f,
     0.5f,  -0.5f, 0.0f,
    -0.5f,  -0.5f, 0.0f
  };
  triangle.addVertices(9, points);

  float colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
  };
  triangle.addColors(9, colors);
  
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  // Shaders and shader program
  queso::Shader vs("shaders/perspective.vert", queso::VERTEX, true);
  queso::Shader fs("shaders/uniform_color.frag", queso::FRAGMENT, true);
  queso::ShaderProgram prog(vs, fs);

  // Projection
  glm::mat4 projection = glm::perspective(3.141592f / 3.0f, 640.0f / 480.0f, 0.1f, 100.0f);

  // View
  glm::mat4 translate = glm::translate(
    glm::mat4(1.0f), glm::vec3(-queso::camPos[0], -queso::camPos[1], -queso::camPos[2]));
  glm::mat4 view = glm::rotate(translate, queso::camYaw, glm::vec3(0.0f, 1.0f, 0.0f));

  // Set uniforms
  prog.setUniform("view", queso::FOUR_BY_FOUR, GL_FALSE, glm::value_ptr(view));
  prog.setUniform("proj", queso::FOUR_BY_FOUR, GL_FALSE, glm::value_ptr(projection));

  // Other setup
  glClearColor(0.1f, 0.1f, 0.3f, 1.0f);

  // Set up our drawing loop
  while (!glfwWindowShouldClose(window)) {

    // Timer -- to update FPS
    static double previousTime = glfwGetTime();
    static int frameCount;
    double currTime = glfwGetTime();
    double elapsedTime = currTime - previousTime;

    if (elapsedTime > 0.25) {
      previousTime = currTime;
      double fps = (double)frameCount / elapsedTime;
      std::ostringstream oss;
      oss << "Lesson 6: Virtual Camera [" << fps << " fps]";
      glfwSetWindowTitle(window, oss.str().c_str());
      frameCount = 0;
    }
    frameCount++;

    // Clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, width, height);

    // Shape 1
    prog.use();
    triangle.draw();

    // Put it on the screen!
    glfwSwapBuffers(window);

    // Poll for input handling
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

