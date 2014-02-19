#include "common.h"

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
 
  LOG(INFO) << argv[0] << " completed. Thanks for playing.";
}
