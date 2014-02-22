#include "shader.h"

#include <sstream>
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
  return true;
}

bool queso::Shader::compile()
{
  if (!m_compiled) {
    const char* source = m_source.c_str();
    glShaderSource(m_handle, 1, &source, NULL);
    glCompileShader(m_handle);

    // Check for errors. TODO(rgayle): Make this part of a debug mode?
    int params = -1;
    glGetShaderiv(m_handle, GL_COMPILE_STATUS, &params);
    m_compiled = (params == GL_TRUE);

    if (!m_compiled) {
      LOG(ERROR) << "Shader " << m_handle << " did not compile. Details: "; 
      LOG(ERROR) << getShaderInfoLog();
    } 
  }

  return m_compiled;
}

std::string queso::Shader::getShaderInfoLog() {
  int max_len = 2048;
  int actual_len = 0;
  char log[2048];
  glGetShaderInfoLog(m_handle, max_len, &actual_len, log);
  
  std::ostringstream oss;
  oss << "[Shader " << m_handle << "]: " << log;
  return oss.str();

}

