#include "utils.h"

std::string queso::glTypeToString(unsigned int type) {
  if (GL_FLOAT == type) {
    return "GL_FLOAT";
  }
  if (GL_FLOAT_VEC2 == type) {
    return "GL_FLOAT_VEC2";
  }
  if (GL_FLOAT_VEC3 == type) {
    return "GL_FLOAT_VEC3";
  }
  if (GL_FLOAT_VEC4 == type) {
    return "GL_FLOAT_VEC4";
  }
  if (GL_FLOAT_MAT2 == type) {
    return "GL_FLOAT_MAT2";
  }
  if (GL_FLOAT_MAT3 == type) {
    return "GL_FLOAT_MAT3";
  }
  if ( GL_FLOAT_MAT4 == type) {
    return "GL_FLOAT_MAT4";
  }
  if (GL_INT == type) {
    return "GL_INT";
  }
  if (GL_BOOL == type) {
    return "GL_BOOL";
  }
  if (GL_SAMPLER_2D == type) {
    return "GL_SAMPLER_2D";
  }
  if (GL_SAMPLER_3D == type) {
    return "GL_SAMPLER_3D";
  }
  if (GL_SAMPLER_CUBE == type) {
    return "GL_SAMPLER_CUBE";
  }
  if (GL_SAMPLER_2D_SHADOW == type) {
    return "GL_SAMPLER_2D_SHADOW";
  }
  return "OTHER";
}
