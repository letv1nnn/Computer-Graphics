# *Graphics with OpenGL*

I'm storing my notes and core implementation of OpenGL graphics. I've orginized my notes, so anyone could understand the foundation of computer graphics.

### *Prerequisites*
I've used [GLFW](https://www.glfw.org/download) and [GLAD](https://glad.dav1d.de/) to work with OpenGL.

### *Compilation*
To compile most of the programs in this directory, you need to use the following command. I did not want to create a Makefile for each 100 lines of code C++ file. I've created a ***Dependencies*** directory and stored all required libs there. For some serious programs, I'm definitely going to configure Makefile/Cmake files and attach full instructions.

***Example***
```shell
g++ "program.cpp" "path/to/glad.c" -I"path/to/include/dir" -Iinclude -lglfw -ldl
```

