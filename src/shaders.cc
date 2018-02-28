#include "shaders.h"

GLuint LoadShaders(const char* vs_path, const char* fs_path) {
  GLuint vs_id = glCreateShader(GL_VERTEX_SHADER);
  GLuint fs_id = glCreateShader(GL_FRAGMENT_SHADER);

  std::string vs_code;
  std::ifstream vs_stream(vs_path);

  if (vs_stream.is_open()) {
    std::stringstream sstream;
    sstream << vs_stream.rdbuf();
    vs_code = sstream.str();
    vs_stream.close();
  } else {
    std::cout << "Could not load vertex shader" << std::endl;

    return 0;
  }

  std::string fs_code;
  std::ifstream fs_stream(fs_path);

  if (fs_stream.is_open()) {
    std::stringstream sstream;
    sstream << fs_stream.rdbuf();
    fs_code = sstream.str();
    fs_stream.close();
  } else {
    std::cout << "Could not load fragment shader" << std::endl;

    return 0;
  }

  GLint result = GL_FALSE;

  int log_length = 0;

  const char* vs_source = vs_code.c_str();
  glShaderSource(vs_id, 1, &vs_source, NULL);
  glCompileShader(vs_id);

  glGetShaderiv(vs_id, GL_COMPILE_STATUS, &result);
  glGetShaderiv(vs_id, GL_INFO_LOG_LENGTH, &log_length);

  if (log_length > 0) {
    std::vector<char> error_message(log_length + 1);
    glGetShaderInfoLog(vs_id, log_length, NULL, &error_message[0]);
    std::cout << "Vertex Shader log:" << std::endl;
    std::cout << std::string(&error_message[0]) << std::endl;
  }

  const char* fs_source = fs_code.c_str();
  glShaderSource(fs_id, 1, &fs_source, NULL);
  glCompileShader(fs_id);

  glGetShaderiv(fs_id, GL_COMPILE_STATUS, &result);
  glGetShaderiv(fs_id, GL_INFO_LOG_LENGTH, &log_length);

  if (log_length > 0) {
    std::vector<char> error_message(log_length + 1);
    glGetShaderInfoLog(fs_id, log_length, NULL, &error_message[0]);
    std::cout << "Fragment Shader log:" << std::endl;
    std::cout << std::string(&error_message[0]) << std::endl;
  }

  GLuint program_id = glCreateProgram();

  glAttachShader(program_id, vs_id);
  glAttachShader(program_id, fs_id);
  glLinkProgram(program_id);

  glGetShaderiv(program_id, GL_COMPILE_STATUS, &result);
  glGetShaderiv(program_id, GL_INFO_LOG_LENGTH, &log_length);

  if (log_length > 0) {
    std::vector<char> error_message(log_length + 1);
    glGetShaderInfoLog(program_id, log_length, NULL, &error_message[0]);
    std::cout << "Program log:" << std::endl;
    std::cout << std::string(&error_message[0]) << std::endl;
  }

  glDetachShader(program_id, vs_id);
  glDetachShader(program_id, fs_id);

  glDeleteShader(vs_id);
  glDeleteShader(fs_id);

  return program_id;
}
