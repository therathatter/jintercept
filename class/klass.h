
#ifndef JINTERCEPT_KLASS_H
#define JINTERCEPT_KLASS_H

#include <vector>
#include <string>

class klass {
public:
    std::string m_name;
    std::string m_source;
    std::string m_path;
    std::vector<uint8_t> m_code;

    // TODO: a class probably should not be the one writing itself to disk
    //       but this is convenient for now
    void write_to_disk() const;
};

#endif //JINTERCEPT_KLASS_H
