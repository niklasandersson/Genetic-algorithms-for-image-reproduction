#include "window.h"
#include "utils.h"
#include "shaders.h"
#include "image.h"
#include "population.h"

Population* population;

int window_height = 0;
int window_width = 0;
int image_height = 0;
int image_width = 0;

void CreateQuad();
void CreateTriangle();
void DrawQuad();
void CleanUp();
void CreateOrigTexture(unsigned char* data);
void DrawOriginalImage();
void DrawCreature(int i);

GLuint quad_vertex_array;
GLuint triangle_vertex_array;
GLuint quad_buffer;
GLuint triangle_buffer;
GLuint quad_shader;
GLuint triangle_shader;
GLuint orig_texture;
GLuint orig_texture_location;

GLuint transform_location;
GLuint color_location;
GLuint opacity_location;

int main(int argc, char* argv[])
{
  std::string image_path;
  if (argc == 2) {
    image_path = argv[1];
  } else {

    image_path = "img3.jpg";
  }

  Image image(image_path); window_height = image.GetHeight(); window_width = image.GetWidth() * 2;
  image_width = image.GetWidth();
  image_height = image.GetHeight();
  std::cout << "Original image: " << image_path << std::endl;
  std::cout << "Image size" << std::endl;
  std::cout << "  height: " << image.GetHeight() << std::endl;
  std::cout << "  width: " << image.GetWidth() << std::endl;
  gene::Window window(window_width, window_height);

  population = new Population(1,10);

  glDisable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(0.f, 0.4f, 0.4f, 0.0f);

  CreateOrigTexture(image.GetData());
  orig_texture_location = glGetUniformLocation(quad_shader, "myTextureSampler");
  CreateQuad();
  CreateTriangle();


  do {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    DrawCreature(0);
    DrawOriginalImage();

    window.SwapBuffer();
    window.PollEvents();
  } while(glfwGetKey(window.GetWindow(), GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
                 glfwWindowShouldClose(window.GetWindow()) == 0);

  CleanUp();
  return 0;
}

void CreateQuad() {
  quad_vertex_array = CreateVertexArray();
  quad_buffer = CreateQuadBuffer();
  quad_shader = LoadShaders("shaders/texture.vs", "shaders/texture.fs");
}

void CreateTriangle() {
  triangle_vertex_array = CreateVertexArray();
  triangle_buffer = CreateTriangleBuffer();
  triangle_shader = LoadShaders("shaders/passthrough.vs", "shaders/red.fs");
  transform_location = glGetUniformLocation(triangle_shader, "transform");
  color_location = glGetUniformLocation(triangle_shader, "color");
  opacity_location = glGetUniformLocation(triangle_shader, "opacity");
}

void DrawQuad() {
  glViewport(0,0,image_width,window_height);
  glUseProgram(quad_shader);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, quad_buffer);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glDisableVertexAttribArray(0);
}

void CleanUp() {
  delete population;
  glDeleteBuffers(1, &quad_buffer);
  glDeleteVertexArrays(1, &quad_vertex_array);
  glDeleteVertexArrays(1, &triangle_vertex_array);
  glDeleteProgram(quad_shader);
}

void CreateOrigTexture(unsigned char* data) {

  GLuint texture_id;
  glGenTextures(1, &texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);
  glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, image_width, image_height,
               0, GL_RGB, GL_UNSIGNED_BYTE, data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  orig_texture = texture_id;
}

void DrawOriginalImage() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, orig_texture);
    glUniform1i(orig_texture_location, 0);
    DrawQuad();
}

void DrawCreature(int i) {
  Gene* gene = population->GetGenes() + i;
  int number_of_genes_per_creature = population->GetNumberOfGenesPerCreature();

  glViewport(image_width,0,image_width,window_height);
  glUseProgram(triangle_shader);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, triangle_buffer);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

  for (int j = 0; j < number_of_genes_per_creature; ++j) {
    glm::mat4 trans = gene->transform;
    glUniformMatrix4fv(transform_location, 1, GL_FALSE, &trans[0][0]);
    glUniform3f(color_location, gene->color.x, gene->color.y, gene->color.z);
    glUniform1f(opacity_location, gene->opacity);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    gene++;
  }

  glDisableVertexAttribArray(0);
}
