#ifndef JINTERCEPT_COMMON_H
#define JINTERCEPT_COMMON_H

#include <cstdint>

typedef struct JNINativeInterface_* JNIEnv;
typedef struct _jobject* jobject;
typedef jobject jclass;
typedef int jint;
typedef uint8_t jbyte;
typedef jint jsize;

namespace hooks {
    void init();
    jclass JVM_DefineClass(JNIEnv *env, const char *name, jobject loader, const jbyte *buf, jsize len, jobject pd);
    jclass JVM_DefineClassWithSource(JNIEnv *env, const char *name, jobject loader, const jbyte *buf, jsize len, jobject pd, const char *source);

    inline decltype(&JVM_DefineClass) oldJVM_DefineClass= nullptr;
    inline decltype(&JVM_DefineClassWithSource) oldJVM_DefineClassWithSource = nullptr;
}

#endif //JINTERCEPT_COMMON_H


