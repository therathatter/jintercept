
#include "package_manager.h"

klass& package_manager::get_class(std::string name) {
    // Start at the root
    std::reference_wrapper target = get_root();

    // Chop the string down until we get to the right subpackage
    std::string token;
    size_t pos;
    while ((pos = name.find('/')) != std::string::npos) {
        token = name.substr(0, pos);

        target = target.get().m_subpackages[token];
        name.erase(0, pos + 1);
    }

    return target.get().m_classes[name];
}

void package_manager::add_class(const std::string &name, const std::string &source, const jbyte *buf, int size) {
    const std::lock_guard<std::mutex> lock(get_mutex());
    auto& klass = get_class(name);

    klass.m_name = name;
    klass.m_source = source;
    klass.m_code = {buf, buf + size};
    klass.m_path = name.substr(0, name.find_last_of('/'));
}