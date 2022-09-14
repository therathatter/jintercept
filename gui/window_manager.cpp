
#include "window_manager.h"

#include <GLFW/glfw3.h>
#include <stdexcept>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

window_manager::window_manager() {
    if (m_initialized) {
        return;
    }

    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW.");
    }

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    // Prevent Dear ImGui from creating 'imgui.ini'
    ImGui::GetIO().IniFilename = nullptr;

    m_initialized = true;
}

window_manager::~window_manager() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    for (const auto& window : m_windows) {
        glfwDestroyWindow(window->m_glfw_window);
    }

    glfwTerminate();
}

