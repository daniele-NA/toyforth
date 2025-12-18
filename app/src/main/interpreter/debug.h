#pragma once

#ifdef __ANDROID__
#include <android/log.h>
#define LOG_I(...) __android_log_print(ANDROID_LOG_INFO, "MY-LOG", __VA_ARGS__)

// Su Android perror non ha senso, quindi log normale
#define LOG_E(...) __android_log_print(ANDROID_LOG_ERROR, "MY-LOG", __VA_ARGS__)
#else
#include <stdio.h>
#include <errno.h>
#include <string.h>
#define LOG_I(...) do { printf(__VA_ARGS__); } while(0)

// Usa perror per l’errore di sistema
#define LOG_E(msg, ...) do { \
printf("[ERROR] "); \
printf(msg, ##__VA_ARGS__); \
printf(": "); \
perror(""); \
} while(0)
#endif
