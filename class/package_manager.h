
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

    static auto& get_mutex() {
        return mutex;
    }

    static auto& get_root() {
        return root;
    }

    klass& get_class(std::string name);
    void add_class(const std::string& name, const std::string& source, const jbyte* buf, int size);
};

#endif //JINTERCEPT_PACKAGE_MANAGER_H
