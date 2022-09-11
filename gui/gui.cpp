
#include "gui.h"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include <stdexcept>

GLFWwindow* window = nullptr;

void gui::init() {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW.");
    }

    window = glfwCreateWindow(1280, 720, "jintercept", NULL, NULL);

    if (!window) {
        throw std::runtime_error("GLFW failed to create a window.");
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    // Prevent Dear ImGui from creating 'imgui.ini'
    ImGui::GetIO().IniFilename = nullptr;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

bool gui::render() {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(display_w, display_h));
    if (ImGui::Begin("##jintercept", nullptr,   ImGuiWindowFlags_NoTitleBar
                                                                | ImGuiWindowFlags_MenuBar
                                                                | ImGuiWindowFlags_NoResize)) {
        if (ImGui::BeginMenuBar()) {
            if (ImGui::MenuItem("About")) {
                ImGui::OpenPopup("About");
            }

            if (ImGui::BeginPopupModal("About")) {
                ImGui::Text("jintercept - https://github.com/therathatter/jintercept");
                ImGui::Text("Dump and patch Java classes at runtime");

                if (ImGui::Button("Close")) {
                    ImGui::CloseCurrentPopup();
                }

                ImGui::EndPopup();
            }

            ImGui::EndMenuBar();
        }

        if (ImGui::BeginChild("##loaded_classes")) {
            ImGui::ListBoxHeader("Loaded classes");
        }

        ImGui::End();
    }

    ImGui::Render();

    glViewport(0, 0, display_w, display_h);
    const ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0, 1.0f);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);

    return !glfwWindowShouldClose(window);
}

void gui::shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}