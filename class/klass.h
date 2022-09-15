
#ifndef JINTERCEPT_KLASS_H
#define JINTERCEPT_KLASS_H

#include <vector>
#include <string>

class klass {
public:
    std::string m_name;
    std::string m_source;
    std::vector<uint8_t> m_code;
};

#endif //JINTERCEPT_KLASS_H
