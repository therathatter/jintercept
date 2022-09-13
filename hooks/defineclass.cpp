
#include "common.h"
#include "../class/package_manager.h"

jclass hooks::JVM_DefineClass(JNIEnv *env, const char *name, jobject loader, const jbyte *buf, jsize len, jobject pd) {
    package_manager::add_class(name);

    return oldJVM_DefineClass(env, name, loader, buf, len, pd);
}


