#ifndef JINTERCEPT_PACKAGE_MANAGER_H
#define JINTERCEPT_PACKAGE_MANAGER_H

#include "klass.h"
#include <vector>
#include <map>
#include "package.h"
#include <Windows.h>
#include <mutex>

namespace package_manager {
    inline std::mutex mutex;
    inline package root;

    static auto& get_mutex() {
        return mutex;
    }

    static auto& get_root() {
        return root;
    }

    static void add_class(std::string name) {
        const std::lock_guard<std::mutex> lock(get_mutex());

        // Start at the root
        std::reference_wrapper target = get_root();

        // Chop the string down until we get to the right package and class
        std::string token;
        size_t pos;
        while ((pos = name.find('/')) != std::string::npos) {
            token = name.substr(0, pos);

            target = target.get().subpackages[token];
            name.erase(0, pos + 1);
        }

        target.get().classes[name] = {
                name
        };
    }
};

#endif //JINTERCEPT_PACKAGE_MANAGER_H
