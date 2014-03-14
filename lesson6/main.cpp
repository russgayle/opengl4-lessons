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
   
  lesson6.addDrawable(&triangle);
  lesson6.addShaderProgram(&prog);
  lesson6.run();
  return 0;
}

