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

    unsigned int getHandle() const { return m_handle; }
    ShaderType getType() const { return m_type; }
    std::string getSource() const { return m_source; }
    std::string getFilename() const { return m_filename; }

  private:

    // No default c'tors.
    Shader() {}
    Shader(const Shader& shader) {}

    std::string m_filename;
    std::string m_source;
    unsigned int m_handle;
    ShaderType m_type;
    bool m_compiled;

    std::string getShaderInfoLog();
};

} // namespace queso

#endif // _QUESO_SHADER_H_
