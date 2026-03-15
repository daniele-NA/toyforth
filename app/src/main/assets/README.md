# ToyForth

A minimal **Forth interpreter written in C**, embedded in an Android app via **JNI**.

The app serves as an interactive shell — the interpreter runs entirely in native code.

## Interpreter

* Written in **C**, exposed through JNI
* Minimal Forth-like execution model
* Operates **only on integers**
* Available words: `+ - * / dup abs pow`

> This is a learning project — safety checks are minimal and invalid input may crash.

## AGSL Shaders

The app uses **AGSL** (Android Graphics Shading Language) for real-time animated backgrounds.

Shader files live in `assets/shaders/` and are loaded at runtime:

```kotlin
val src = context.assets.open("shaders/orbit.agsl").bufferedReader().readText()
RuntimeShader(src)
```

Uniforms (`iResolution`, `iTime`) are updated every frame via `drawBehind` in Compose.

## Tech Stack

* C + Android NDK + JNI
* Kotlin + Jetpack Compose
* AGSL (RuntimeShader)
