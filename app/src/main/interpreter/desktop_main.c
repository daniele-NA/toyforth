int main(int argc, char **argv) {
    s_tfcontext *ctx = tfcontextCreate();

    const s_tfobj *obj = compile("20 4 /");
    tfobjDump(obj);

    exec(ctx, obj);

    LOG_I("\nStack at the end : ");

    tfobjDump(tfcontextGetStack(ctx));

    return 0;
}