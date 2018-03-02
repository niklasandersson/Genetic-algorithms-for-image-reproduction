#ifndef SHADERS_H
#define SHADERS_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "GL/glew.h"

GLuint LoadShaders(const char* vs_path, const char* fs_path);
GLuint LoadComputeShader(const char* path);

#endif /* SHADERS_H */
