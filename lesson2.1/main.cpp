// Lesson 2: http://antongerdelan.net/opengl/glcontext2.html

#include <fstream>

// Queso!
#include "queso.h"

// Globals
int width = 640;
int height = 480;

void window_callback(GLFWwindow* window, int p_width, int p_height) {
  width = p_width;
  height = p_height;
}

void updateFPSCounter(GLFWwindow* window) {
  static double previous = glfwGetTime();
  static int frame_count;
  double current = glfwGetTime();
  double elapsed = current - previous;
  if (elapsed > 0.25) {
    previous = current;
    double fps = (double)frame_count / elapsed;
    std::ostringstream oss;
    oss << "Lesson2.1: " << fps << " fps";
    glfwSetWindowTitle(window, oss.str().c_str());
    frame_count = 0;
  }
  frame_count++;
}

int main(int argc, char* argv[]) {

  GLFWwindow* window = queso::init(argc, argv, "Lesson 2(.1): Basic setup");

  // Setup OpenGL
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);  // TODO(rgayle): Is this necessary?

  // Do stuff.

  // First shape!
  float points[] = {
     0.25f,  0.25f, 0.0f,
     0.25f, -0.25f, 0.0f,
    -0.25f, -0.25f, 0.0f,

    -0.25f, -0.25f, 0.0f,
    -0.25f,  0.25f, 0.0f,
     0.25f,  0.25f, 0.0f
  };

  // Set up a Vertex Buffer Object (VBO)
  unsigned int vbo = 0;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), points, GL_STATIC_DRAW);

  // Set up a Vertex Attribute Object (VAO) to keep track of our VBOs
  unsigned int vao = 0;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  // Second shape!
  float points2[] = {
     0.5f,  -0.5f, 0.0f,
     1.0f,  -0.5f, 0.0f,
     0.75f,  0.0f, 0.0f
  };

  unsigned int vbo2 = 1;
  glGenBuffers(1, &vbo2);
  glBindBuffer(GL_ARRAY_BUFFER, vbo2);
  glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points2, GL_STATIC_DRAW);

  unsigned int vao2 = 1;
  glGenVertexArrays(1, &vao2);
  glBindVertexArray(vao2);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vbo2);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  // Load shaders, and compile
  queso::Shader vs1("vs.glsl", queso::VERTEX, true);
  queso::Shader vs2("vs2.glsl", queso::VERTEX, true);
  queso::Shader fs1("fs.glsl", queso::FRAGMENT, true);
  queso::Shader fs2("fs2.glsl", queso::FRAGMENT, true);

  // Make programs
  queso::ShaderProgram prog1(vs1, fs1);
  queso::ShaderProgram prog2(vs2, fs2);

  // Let's see what they're about
  prog1.printAllInfo();
  prog2.printAllInfo();

  // Other setup
  glClearColor(0.1f, 0.1f, 0.3f, 1.0f);

  // Set up our drawing loop
  while (!glfwWindowShouldClose(window)) {
    updateFPSCounter(window);

    // Clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, width, height);

    // Shape 1
    prog1.use();
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Shape 2
    prog2.use();
    glBindVertexArray(vao2);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Put it on the screen!
    glfwSwapBuffers(window);

    // Poll for input handling
    glfwPollEvents();

    // Check for escape-key press to close window
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
      glfwSetWindowShouldClose(window, 1);
    }
  }

  glfwTerminate();
  return 0;
}

