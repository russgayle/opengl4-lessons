#include "shader.h"

#include <fstream>

queso::Shader::Shader(const std::string& filename, ShaderType type, bool compileShader) 
  : m_type(type)
{
  load(filename);
  m_compiled = false;

  if (type == VERTEX) {
    m_handle = glCreateShader(GL_VERTEX_SHADER);
  } else if (type == FRAGMENT) {
    m_handle = glCreateShader(GL_FRAGMENT_SHADER);
  } else {
    LOG(ERROR) << "Unsupported shader type";
    m_source = "";
    return;
  }

  if (compileShader) {
    compile();
  }
}

bool queso::Shader::load(const std::string& filename)
{
  std::ifstream file;
  m_source = "";
  file.open(filename.c_str());
  if (!file.is_open()) {
    LOG(ERROR) << "Could not load shader: " << filename;
    return false;
  } else {
    std::string line;
    while(getline(file, line)) {
      m_source += line + "\n";
    }
    file.close();
  }

  const char* source = m_source.c_str();
  glShaderSource(m_handle, 1, &source, NULL);
  return true;
}

bool queso::Shader::compile()
{
  glCompileShader(m_handle);
  m_compiled = true;
  return true;
}

