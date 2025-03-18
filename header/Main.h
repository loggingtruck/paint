#ifndef MAIN_H
#define MAIN_H

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Canvas size 
#define CANVAS_SIZE 32 // 32x32 grid

typedef struct App App;
typedef struct Canvas Canvas;
typedef struct Shader Shader;
typedef struct Renderer Renderer;
typedef struct InputHandler InputHandler;

#endif // MAIN_H