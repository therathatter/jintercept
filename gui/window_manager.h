//
// Created by root on 9/13/2022.
//

#ifndef JINTERCEPT_WINDOW_MANAGER_H
#define JINTERCEPT_WINDOW_MANAGER_H

#include "window.h"
#include <vector>
#include <memory>

class window_manager {
public:
    window_manager();
    ~window_manager();

    template <typename T>
    auto& create(const std::string& name, int width, int height) {
        return m_windows.emplace_back(std::make_unique<T>(name, width, height));
    };
private:
    bool m_initialized;
    std::vector<std::unique_ptr<window>> m_windows;
};

#endif //JINTERCEPT_WINDOW_MANAGER_H
