// Lesson 2: http://antongerdelan.net/opengl/glcontext2.html

#include <fstream>

// Queso!
#include "queso.h"
#include "shader.h"
#include "shader_program.h"

// Globals
int width = 640;
int height = 480;

void window_callback(GLFWwindow* window, int p_width, int p_height) {
  width = p_width;
  height = p_height;
}

int main(int argc, char* argv[]) {

  GLFWwindow* window = queso::init(argc, argv);

  // Setup OpenGL
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);  // TODO(rgayle): Is this necessary?

  // Set up a triangle.
  float points[] = {
     0.0f,   0.5f, 0.0f,
     0.5f,  -0.5f, 0.0f,
    -0.5f,  -0.5f, 0.0f
  };

  unsigned int vbo = 1;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

  unsigned int vao = 1;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  // Shader, program
  queso::Shader vs("shaders/no_perspective.vert", queso::VERTEX, true);
  queso::Shader fs("shaders/uniform_color.frag", queso::FRAGMENT, true);

  queso::ShaderProgram prog(vs, fs);
  prog.use();
  prog.setUniform("inputColor", 1.0f, 0.0f, 0.0f, 1.0f); // red

  // Other setup
  glClearColor(0.1f, 0.1f, 0.3f, 1.0f);

  // Set up our drawing loop
  while (!glfwWindowShouldClose(window)) {
    // Clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, width, height);

    // Shape 1
    prog.use();
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);

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

