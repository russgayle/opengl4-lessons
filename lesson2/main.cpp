// Lesson 1: http://antongerdelan.net/opengl/hellotriangle.html

// Graphics. 
#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

// Google stack
#include <gflags/gflags.h>
#include <glog/logging.h>

// Standard.
#include <iostream>
#include <fstream>

// Globals
int width = 640;
int height = 480;

void error_callback(int error, const char* description) {
  LOG(ERROR) << "[GLFW ERROR " << error << "] " << description; 
}

void window_callback(GLFWwindow* window, int p_width, int p_height) {
  width = p_width;
  height = p_height;
  
  // Ordinarily, update perspective matrices here.
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
    oss << "Lesson2: " << fps << " fps";
    glfwSetWindowTitle(window, oss.str().c_str());
    frame_count = 0;
  }
  frame_count++;
}

int main(int argc, char* argv[]) {
  
  // Init google stack
  google::SetVersionString("0.0.2");
  google::ParseCommandLineFlags(&argc, &argv, true);

  // Init logging
  FLAGS_log_link = ".";
  FLAGS_alsologtostderr = true;
  FLAGS_colorlogtostderr = true;
  google::InitGoogleLogging(argv[0]);

  // Set up error handling for GLFW
  LOG(INFO) << "Starting GLFW... ";
  glfwSetErrorCallback(error_callback);

  // Start GL context (using GLFW)
  if (!glfwInit()) {
    LOG(FATAL) << "Fatal: Could not start GLFW3";
  }
  
  // Mac hints
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // GLFW setup
  glfwWindowHint(GLFW_SAMPLES, 4); // anti-aliasing

  // Start full screen
  GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL4: Lesson 2", NULL, NULL);
  if (!window) {
    glfwTerminate();
    LOG(FATAL) << "Fatal: Could not open window with GLFW3" << std::endl;
  }
  glfwSetWindowSizeCallback(window, window_callback); 

  glfwMakeContextCurrent(window);

  // GLEW!
  glewExperimental = GL_TRUE;
  glewInit();

  // Fun. 
  const GLubyte* renderer = glGetString(GL_RENDERER);
  const GLubyte* version = glGetString(GL_VERSION);
  LOG(INFO) << "Renderer: " << renderer;
  LOG(INFO) << "OpenGL version supported: " << version;

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

  // Load vertex shader
  std::ifstream vsFile;
  std::string vsLines;
  vsFile.open("vs.glsl");
  if (!vsFile.is_open()) {
    LOG(FATAL) << "Fatal: Could not open vs.glsl";
  } else {
    std::string line;
    while(getline(vsFile, line)) {
      vsLines += line + "\n";
    }
    vsFile.close();
  }
  const char* vsSource = vsLines.c_str();

  // vs2
  std::string vs2Lines;
  vsFile.open("vs2.glsl");
  if (!vsFile.is_open()) {
    LOG(FATAL) << "Fatal: Could not open vs2.glsl";
  } else {
    std::string line;
    while (getline(vsFile, line)) {
      vs2Lines += line + "\n";
    }
    vsFile.close();
  }
  const char* vs2Source = vs2Lines.c_str();

  //std::cout << "Vertex Shader:" << std::endl;
  //std::cout << vsSource << std::endl;

  // Load fragment shader
  std::ifstream fsFile;
  std::string fsLines;
  fsFile.open("fs.glsl");
  if (!fsFile.is_open()) {
    LOG(FATAL) << "Fatal: Could not open fs.glsl";
  } else {
    std::string line;
    while(getline(fsFile, line)) {
      fsLines += line + "\n";
    }
    fsFile.close();
  }
  const char* fsSource = fsLines.c_str();

  std::string fs2Lines;
  fsFile.open("fs2.glsl");
  if (!fsFile.is_open()) {
    LOG(FATAL) << "Fatal: Could not open fs2.glsl";
  } else {
    std::string line;
    while(getline(fsFile, line)) {
      fs2Lines += line + "\n";
    }
    fsFile.close();
  }
  const char* fs2Source = fs2Lines.c_str();
  //std::cout << "Fragment Shader:" << std::endl;
  //std::cout << fsSource << std::endl; 

  // Compile shaders
  unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vsSource, NULL);
  glCompileShader(vs);

  unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fsSource, NULL);
  glCompileShader(fs);

  unsigned int vs2 = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs2, 1, &vs2Source, NULL);
  glCompileShader(vs2);

  unsigned int fs2 = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs2, 1, &fs2Source, NULL);
  glCompileShader(fs2);

  // Attach shaders to our program
  unsigned int shader_program = glCreateProgram();
  glAttachShader(shader_program, fs);
  glAttachShader(shader_program, vs);
  glLinkProgram(shader_program);

  unsigned int shader_program2 = glCreateProgram();
  glAttachShader(shader_program2, fs2);
  glAttachShader(shader_program2, vs2);
  glLinkProgram(shader_program2);

  // Other setup
  glClearColor(0.1f, 0.1f, 0.3f, 1.0f);

  // Set up our drawing loop
  while (!glfwWindowShouldClose(window)) {
    updateFPSCounter(window);

    // Clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, width, height);

    // Shape 1
    glUseProgram(shader_program);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Shape 2
    glUseProgram(shader_program2);
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

