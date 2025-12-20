#include <jni.h>

#include "compiler/compiler.h"
#include "runtime/runtime.h"
#include "data/s_tfcontext.h"
#include "debug.h"

static s_tfcontext *ctx = NULL;

/* Called when the native library is loaded */
jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    ctx = tfcontextCreate();

    return JNI_VERSION_1_6;
}

/* Run a Forth command from Java and return the result as a string */
JNIEXPORT jstring JNICALL
Java_com_app_toyforth_MainActivity_runCommand(JNIEnv *env, jclass clazz, jstring jinstruction) {

    /* Convert Java string to C string */
    char *instruction = (*env)->GetStringUTFChars(env, jinstruction, false);

    /* Compile the instruction */
    const s_tfobj *obj = compile(instruction);

    /* Execute the compiled object */
    exec(ctx, obj);

    // tfobjDump(tfcontextGetStack(ctx));

    /* Release the C string */
    (*env)->ReleaseStringUTFChars(env, jinstruction, instruction);

    /* Return the string representation of the stack to Compose UI */
    return (*env)->NewStringUTF(env, tfobjToString(tfcontextGetStack(ctx)));
}
