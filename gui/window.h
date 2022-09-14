
#ifndef JINTERCEPT_WINDOW_H
#define JINTERCEPT_WINDOW_H

#include <string>
#include <GLFW/glfw3.h>

class window {
public:
    window(const std::string& title, int width, int height);
    bool render();

    virtual void glfw_callback() = 0;

    GLFWwindow* m_glfw_window;
    int m_width{}, m_height{};
};

#endif //JINTERCEPT_WINDOW_H
