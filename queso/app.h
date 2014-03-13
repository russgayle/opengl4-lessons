#ifndef _QUESO_APP_H_
#define _QUESO_APP_H_

#include "common.h"
#include "shader_program.h"
#include "drawable.h"

namespace queso {

  class App {
    public:
      App(int argc, char* argv[], const std::string& appName, bool appendFPS = true); 

      void addProgram(ShaderProgram* program) { m_programs.push_back(program); }
      void addDrawable(Drawable* drawable) { m_drawables.push_back(drawable); }
      void run();

    private:
      // No default c'tors
      App() {}
      App(const App& app) {} 

      GLFWwindow* m_window;
      
      // App state
      std::string m_appName;
      bool m_appendFPSToTitle;
      int m_width;
      int m_height;
      
      std::vector<ShaderProgram*> m_programs;
      std::vector<Drawable*> m_drawables;

      void init(int argc, char* argv[]);
  };

  // Deprecated:

  // Hooks up all the gadgetry for my apps. For GLFW3 (for now?).
  GLFWwindow* init(int argc, char* argv[], const std::string& appName);

  // The error callback to be used.
  void error_callback(int error, const char* description);
}

#endif
