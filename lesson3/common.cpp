#include "common.h"

void queso::init(int argc, char* argv[]) {
  // Init google flags
  google::SetVersionString("0.0.3");
  google::ParseCommandLineFlags(&argc, &argv, true);

  // Init google logging
  FLAGS_log_link = ".";
  FLAGS_alsologtostderr = true;
  FLAGS_colorlogtostderr = true;
  google::InitGoogleLogging(argv[0]);

  // GLFW
  LOG(INFO) << "Starting GLFW... ";
  glfwSetErrorCallback(queso::error_callback);

  if (!glfwInit()) {
    std::cerr << "Fatal." << std::endl;
    LOG(FATAL) << "Fatal: Could not start GLFW3";
  }

  // Mac
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Preferences
  glfwWindowHint(GLFW_SAMPLES, 4); // anti-aliasing
}

void queso::error_callback(int error, const char* description) {
  LOG(ERROR) << "[GLFW3 ERROR #" << error << "] " << description;
}
