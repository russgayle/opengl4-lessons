// Lesson 2: http://antongerdelan.net/opengl/glcontext2.html

#include <fstream>

// Setup GLM
#define GLM_FORCE_RADIANS

// Queso!
#include "queso.h"

// GLM extras
#include <glm/gtc/matrix_transform.hpp>   // glm::translate, glm::rotate, glm::scale
#include <glm/gtc/type_ptr.hpp>           // glm::value_ptr

int main(int argc, char* argv[]) {

  queso::App lesson6(argc, argv, "Lesson 6: Virtual Camera");

  // Set up a triangle.
  queso::Drawable triangle;

  float points[] = {
     0.0f,   0.5f, 0.0f,
     0.5f,  -0.5f, 0.0f,
    -0.5f,  -0.5f, 0.0f
  };
  triangle.addVertices(9, points);

  float colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
  };
  triangle.addColors(9, colors);

  // Shaders and shader program
  queso::Shader vs("shaders/perspective.vert", queso::VERTEX, true);
  queso::Shader fs("shaders/uniform_color.frag", queso::FRAGMENT, true);
  queso::ShaderProgram prog(vs, fs);

  // Projection
  glm::mat4 projection = glm::perspective(3.141592f / 3.0f, 640.0f / 480.0f, 0.1f, 100.0f);

  // View
  glm::mat4 translate = glm::translate(
    glm::mat4(1.0f), glm::vec3(-queso::camPos[0], -queso::camPos[1], -queso::camPos[2]));
  glm::mat4 view = glm::rotate(translate, queso::camYaw, glm::vec3(0.0f, 1.0f, 0.0f));

  // Set uniforms
  prog.setUniform("view", queso::FOUR_BY_FOUR, GL_FALSE, glm::value_ptr(view));
  prog.setUniform("proj", queso::FOUR_BY_FOUR, GL_FALSE, glm::value_ptr(projection));
   
  lesson6.addDrawable(&triangle);
  lesson6.addShaderProgram(&prog);
  lesson6.run();
  return 0;
}

