
#include "main_window.h"
#include "../class/package_manager.h"

#include <imgui.h>
#include <memory>

klass empty_klass{};
std::reference_wrapper<const klass> active_klass = empty_klass;

void render_package(const package& package) {
    for (const auto& [subpackage_name, subpackage] : package.subpackages) {
        if (ImGui::TreeNode(subpackage_name.c_str())) {
            render_package(subpackage);

            for (const auto& [name, klass] : subpackage.classes) {
                if (ImGui::Selectable(name.c_str())) {
                    active_klass = klass;
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

        // Two children, exactly the same size, next to each other.
        ImVec2 available_size = ImGui::GetContentRegionAvail();
        ImVec2 child_size = available_size;
        child_size.x /= 2;
        // Compensate for the window padding
        child_size.x -= ImGui::GetStyle().WindowPadding.x / 2;

        // If the active class has a name, then a class has been selected
        bool class_selected = !active_klass.get().name.empty();

        // If no class has been selected, take up all the available space.
        if (ImGui::BeginChild("##loaded_classes", class_selected ? child_size : available_size, true)) {
            ImGui::Text("Loaded classes");
            // Recursively render each package, starting at the root package
            render_package(package_manager::get_root());
        }
        ImGui::EndChild();

        ImGui::SameLine();

        if (class_selected) {
            if (ImGui::BeginChild("##active_class", child_size, true)) {
                ImGui::Text("Active class");

                const auto& klass = active_klass.get();

                ImGui::Text("Name: %s", klass.name.c_str());
                ImGui::Text("Source: %s", klass.source.c_str());
                ImGui::Text("Byte count: %zu", klass.code.size());
            }
            ImGui::EndChild();
        }

        ImGui::End();
    }
}