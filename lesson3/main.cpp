#include "queso.h"
#include "shader.h"
#include "shader_program.h"

int width = 640;
int height = 480; 

void window_callback(GLFWwindow* window, int p_width, int p_height) {
  width = p_width;
  height = p_height;
}

int main(int argc, char* argv[])
{
  GLFWwindow* window = queso::init(argc, argv);
  glfwSetWindowSizeCallback(window, window_callback);

  // Set up our shaders
  queso::Shader vert("shaders/no_perspective.vert", queso::VERTEX, true); 
  queso::Shader frag("shaders/uniform_color.frag", queso::FRAGMENT, true);

  // Program!
  queso::ShaderProgram prog(vert, frag);
  prog.printAllInfo();

  // Testing.
  unsigned int inputColorLocation = glGetUniformLocation(prog.getHandle(), "inputColor");
  LOG(INFO) << "inputColor at location " << inputColorLocation;
  prog.use();
  glUniform4f(inputColorLocation, 1.0f, 0.0f, 0.0f, 1.0f); // red
 
  LOG(INFO) << argv[0] << " completed. Thanks for playing.";
}
