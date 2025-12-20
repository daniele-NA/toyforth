
#include <jni.h>

#include "compiler/compiler.h"
#include "runtime/runtime.h"
#include "data/s_tfcontext.h"
#include "debug.h"

static s_tfcontext *ctx = NULL;


jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    ctx = tfcontextCreate();

    return JNI_VERSION_1_6;
}


JNIEXPORT jstring JNICALL
Java_com_app_toyforth_MainActivity_runCommand(JNIEnv *env, jclass clazz, jstring jinstruction) {


    char *instruction = (*env)->GetStringUTFChars(env, jinstruction, false);
    const s_tfobj *obj = compile(instruction);


    exec(ctx, obj);

    // tfobjDump(tfcontextGetStack(ctx));

    (*env)->ReleaseStringUTFChars(env, jinstruction, instruction);


    // return the tfobjToString to Compose UI
    return (*env)->NewStringUTF(env, tfobjToString(tfcontextGetStack(ctx)));
}