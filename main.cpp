
#include "hooks/common.h"
#include "gui/window_manager.h"
#include "gui/main_window.h"

#include <iostream>
#include <Windows.h>
#include <thread>
#include <atomic>

bool DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    static std::atomic_bool running = true;
    static std::thread main_thread([&] () {
        try {
            hooks::init();

            static window_manager wm;

            const auto& window = wm.create<main_window>("jintercept", 300, 400);

            while (window->render()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }

            FreeLibraryAndExitThread(hinstDLL, 0);
        } catch (const std::runtime_error& e) {
            MessageBoxA(nullptr, e.what(), "jintercept", 0);
        };
    });

    if (fdwReason == DLL_PROCESS_ATTACH) {
        main_thread.detach();
    } else if (fdwReason == DLL_PROCESS_DETACH) {
        running = false;
    }

    return true;
}
