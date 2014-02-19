#include "common.h"

void queso::init(int argc, char* argv[]) {
  // Init google flags
  google::SetVersionString("0.0.3");
  google::ParseCommandLineFlags(&argc, &argv, true);

  // Google logging preferences
  FLAGS_log_link = ".";
  FLAGS_alsologtostderr = true;
  FLAGS_colorlogtostderr = true;
  google::InitGoogleLogging(argv[0]);

  // GLFW state
  glfwSetErrorCallback(queso::error_callback);

  LOG(INFO) << "Starting GLFW.. ";
  if (!glfwInit()) {
    LOG(FATAL) << "Fatal: Could not start GLFW3";
  }
  LOG(INFO) << "... done!";

  // Mac
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Preferences
  glfwWindowHint(GLFW_SAMPLES, 4); // anti-aliasing

  //// GLEW
  //LOG(INFO) << "Starting GLEW.. ";
  //glewExperimental = GL_TRUE;
  //glewInit();
  //LOG(INFO) << "... done!";

  //// Print some basic info
  //const GLubyte* renderer = glGetString(GL_RENDERER);
  //const GLubyte* version = glGetString(GL_VERSION);
  //LOG(INFO) << "Renderer: " << renderer;
  //LOG(INFO) << "OpenGL version supported: " << version;
}

void queso::error_callback(int error, const char* description) {
  LOG(ERROR) << "[GLFW3 ERROR #" << error << "] " << description;
}
