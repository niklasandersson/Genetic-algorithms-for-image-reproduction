#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "GL/glew.h"

class Shader {

  public:
    enum TYPE {
      VERTEX,
      FRAGMENT,
      COMPUTE
    };

    Shader();

    void CompileSourceFile(const std::string& file_path, TYPE type);
    void Link();

    GLuint GetProgram() const;

    ~Shader();

  private:
    bool is_linked_;
    bool has_vertex_shader_;
    bool har_fragment_shader;
    bool has_compute_shader;

    GLuint ids[4];
};

inline GLuint Shader::GetProgram() const {
  return ids[0];
}

#endif /* SHADER_H */
