#include "shader_program.h"

#include "shader.h"

queso::ShaderProgram::ShaderProgram(const Shader& vertex, const Shader& fragment) {
  // TODO(rgayle): Verify that vertex is really a vertex, fragment is really a fragment

  m_handle = glCreateProgram();
  glAttachShader(m_handle, vertex.getHandle());
  glAttachShader(m_handle, fragment.getHandle());
  glLinkProgram(m_handle);
}

void queso::ShaderProgram::use() {
  glUseProgram(m_handle);
}
