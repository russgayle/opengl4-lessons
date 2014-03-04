// Lesson 2: http://antongerdelan.net/opengl/glcontext2.html

#include <fstream>

// Queso!
#include "queso.h"

// Globals
int width = 640;
int height = 480;
bool wireframe = false;
GLFWwindow* window;

void window_callback(GLFWwindow* window, int p_width, int p_height) {
  width = p_width;
  height = p_height;
}

int main(int argc, char* argv[]) {

  window = queso::init(argc, argv, "Lesson 4: Vertex buffers");

  // Register callbacks
  glfwSetWindowSizeCallback(window, window_callback);

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

  // Simple vertex transform
  // Note: It's in column order. So, it would really look like: 
  // | 1   0   0 0.5 |
  // | 0   1   0   0 |
  // | 0   0   1   0 |
  // | 0   0   0   1 | 
  float matrix[] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f, 
    0.0f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.0f, 0.0f, 1.0f
  };
  prog.setUniform("matrix", queso::FOUR_BY_FOUR, GL_FALSE, matrix);

  // Other setup
  glClearColor(0.1f, 0.1f, 0.3f, 1.0f);

  // Variables for moving the triangle. 
  float speed = 1.0f;
  float last_pos = matrix[12];

  // Set up our drawing loop
  while (!glfwWindowShouldClose(window)) {

    // Timer, for animations.
    static double previousTime = glfwGetTime();
    double currTime = glfwGetTime();
    double elapsedTime = currTime - previousTime;
    previousTime = currTime;

    // ReverseDirection if we get too far left or right
    if (last_pos > 1.0f) {
      last_pos = 1.0;
      speed *= -1;
    } else if (last_pos < -1.0f) {
      last_pos = -1.0f;
      speed *= -1;
    }

    // Update our matrix
    if (!queso::paused) { 
      matrix[12] = elapsedTime * speed + last_pos;
      last_pos = matrix[12];

      prog.setUniform("matrix", queso::FOUR_BY_FOUR, GL_FALSE, matrix);
    }

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

