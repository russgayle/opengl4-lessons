#include "common.h"

int width = 640;
int height = 480; 

void window_callback(GLFWwindow* window, int p_width, int p_height) {
  width = p_width;
  height = p_height;
}

int main(int argc, char* argv[])
{
  queso::init(argc, argv);

  // Set up a window
  GLFWwindow* window = glfwCreateWindow(width, height, "Gooey cheese. Lesson 3", NULL, NULL);
  if (!window) {
    glfwTerminate();
    LOG(FATAL) << "Could not open a window with GLFW3";
  }
  glfwSetWindowSizeCallback(window, window_callback);
  glfwMakeContextCurrent(window);

  // Yay, window is up. 
  glewExperimental = GL_TRUE;
  glewInit();

  // Query system
  const GLubyte* renderer = glGetString(GL_RENDERER);
  const GLubyte* version = glGetString(GL_VERSION);
  LOG(INFO) << "Renderer: " << renderer;
  LOG(INFO) << "OpenGL version supported: " << version;

  LOG(INFO) << argv[0] << " completed. Thanks for playing.";
}
