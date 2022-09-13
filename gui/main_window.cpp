//
// Created by root on 9/13/2022.
//

#include "main_window.h"
#include "../class/package_manager.h"

#include <imgui.h>

void render_package(const package& package) {
    for (const auto& [name, subpackage] : package.subpackages) {
        if (ImGui::TreeNode(name.c_str())) {
            render_package(subpackage);

            for (const auto& [subpackage_name, klass] : package.classes) {
                if (ImGui::Selectable(subpackage_name.c_str())) {

                }
            }

            ImGui::TreePop();
        }
    }
}

void main_window::glfw_callback() {
    ImGui::SetNextWindowPos(ImVec2());
    ImGui::SetNextWindowSize(ImVec2(m_width, m_height));

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
        }
        ImGui::EndChild();

        ImGui::End();
    }
}