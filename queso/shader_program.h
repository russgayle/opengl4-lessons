#ifndef _QUESO_SHADER_PROGRAM_H_
#define _QUESO_SHADER_PROGRAM_H_

#include "common.h"

namespace queso {

  // Forward declaration
  class Shader;

  enum MatrixType { TWO_BY_TWO, THREE_BY_THREE, FOUR_BY_FOUR };

  class ShaderProgram {
    public:
      ShaderProgram(const Shader& vertex, const Shader& fragment);

      void use();

      unsigned int getHandle() const { return m_handle; }

      // Uniforms 

      // Ints
      bool setUniform(const std::string& name, GLint v);
      bool setUniform(const std::string& name, GLint v1, GLint v2);
      bool setUniform(const std::string& name, GLint v1, GLint v2, GLint v3);
      bool setUniform(const std::string& name, GLint v1, GLint v2, GLint v3, GLint v4);

      // Floats
      bool setUniform(const std::string& name, GLfloat v);
      bool setUniform(const std::string& name, GLfloat v1, GLfloat v2);
      bool setUniform(const std::string& name, GLfloat v1, GLfloat v2, GLfloat v3);
      bool setUniform(const std::string& name, GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4);

      // Matrices
      // TODO(rgayle): Support array of matrices?
      bool setUniform(const std::string& name, MatrixType matType, GLboolean transpose, const GLfloat* value);

      // Debugging
      void printAllInfo();
      bool validate();

    private:
      // Don't allow these c'tors.
      ShaderProgram() {}
      ShaderProgram(const ShaderProgram& program) {}

      const Shader* m_vertex;
      const Shader* m_fragment;
      unsigned int m_handle;

      std::string getProgramLogInfo();
      GLint getLocation(const std::string& name, bool useProgram = true);
  };

} // namespace queso

#endif // _QUESO_SHADER_PROGRAM_H_
