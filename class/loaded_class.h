#ifndef JINTERCEPT_LOADED_CLASS_H
#define JINTERCEPT_LOADED_CLASS_H

#include <vector>

class loaded_class {


};

class class_manager {
    const static auto& get_loaded_classes() {
        return loaded_classes;
    }
private:
    static std::vector<loaded_class> loaded_classes;
};

#endif //JINTERCEPT_LOADED_CLASS_H
