// Lesson 2: http://antongerdelan.net/opengl/glcontext2.html

#include <fstream>

// Queso!
#include "queso.h"
#include "shader.h"
#include "shader_program.h"

// Globals
int width = 640;
int height = 480;
bool wireframe = false;
GLFWwindow* window;

void window_callback(GLFWwindow* window, int p_width, int p_height) {
  width = p_width;
  height = p_height;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, 1);
  }

  if (key == GLFW_KEY_W && action == GLFW_PRESS) {
    if (!wireframe) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      LOG(INFO) << "Wireframe: ON";
    } else {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      LOG(INFO) << "Wireframe: OFF";
    }
    wireframe = !wireframe;
  }
}

int main(int argc, char* argv[]) {

  window = queso::init(argc, argv, "Lesson 4: Vertex buffers");

  // Register callbacks
  glfwSetWindowSizeCallback(window, window_callback);
  glfwSetKeyCallback(window, key_callback);

  // Setup OpenGL
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);  // TODO(rgayle): Is this necessary?

  // Set up a triangle.
  float points[] = {
     0.0f,   0.5f, 0.0f,
     0.5f,  -0.5f, 0.0f,
    -0.5f,  -0.5f, 0.0f
  };

  float colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
  };

  unsigned int points_vbo = 0;
  glGenBuffers(1, &points_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
  glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

  unsigned int colors_vbo = 0;
  glGenBuffers(1, &colors_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
  glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colors, GL_STATIC_DRAW);

  unsigned int vao = 0;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL); // points are idx 0
  glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL); // colors are idx 1

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

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
  }

  glfwTerminate();
  return 0;
}

