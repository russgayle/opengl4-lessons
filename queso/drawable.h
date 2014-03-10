#ifndef _QUESO_DRAWABLE_H_
#define _QUESO_DRAWABLE_H_

#include "common.h"

namespace queso {

  class VBO {
     public: 
      VBO() : m_handle(-1), m_nItems(0) {}
  
      void bind() {
        glBindBuffer(GL_ARRAY_BUFFER, m_handle);
      }
  
      void set(size_t numItems, float* items) {
        m_nItems = numItems;

        glGenBuffers(1, &m_handle);
        bind();
        glBufferData(GL_ARRAY_BUFFER, numItems * sizeof(float), items, GL_STATIC_DRAW);
      }

      GLuint getHandle() { return m_handle; }

    private:
      GLuint m_handle;
      size_t m_nItems;
  };
  
  class Drawable {

    public:
      Drawable();

      void draw(GLenum mode = GL_TRIANGLES);
      void bind();

      void addVertices(size_t nItems, float* items);
      void addColors(size_t nItems, float* items);
  
    private:
      VBO m_vertices;
      VBO m_colors;

      GLuint m_handle;
      size_t m_numPrims;
  };
  
}

#endif // _QUESO_DRAWABLE_H_
