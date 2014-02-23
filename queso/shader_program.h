#ifndef _QUESO_SHADER_PROGRAM_H_
#define _QUESO_SHADER_PROGRAM_H_

#include "common.h"

namespace queso {

  // Forward declaration
  class Shader;

  class ShaderProgram {
    public:
      ShaderProgram(const Shader& vertex, const Shader& fragment);

      void use();

      unsigned int getHandle() const { return m_handle; }

    private:
      // Don't allow these c'tors.
      ShaderProgram() {}
      ShaderProgram(const ShaderProgram& program) {}

      unsigned int m_handle;

      std::string getProgramLogInfo();
  };

} // namespace queso

#endif // _QUESO_SHADER_PROGRAM_H_
