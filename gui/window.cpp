//
// Created by root on 9/13/2022.
//

#include "window.h"

#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <stdexcept>

window::window(const std::string& name, int width, int height) {
    m_glfw_window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    m_width = width, m_height = height;

    if (!m_glfw_window) {
        throw std::runtime_error("GLFW failed to create a window");
    }

    glfwMakeContextCurrent(m_glfw_window);
    glfwSwapInterval(1);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    ImGui_ImplGlfw_InitForOpenGL(m_glfw_window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

bool window::render() {
    glfwPollEvents();
    glfwGetFramebufferSize(m_glfw_window, &m_width, &m_height);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    glfw_callback();

    ImGui::Render();

    glViewport(0, 0, m_width, m_height);
    const ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0, 1.0f);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(m_glfw_window);

    return !glfwWindowShouldClose(m_glfw_window);
}