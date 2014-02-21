#ifndef _QUESO_SHADER_H_
#define _QUESO_SHADER_H_

#include "common.h"
 
namespace queso {

enum ShaderType { VERTEX, FRAGMENT };

class Shader
{
  public:
    Shader(const std::string& filename, ShaderType type, bool compileShader = false);

    bool load(const std::string& filename);
    bool compile();

    unsigned int getHandle() { return m_handle; }
    ShaderType getType() { return m_type; }

  private:

    // No default c'tors.
    Shader() {}
    Shader(const Shader& shader) {}

    std::string m_source;
    unsigned int m_handle;
    ShaderType m_type;
    bool m_compiled;

    std::string getShaderInfoLog();
};

} // namespace queso

#endif // _QUESO_SHADER_H_
