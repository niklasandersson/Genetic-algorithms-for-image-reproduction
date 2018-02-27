#include "shader.h"

Shader::Shader() :
  is_linked_(false),
  has_vertex_shader_(false),
  har_fragment_shader(false),
  has_compute_shader(false),
  vertex_id_(0),
  fragment_id_(0),
  compute_id_(0) {

  program_id_ = glCreateProgram();
}

void Shader::CompileSourceFile(const std::string& file_path, TYPE type) {
  GLuint id;
  switch (type) {
    case VERTEX: id = glCreateShader(GL_VERTEX_SHADER); break;
    case FRAGMENT: id = glCreateShader(GL_FRAGMENT_SHADER); break;
    case COMPUTE: id = glCreateShader(GL_COMPUTE_SHADER); break;
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
  glShaderSource(id, 1, &char_source, NULL);
  glCompileShader(id);

  // Kolla så det funkade
  switch (type) {
    case VERTEX: vertex_id_ = id;
                 has_vertex_shader_ = true;
                 break;
    case FRAGMENT: fragment_id_  = id;
                   har_fragment_shader = true;
                   break;
    case COMPUTE: compute_id_ = id;
                  has_compute_shader = true;
                  break;
  }
}

void Shader::Link() {
  if (!is_linked_) {
    glLinkProgram(program_id_);

    if (has_vertex_shader_) {
      glDetachShader(program_id_, vertex_id_);
      glDeleteShader(vertex_id_);
    }
    if (har_fragment_shader) {
      glDetachShader(program_id_, fragment_id_);
      glDeleteShader(fragment_id_);
    }
    if (has_compute_shader) {
      glDetachShader(program_id_, compute_id_);
      glDeleteShader(compute_id_);
    }

    is_linked_ = true;
  }
}
