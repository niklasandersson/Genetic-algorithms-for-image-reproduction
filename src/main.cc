#include "window.h"
#include "utils.h"
#include "shaders.h"

void CreateQuad();
void DrawQuad();
void CleanUp();

GLuint vertex_array;
GLuint quad_buffer;
GLuint quad_shader;
int main()
{
  Window window(512, 512);

  glDisable(GL_CULL_FACE);
  glClearColor(0.0f, 1.0f, 0.4f, 0.0f);

  CreateQuad();

  do {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    DrawQuad();

    window.SwapBuffer();
    window.PollEvents();
  } while(glfwGetKey(window.GetWindow(), GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
                 glfwWindowShouldClose(window.GetWindow()) == 0);

  CleanUp();
  return 0;
}

void CreateQuad() {
  vertex_array = CreateVertexArray();
  quad_buffer = CreateQuadBuffer();
  quad_shader = LoadShaders("shaders/passthrough.vs", "shaders/red.fs");
}

void DrawQuad() {
  glUseProgram(quad_shader);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, quad_buffer);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glDisableVertexAttribArray(0);
}

void CleanUp() {
  glDeleteBuffers(1, &quad_buffer);
  glDeleteVertexArrays(1, &vertex_array);
  glDeleteProgram(quad_shader);
}
