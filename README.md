# ⚙️ ToyForth Interpreter (Android)

## Overview

This repository contains a **small ToyForth interpreter written in C**, embedded in an Android project through **JNI**.

The Android app exists mainly as a **host and interactive shell**. The interpreter is the core of the project and runs entirely in native code.

## 🧠 Interpreter Focus

* Implemented entirely in **C**
* Minimal Forth-like execution model
* Designed for experimentation and learning
* Exposed through a simple interactive shell

The UI layer is intentionally thin and secondary.

## ⚠️ Limitations

This is a **minimal interpreter**.

* Operates **only on integers**
* Several integrity and safety checks are **not implemented**
* Invalid input may cause crashes or undefined behavior

Use with care.

## 🎥 Preview

[Watch the Video](ASSETS/preview.mp4)

## 🖥️ Interactive Shell

The application provides a basic REPL:

* Input is sent directly to the interpreter
* Execution happens in native code
* Output is printed back to the shell

### Currently Available Commands

```
+  -  *  /
dup  abs  pow
```

## 🔧 Extending the Interpreter

To add new functionality:

1. Implement the word in the C source
2. Register it in the interpreter dictionary
3. Rebuild the native library
4. Test carefully

JNI changes are only needed when interaction with Kotlin is required.

To add a new mathematical function:

1. **Update the symbol list** (`sym_chars`) in `tfparserIsSymbol`:

```c
const char sym_chars[] = "+-*/powdupabsnewFunction";
```

2. **Register the function** in `tfcontextCreate`:

```c
tfcontextNewCFunction(ctx,"newFunction",basicMathFunctions);
```

3. **Implement the callback** in `basicMathFunctions`:

```c
if(strcmp(word,"newFunction")==0){
    // code for the new function
}
```

4. Rebuild the native library and test.

## 🧩 Tech Stack

* C (ToyForth interpreter)
* Android NDK
* JNI
* Kotlin
* Jetpack Compose

## 📎 Notes

This project favors **clarity and control over completeness**. It is not meant to be safe or production-ready.

---
