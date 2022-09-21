
#include <filesystem>
#include <fstream>
#include "klass.h"

void klass::write_to_disk() const {
    std::filesystem::create_directories("jintercept/" + m_path);

    std::ofstream klass_file("jintercept/" + m_path + "/" + m_name + ".class", std::ios::ate | std::ios::binary);
    klass_file.write(reinterpret_cast<const char*>(m_code.data()), m_code.size());
    klass_file.close();
}
