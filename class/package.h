
#ifndef JINTERCEPT_PACKAGE_H
#define JINTERCEPT_PACKAGE_H

#include "klass.h"

#include <map>

class package {
public:
    std::map<std::string, klass> m_classes;
    std::map<std::string, package> m_subpackages;
};

#endif //JINTERCEPT_PACKAGE_H
