
#include <iostream>
#include <Windows.h>
#include <thread>
#include <atomic>
#include "gui/gui.h"

bool DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    static std::atomic_bool running = true;
    static std::thread main_thread([&] () {
        try {
            gui::init();

            while (gui::render() && running) {

            }

            gui::shutdown();
        } catch (const std::runtime_error& e) {
            std::cerr << "Fatal error: " << e.what();
        };
    });

    if (fdwReason == DLL_PROCESS_ATTACH) {
        main_thread.detach();
    } else if (fdwReason == DLL_PROCESS_DETACH) {
        running = false;
    }

    return true;
}
