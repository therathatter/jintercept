
#include "common.h"
#include "../class/package_manager.h"

jclass hooks::JVM_DefineClassWithSource(JNIEnv *env, const char *name, jobject loader, const jbyte *buf, jsize len, jobject pd, const char *source) {
    package_manager::add_class(name, source, buf, len);

    return oldJVM_DefineClassWithSource(env, name, loader, buf, len, pd, source);
}