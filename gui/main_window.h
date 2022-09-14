
#ifndef JINTERCEPT_MAIN_WINDOW_H
#define JINTERCEPT_MAIN_WINDOW_H

#include "window.h"

class main_window : public window {
public:
    using window::window;

    void glfw_callback() override;
};

#endif //JINTERCEPT_MAIN_WINDOW_H
