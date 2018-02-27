#ifndef WINDOW_H
#define WINDOW_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"

class Window {

  public:
    Window(int height, int width);
    ~Window();

    void SwapBuffer();
    void PollEvents();

    GLFWwindow* GetWindow();

  private:
    GLFWwindow* window_;
};

inline void Window::SwapBuffer() {
  glfwSwapBuffers(window_);
}

inline void Window::PollEvents() {
  glfwPollEvents();
}

inline GLFWwindow* Window::GetWindow() {
  return window_;
}

#endif /* WINDOW_H */
