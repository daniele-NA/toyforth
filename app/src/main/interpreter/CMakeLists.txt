cmake_minimum_required(VERSION 3.22.1)
project(toyforth LANGUAGES C)

set(CMAKE_C_STANDARD 17)

if (ANDROID)
    # The main function is into android_main.c
    add_library(toyforth SHARED android_main.c

            runtime/runtime.c
            compiler/compiler.c
            data/s_tfcontext.c
            data/s_tfobj.c
            data/s_tfparser.c
    )

find_library(log-lib log)
target_link_libraries(toyforth ${log-lib})
else ()
    # The main function is into desktop_main.c
add_executable(toyforth desktop_main.c

        runtime/runtime.c
        compiler/compiler.c
        data/s_tfcontext.c
        data/s_tfobj.c
        data/s_tfparser.c)

endif ()