// Queso!
#include "queso.h"

// GLM extras
#include <glm/gtc/matrix_transform.hpp>   // glm::translate, glm::rotate, glm::scale
#include <glm/gtc/type_ptr.hpp>           // glm::value_ptr

int main(int argc, char* argv[]) {

  queso::App phongToy(argc, argv, "Per-pixel (phong) lighting.");

  // Set up a triangle.
  queso::Drawable triangle;

  float points[] = {
     0.0f,   0.5f, 0.0f,
     0.5f,  -0.5f, 0.0f,
    -0.5f,  -0.5f, 0.0f
  };
  triangle.addVertices(9, points);

  float colors[] = {
    0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, 0.5f
  };
  triangle.addColors(9, colors);

  // Shaders and shader program
  queso::Shader vs("shaders/perspective.vert", queso::VERTEX, true);
  queso::Shader fs("shaders/uniform_color.frag", queso::FRAGMENT, true);
  queso::ShaderProgram prog(vs, fs);
   
  phongToy.addDrawable(&triangle);
  phongToy.addShaderProgram(&prog);
  phongToy.run();
  return 0;
}

