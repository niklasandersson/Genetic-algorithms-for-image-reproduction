#include "window.h"

Window::Window(int height, int width) {
  if (!glfwInit()) {
    std::cout << "Could not init glfw" << std::endl;
  }

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window_ = glfwCreateWindow(height, width, " ", NULL, NULL);
  if (window_ == NULL) {
    std::cout << "Could not create window" << std::endl;
    glfwTerminate();
  }

	glfwMakeContextCurrent(window_);
  glewExperimental = true;
  if (glewInit() != GLEW_OK) {
    std::cout << "Could not init glew" << std::endl;
    glfwTerminate();
  }

  glfwSetInputMode(window_, GLFW_STICKY_KEYS, GL_TRUE);
}

Window::~Window() {
  glfwDestroyWindow(window_);
  glfwTerminate();
}
