// Lesson 1: http://antongerdelan.net/opengl/hellotriangle.html

// Graphics. 
#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

// Standard.
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {

  // Start GL context (using GLFW)
  if (!glfwInit()) {
    std::cerr << "Error: Problem starting GLFW3" << std::endl;
    return 1;
  }
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(640, 480, "Hello, Triangle!", NULL, NULL);
  if (!window) {
    std::cerr << "Error: Could not open window with GLFW3" << std::endl;
    glfwTerminate();
    return 1;
  }

  glfwMakeContextCurrent(window);

  // GLEW!
  glewExperimental = GL_TRUE;
  glewInit();

  // Fun. 
  const GLubyte* renderer = glGetString(GL_RENDERER);
  const GLubyte* version = glGetString(GL_VERSION);
  std::cout << "Renderer: " << renderer << std::endl;
  std::cout << "OpenGL version supported: " << version << std::endl;

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
    std::cerr << "Could not open vs.glsl" << std::endl;
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
    std::cerr << "Could not open vs2.glsl" << std::endl;
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
    std::cerr << "Could not open fs.glsl" << std::endl;
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
    std::cerr << "Could not open fs2.glsl" << std::endl;
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
    // Clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Shape 1
    glUseProgram(shader_program);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Shape 2
    glUseProgram(shader_program2);
    glBindVertexArray(vao2);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    // Poll for input handling
    glfwPollEvents();

    // Put it on the screen
    glfwSwapBuffers(window);
  }

  glfwTerminate();
  return 0;
}

