
#include "common.h"

#include <stdexcept>
#include <MinHook.h>
#include <thread>

void hooks::init() {
    if (MH_Initialize() != MH_OK) {
        throw std::runtime_error("Failed to initialize MinHook");
    }

    HMODULE jvm = nullptr;

    while (!jvm) {
        jvm = GetModuleHandleA("jvm.dll");
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    void* define_class              = reinterpret_cast<void*>(GetProcAddress(jvm, "JVM_DefineClass"));
    void* define_class_with_source  = reinterpret_cast<void*>(GetProcAddress(jvm, "JVM_DefineClassWithSource"));

    if (!define_class) {
        throw std::runtime_error("Failed to find JVM_DefineClass export");
    }

    if (!define_class_with_source) {
        throw std::runtime_error("Failed to find JVM_DefineClassWithSource export");
    }

    if (MH_CreateHook(define_class, reinterpret_cast<void*>(hooks::JVM_DefineClass),
                      reinterpret_cast<void**>(&hooks::oldJVM_DefineClass)) != MH_OK
                      || MH_EnableHook(define_class) != MH_OK) {
        throw std::runtime_error("Failed to hook JVM_DefineClass");
    }

    if (MH_CreateHook(define_class_with_source, reinterpret_cast<void*>(hooks::JVM_DefineClassWithSource),
                      reinterpret_cast<void**>(&hooks::oldJVM_DefineClassWithSource)) != MH_OK
                      || MH_EnableHook(define_class_with_source) != MH_OK) {
        throw std::runtime_error("Failed to hook JVM_DefineClassWithSource");
    }
}