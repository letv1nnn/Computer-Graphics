# ***OpenGL Fundamentals***

It's basically my way through ***[Learn OpenGL](https://learnopengl.com/)*** book and some research in graphics with OpenGL. I'd leave my notes and ideas here, so it's going to be like bee notebook.

---

## ***OpenGL Buffers***
Primarily, need to define how OpenGL handle the memory access with buffers.

In CPU world you store data in RAM using variables, arrays etc. You work with them via pointers or references. However, in GPU world, ***buffers*** are chunks of GPU memory. You can't get a pointer to them, you work with them through an ***integer ID*** (handle) that OpenGL provides.

***Loading data into a GPU buffer***

1. Generate an ID

CPU analogy: like integer pointer. You now have a ***label*** but not allocated memory yet. 
```cpp
GLuint vbo;
glGenBuffers(1, &vbo);
```

2. Bind the buffer to a target

Basically, likee deciding the "type" of that memory.

CPU analogy: "this pointer will store vertex data", but instead of a type keyword, you specify a target (***GL_ARRAY_BUFFER***, ***GL_ELEMENT_ARRAY_BUFFER***, etc.).

```cpp
glBindBuffer(GL_ARRAY_BUFFER, vbo);
```

3. Allocate storage and upload data

Like ***malloc()*** + ***memcpy()*** in C terminology.

CPU analogy: allocates space and then fills it with your data. In OpenGL, ***glBufferData*** does both at once.

```cpp
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
```

***Example***
```cpp
// CPU:
int arr[3] = {1, 2, 3};

// GPU:
float array[3] = {1.0f, 2.0f, 3.0f};

GLuint id;
glGenBuffers(1, &id);
glBindBuffer(GL_ARRAY_BUFFER, id);
glBufferData(GL_ARRAY_BUFFER, sizeof(array), array, GL_STATIC_DRAW);
```

## ***Shaders***

Then, I'd like to talk about shaders foundation, what are they and how to interact with them. In consequence, I'd like to draw a triangle and write some shaders for it using ***GLSL*** (OpenGL Shading Language).

***Graphics Pipeline***

![graphics pipeline](basic_opengl_images/graphics-pipeline.png)


***Writing Shaders***

In the example below, I've configured the ***Vertex*** and ***Fragment*** shaders.

```cpp
const char *vertexShaderSource = "#version 450 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 450 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";
```

