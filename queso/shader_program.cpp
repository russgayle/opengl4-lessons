#include "shader_program.h"

#include "shader.h"
#include "utils.h"

queso::ShaderProgram::ShaderProgram(const Shader& vertex, const Shader& fragment) {
  // TODO(rgayle): Verify that vertex is really a vertex, fragment is really a fragment
  m_vertex = &vertex;
  m_fragment = &fragment;

  m_handle = glCreateProgram();
  if (m_vertex)   glAttachShader(m_handle, m_vertex->getHandle());
  if (m_fragment) glAttachShader(m_handle, m_fragment->getHandle());
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

bool queso::ShaderProgram::setUniform(const std::string& name, GLint v) {
  GLint loc = getLocation(name);
  if (loc != -1) glUniform1i(loc, v);
  return loc != -1;
}

bool queso::ShaderProgram::setUniform(const std::string& name, GLint v1, GLint v2) {
  GLint loc = getLocation(name);
  if (loc != -1) glUniform2i(loc, v1, v2);
  return loc != -1;
}

bool queso::ShaderProgram::setUniform(const std::string& name, GLint v1, GLint v2, GLint v3) {
  GLint loc = getLocation(name);
  if (loc != -1) glUniform3i(loc, v1, v2, v3);
  return loc != -1;
}

bool queso::ShaderProgram::setUniform(const std::string& name, GLint v1, GLint v2, GLint v3, GLint v4) {
  GLint loc = getLocation(name);
  if (loc != -1) glUniform4i(loc, v1, v2, v3, v4);
  return loc != -1;
}

bool queso::ShaderProgram::setUniform(const std::string& name, GLfloat v) {
  GLint loc = getLocation(name);
  if (loc != -1) glUniform1f(loc, v);
  return loc != -1;
}

bool queso::ShaderProgram::setUniform(const std::string& name, GLfloat v1, GLfloat v2) {
  GLint loc = getLocation(name);
  if (loc != -1) glUniform2f(loc, v1, v2);
  return loc != -1;
}

bool queso::ShaderProgram::setUniform(const std::string& name, GLfloat v1, GLfloat v2, GLfloat v3) {
  GLint loc = getLocation(name);
  if (loc != -1) glUniform3f(loc, v1, v2, v3);
  return loc != -1;
}

bool queso::ShaderProgram::setUniform(const std::string& name, GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4) {
  GLint loc = getLocation(name);
  if (loc != -1) glUniform4f(loc, v1, v2, v3, v4);
  return loc != -1;
}

bool queso::ShaderProgram::setUniform(const std::string& name, MatrixType matType, GLboolean transpose, const GLfloat* value) {
  GLint loc = getLocation(name);
  if (loc != -1) {
    switch(matType) {
      case TWO_BY_TWO:
        glUniformMatrix2fv(loc, 1, transpose, value);
        return true;
      case THREE_BY_THREE: 
        glUniformMatrix3fv(loc, 1, transpose, value);
        return true;
      case FOUR_BY_FOUR:
        glUniformMatrix4fv(loc, 1, transpose, value);
        return true;
      default: 
        LOG(WARNING) << "Unknown matrix type.";
        break;
    }
  }
  return false;
}

std::string queso::ShaderProgram::getProgramLogInfo() {
  int max_len = 2048;
  int actual_len = 0;
  char log[2048];
  glGetProgramInfoLog(m_handle, max_len, &actual_len, log);

  std::ostringstream oss;
  oss << "[Program " << m_handle << " log]: " << log;
  return oss.str();
}

void queso::ShaderProgram::printAllInfo() {
  LOG(INFO) << "[Program " << m_handle << "]: All information:";

  int params = -1;

  // Link status
  glGetProgramiv(m_handle, GL_LINK_STATUS, &params);
  char value[32];
  LOG(INFO) << "\tGL_LINK_STATUS: " << (params == GL_TRUE ? "GL_TRUE" : "GL_FALSE");

  // Attached shaders
  glGetProgramiv(m_handle, GL_ATTACHED_SHADERS, &params);
  LOG(INFO) << "\tGL_ATTACHED_SHADERS: " << params;
  if (m_vertex)
    LOG(INFO) << "\t\t[Vertex " << m_vertex->getHandle() << "]: " << m_vertex->getFilename();
  if (m_fragment)
    LOG(INFO) << "\t\t[Fragment " << m_fragment->getHandle() << "]: " << m_fragment->getFilename();

  // Active attributes
  glGetProgramiv(m_handle, GL_ACTIVE_ATTRIBUTES, &params);
  LOG(INFO) << "\tGL_ACTIVE_ATTRIBUTES: " << params;
  for (unsigned int i = 0; i < params; i++) {
    char name[64];
    int max_len = 64, actual_len = 0, size = 0;
    GLenum type;
    glGetActiveAttrib(m_handle, i, max_len, &actual_len, &size, &type, name);
    if (size > 1) {
      for (int j = 0; j < size; j++) {
        std::stringstream oss;
        oss << name << "[" << j << "]";
        int location = glGetAttribLocation(m_handle, oss.str().c_str());
        LOG(INFO) << "\t\tAttribute #" << i
          << ": type=" << glTypeToString(type)
          << ", name=" << oss.str()
          << ", location=" << location;
      }
    } else {
      int location = glGetAttribLocation(m_handle, name);
      LOG(INFO) << "\t\tAttribute #" << i
        << ": type=" << glTypeToString(type)
        << ", name=" << name
        << ", location=" << location;
    }
  }

  // Active uniforms
  glGetProgramiv(m_handle, GL_ACTIVE_UNIFORMS, &params);
  LOG(INFO) << "\tGL_ACTIVE_UNIFORMS: " << params;
  for (unsigned int i = 0; i < params; i++) {
    char name[64];
    int max_len = 64, actual_len = 0, size = 0;
    GLenum type;
    glGetActiveUniform(m_handle, i, max_len, &actual_len, &size, &type, name);
    if (size > 1) {
      for (int j = 0; j < size; j++) {
        std::stringstream oss;
        oss << name << "[" << j << "]";
        int location = glGetUniformLocation(m_handle, oss.str().c_str());
        LOG(INFO) << "\t\tAttribute #" << i
          << ": type=" << glTypeToString(type)
          << ", name=" << oss.str()
          << ", location=" << location;
      }
    } else {
      int location = glGetUniformLocation(m_handle, name);
      LOG(INFO) << "\t\tAttribute #" << i
        << ": type=" << glTypeToString(type)
        << ", name=" << name
        << ", location=" << location;
    }
  }

  // Log info
  LOG(INFO) << getProgramLogInfo();
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

GLint queso::ShaderProgram::getLocation(const std::string& name, bool useProgram) {
  // For safer operation, make sure program is in use before doing all of this.
  if (useProgram) use();

  // TODO(rgayle): Precompute locations?
  GLint loc = glGetUniformLocation(m_handle, name.c_str());
  if (loc == -1) { 
    LOG(WARNING) << "Could not find uniform \"" << name << "\" in program " << m_handle;
  }

  return loc;
}
