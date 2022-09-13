
#include "gui.h"
#include "../class/package_manager.h"
#include <stdexcept>
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

GLFWwindow* window = nullptr;

void gui::init() {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW.");
    }


    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    // Prevent Dear ImGui from creating 'imgui.ini'
    ImGui::GetIO().IniFilename = nullptr;


    ImGui_ImplOpenGL3_Init("#version 130");
}

void render_package(const package& package) {
    for (const auto& [name, subpackage] : package.subpackages) {
        if (ImGui::TreeNode(name.c_str())) {
            render_package(subpackage);

            for (const auto& [name, klass] : package.classes) {
                if (ImGui::Selectable("%s", name.c_str())) {
                    //active_klass = klass;
                }
            }

            ImGui::TreePop();
        }
    }
}

bool gui::render() {
    const std::lock_guard<std::mutex> lock(package_manager::get_mutex());

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
                ImGui::Text("Dump Java classes at runtime");

                if (ImGui::Button("Close")) {
                    ImGui::CloseCurrentPopup();
                }

                ImGui::EndPopup();
            }
        }
        ImGui::EndMenuBar();

        if (ImGui::BeginChild("##loaded_classes")) {
            ImGui::Text("Loaded classes");
            // Recursively render each package, starting at the root package
            render_package(package_manager::get_root());

            /*if (ImGui::ListBoxHeader("##loaded_classes")) {

                ImGui::ListBoxFooter();
            }*/

        }
        ImGui::EndChild();

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