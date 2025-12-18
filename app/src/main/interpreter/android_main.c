
#include <jni.h>

#include "compiler/compiler.h"
#include "runtime/runtime.h"
#include "data/s_tfcontext.h"
#include "debug.h"

#ifndef __ANDROID__

int main(int argc, char **argv) {
    s_tfcontext *ctx = tfcontextCreate();

    const s_tfobj *obj = compile("20 4 /");
    tfobjDump(obj);

    exec(ctx, obj);

    LOG_I("\nStack at the end : ");

    tfobjDump(tfcontextGetStack(ctx));

    return 0;
}

#endif

JNIEXPORT void JNICALL
Java_com_app_toyforth_MainActivity_run(JNIEnv* env,jobject thiz) {

    s_tfcontext *ctx =tfcontextCreate();

    const s_tfobj *obj = compile("20 5 /");
    //tfobjDump(obj);

    exec(ctx, obj);

    tfobjDump(tfcontextGetStack(ctx));

}