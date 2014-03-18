#include "app.h"

#include "key_handler.h"

queso::App::App(int argc, char* argv[], const std::string& appName, bool appendFPS) 
  : m_appName(appName), m_appendFPSToTitle(appendFPS), m_width(640), m_height(480)  {
  m_window = NULL;
  init(argc, argv);
}

void queso::App::init(int argc, char* argv[]) {
  // Google flags
  google::SetVersionString("0.0.4");
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

#ifdef __APPLE__
  // Mac
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

  // Preferences
  glfwWindowHint(GLFW_SAMPLES, 4); // anti-aliasing

  // Go ahead and make a window
  m_window = glfwCreateWindow(m_width, m_height, m_appName.c_str(), NULL, NULL);
  if (!m_window) {
    glfwTerminate();
    LOG(FATAL) << "Could not open a window with GLFW3";
  }
  glfwMakeContextCurrent(m_window);

  // GLEW
  LOG(INFO) << "Starting GLEW.. ";
  glewExperimental = GL_TRUE;
  glewInit();
  LOG(INFO) << "... done!";

  // Print some basic info
  const GLubyte* renderer = glGetString(GL_RENDERER);
  const GLubyte* version = glGetString(GL_VERSION);
  LOG(INFO) << "Renderer: " << renderer;
  LOG(INFO) << "OpenGL version supported: " << version;

  // Default handlers
  glfwSetKeyCallback(m_window, queso::keyHandler);
  // glfwSetFramebufferSizeCallback

  // OpenGL setup
  glfwGetFramebufferSize(m_window, &m_width, &m_height);
  glViewport(0, 0, m_width, m_height); 
  glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
}

void queso::App::run() {

  // UGLY.
  // Projection
  glm::mat4 proj = glm::perspective(3.1415192f / 3.0f, (float) m_width / (float) m_height, 0.1f, 1000.0f);

  // UGLY. 
  // Model
  glm::mat4 model = glm::mat4(1.0); 

  while(!glfwWindowShouldClose(m_window)) {

    // Update title with FPS, if desired
    if (m_appendFPSToTitle) {
      static double previousTime = glfwGetTime();
      static int frameCount;
      double currTime = glfwGetTime();
      double elapsedTime = currTime - previousTime;

      if (elapsedTime > 0.25) {
        previousTime = currTime;
        double fps = (double)frameCount / elapsedTime;
        std::ostringstream oss;
        oss << m_appName << " [" << fps << " fps]";
        glfwSetWindowTitle(m_window, oss.str().c_str());
        frameCount = 0;
      }
      frameCount++;
    }

    // Per iteration OpenGL setup 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, m_width, m_height);

    // Update our view
    glm::mat4 translate = glm::translate(
      glm::mat4(1.0f), glm::vec3(-queso::camPos[0], -queso::camPos[1], -queso::camPos[2]));
    glm::mat4 view = glm::rotate(translate, queso::camYaw, glm::vec3(0.0f, 1.0f, 0.0f));

    // Finally draw everything
    for(size_t i = 0; i < m_drawables.size(); i++) {

      // Ew. Perhaps we make all vertex shaders accept these?
      m_programs[i]->setUniform("view", queso::FOUR_BY_FOUR, GL_FALSE, glm::value_ptr(view));
      m_programs[i]->setUniform("proj", queso::FOUR_BY_FOUR, GL_FALSE, glm::value_ptr(proj));
      m_programs[i]->setUniform("model", queso::FOUR_BY_FOUR, GL_FALSE, glm::value_ptr(model));

      m_programs[i]->use();
      m_drawables[i]->draw();
    }

    // End loop
    glfwSwapBuffers(m_window); 
    glfwPollEvents();
  }

  glfwTerminate();
}

GLFWwindow* queso::init(int argc, char* argv[], const std::string& appName) {
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

#ifdef __APPLE__
  // Mac
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

  // Preferences
  glfwWindowHint(GLFW_SAMPLES, 4); // anti-aliasing

  // Go ahead and make a window
  GLFWwindow* window = glfwCreateWindow(640, 480, appName.c_str(), NULL, NULL);
  if (!window) {
    glfwTerminate();
    LOG(FATAL) << "Could not open a window with GLFW3";
  }
  glfwMakeContextCurrent(window);

  // GLEW
  LOG(INFO) << "Starting GLEW.. ";
  glewExperimental = GL_TRUE;
  glewInit();
  LOG(INFO) << "... done!";

  // Print some basic info
  const GLubyte* renderer = glGetString(GL_RENDERER);
  const GLubyte* version = glGetString(GL_VERSION);
  LOG(INFO) << "Renderer: " << renderer;
  LOG(INFO) << "OpenGL version supported: " << version;

  // Default handlers
  glfwSetKeyCallback(window, queso::keyHandler);

  return window;
}

void queso::error_callback(int error, const char* description) {
  LOG(ERROR) << "[GLFW3 ERROR #" << error << "] " << description;
}
