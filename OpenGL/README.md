# Graphics with OpenGL

## Prerequisites
- [GLFW](https://www.glfw.org/download)
- [GLAD](https://glad.dav1d.de/)

## Sources
### Books
- Learn OpenGL: Learn modern OpenGL graphics programming in a step-by-step fashion.
### Playlists
- [Jamie King](https://www.youtube.com/playlist?list=PLRwVmtr-pp06qT6ckboaOhnm9FxmzHpbY) playlist, kind of old, but still relevant, explains the fundamentals in appropriate way.

## Compilation
To compile most of the programs in this directory, you need to use the following command. I did not want to create a Makefile for each 100 lines of code C++ file. I've created a ***Dependencies*** directory and stored all required libs there. For some serious programs, I'm definitely going to configure Makefile/Cmake files and attach full instructions.

***Example***
```bash
g++ window.cpp ../Dependencies/glad/src/glad.c -I../Dependencies/glad/include/ -Iinclude -lglfw -ldl
```

