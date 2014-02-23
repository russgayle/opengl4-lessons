#include "shader_program.h"

#include "shader.h"

queso::ShaderProgram::ShaderProgram(const Shader& vertex, const Shader& fragment) {
  // TODO(rgayle): Verify that vertex is really a vertex, fragment is really a fragment

  m_handle = glCreateProgram();
  glAttachShader(m_handle, vertex.getHandle());
  glAttachShader(m_handle, fragment.getHandle());
  glLinkProgram(m_handle);

  // TODO(rgayle): Debug mode? 
  int params = -1;
  glGetProgramiv(m_handle, GL_LINK_STATUS, &params);
  if (params != GL_TRUE) {
    LOG(ERROR) << "Could not link shader program " << m_handle;
    LOG(ERROR) << getProgramLogInfo();
  }
}

void queso::ShaderProgram::use() {
  glUseProgram(m_handle);
}

std::string queso::ShaderProgram::getProgramLogInfo() {
  int max_len = 2048;
  int actual_len = 0;
  char log[2048];
  glGetProgramInfoLog(m_handle, max_len, &actual_len, log);

  std::ostringstream oss;
  oss << "[Program " << m_handle << "]: " << log;
  return oss.str();
}

void queso::ShaderProgram::printAllInfo() {
  LOG(INFO) << "Program " << m_handle;

  int params = -1;

  // Link status
  glGetProgramiv(m_handle, GL_LINK_STATUS, &params);
  char value[32];
  LOG(INFO) << "\tGL_LINK_STATUS: " << (params == GL_TRUE ? "GL_TRUE" : "GL_FALSE");

  //TODO(rgayle): Fill this out.
  // Attached shaders
  // Active attributes
  // Active uniforms
}

bool queso::ShaderProgram::validate() {
  glValidateProgram(m_handle);
  int params = -1;

  // Refactor?
  glGetProgramiv(m_handle, GL_VALIDATE_STATUS, &params);
  if (params != GL_TRUE) {
    LOG(ERROR) << "[Program " << m_handle << "]: Invalid program.";
    LOG(ERROR) << getProgramLogInfo();
    return false;
  } else {
    LOG(INFO) << "[Program " << m_handle << "]: Validated!";
    return true;
  }
}
