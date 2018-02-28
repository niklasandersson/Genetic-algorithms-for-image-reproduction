#include "shader.h"

Shader::Shader() :
  is_linked_(false),
  has_vertex_shader_(false),
  har_fragment_shader(false),
  has_compute_shader(false) {

  ids[0] = glCreateProgram();
}

Shader::~Shader() {

}

void Shader::CompileSourceFile(const std::string& file_path, TYPE type) {
  switch (type) {
    case VERTEX: ids[1] = glCreateShader(GL_VERTEX_SHADER); break;
    case FRAGMENT: ids[2] = glCreateShader(GL_FRAGMENT_SHADER); break;
    case COMPUTE: ids[3] = glCreateShader(GL_COMPUTE_SHADER); break;
  }

  std::string source;
  std::ifstream source_stream(file_path);

  if (source_stream.is_open()) {
    std::stringstream sstream;
    sstream << source_stream.rdbuf();
    source  = sstream.str();
    source_stream.close();
  } else {
    std::cout << "Could not load vertex shader" << std::endl;
    return;
  }

  const char* char_source = source.c_str();
  switch (type) {
    case VERTEX: glShaderSource(ids[1], 1, &char_source, NULL);
                 glCompileShader(ids[1]);
                 break;
    case FRAGMENT: glShaderSource(ids[2], 1, &char_source, NULL);
                   glCompileShader(ids[2]);
                   break;
    case COMPUTE: glShaderSource(ids[3], 1, &char_source, NULL);
                  glCompileShader(ids[3]);
                  break;
  }


  // Kolla så det funkade
  /* GLint result = GL_FALSE; */

  /* int log_length = 0; */

  /* if (log_length > 0) { */
  /*   std::vector<char> error_message(log_length + 1); */
  /*   glGetShaderInfoLog(id, log_length, NULL, &error_message[0]); */
  /*   std::cout << "Vertex Shader log:" << std::endl; */
  /*   std::cout << std::string(&error_message[0]) << std::endl; */
  /* } */

  switch (type) {
    case VERTEX:
                 has_vertex_shader_ = true;
                 break;
    case FRAGMENT:
                   har_fragment_shader = true;
                   break;
    case COMPUTE:
                  has_compute_shader = true;
                  break;
  }
}

void Shader::Link() {
  if (!is_linked_) {
    glLinkProgram(ids[0]);

    if (has_vertex_shader_) {
      glDetachShader(ids[0], ids[1]);
      glDeleteShader(ids[1]);
    }
    if (har_fragment_shader) {
      glDetachShader(ids[0], ids[2]);
      glDeleteShader(ids[2]);
    }
    if (has_compute_shader) {
      glDetachShader(ids[0], ids[3]);
      glDeleteShader(ids[3]);
    }

    is_linked_ = true;
  }
}
