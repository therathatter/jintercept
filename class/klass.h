#ifndef JINTERCEPT_KLASS_H
#define JINTERCEPT_KLASS_H

#include <vector>
#include <string>

class klass {
public:
    std::string name;
    std::string source;
    std::vector<uint8_t> code;

};

#endif //JINTERCEPT_KLASS_H
