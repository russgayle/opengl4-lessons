#include "drawable.h"

queso::Drawable::Drawable() : m_handle(0) {
  glGenVertexArrays(1, &m_handle);
  VLOG(2) << "Drawable::m_handle = " << m_handle;
}

void queso::Drawable::draw(GLenum mode) {
  glBindVertexArray(m_handle);
  glDrawArrays(mode, 0, m_numPrims); 
}

void queso::Drawable::bind() {
  glBindVertexArray(m_handle);
}

void queso::Drawable::addVertices(size_t nItems, float* items) {
  bind();
  m_vertices.set(nItems, items);
  m_numPrims  = nItems / 3;
 
  m_vertices.bind();
  glVertexAttribPointer(0, m_numPrims, GL_FLOAT, GL_FALSE, 0, NULL);
  glEnableVertexAttribArray(0);
}

void queso::Drawable::addColors(size_t nItems, float* items) {
  bind();
  m_colors.set(nItems, items);
  m_numPrims  = nItems / 3;
 
  m_colors.bind();
  glVertexAttribPointer(1, m_numPrims, GL_FLOAT, GL_FALSE, 0, NULL);
  glEnableVertexAttribArray(1);
}

void queso::Drawable::addNormals(size_t nItems, float* items) {
  bind();
  m_normals.set(nItems, items);
  m_numPrims = nItems / 3;

  m_normals.bind();
  glVertexAttribPointer(2, m_numPrims, GL_FLOAT, GL_FALSE, 0, NULL);
  glEnableVertexAttribArray(2);
}

