
#include <jni.h>

#include "compiler/compiler.h"
#include "runtime/runtime.h"
#include "data/s_tfcontext.h"
#include "debug.h"

JNIEXPORT void JNICALL
Java_com_app_toyforth_MainActivity_run(JNIEnv* env,jobject thiz) {

    s_tfcontext *ctx =tfcontextCreate();

    const s_tfobj *obj = compile("20 5 /");
    //tfobjDump(obj);

    exec(ctx, obj);

    tfobjDump(tfcontextGetStack(ctx));

}