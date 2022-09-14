
#ifndef JINTERCEPT_PACKAGE_MANAGER_H
#define JINTERCEPT_PACKAGE_MANAGER_H

#include "klass.h"
#include "package.h"
#include "../hooks/common.h"

#include <mutex>
#include <vector>
#include <map>

namespace package_manager {
    inline std::mutex mutex;
    inline package root;
    inline klass empty;

    static auto& get_mutex() {
        return mutex;
    }

    static auto& get_root() {
        return root;
    }

    static auto& get_class(std::string name) {
        const std::lock_guard<std::mutex> lock(get_mutex());

        // Start at the root
        std::reference_wrapper target = get_root();

        // Chop the string down until we get to the right subpackage
        std::string token;
        size_t pos;
        while ((pos = name.find('/')) != std::string::npos) {
            token = name.substr(0, pos);

            target = target.get().subpackages[token];
            name.erase(0, pos + 1);
        }

        return target.get().classes[name];
    }

    static void add_class(const std::string& name, const std::string& source, const jbyte* buf, int size) {
        auto& klass = get_class(name);

        klass.name = name;
        klass.source = source;
        klass.code = { buf, buf + size };
    }
};

#endif //JINTERCEPT_PACKAGE_MANAGER_H
