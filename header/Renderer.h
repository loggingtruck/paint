#ifndef RENDERER_H
#define RENDERER_H

#include "app.h"
#include "canvas.h"
#include "shader.h"
#include <stdbool.h>

typedef struct Renderer {
    App* app;
    Shader shader;
    unsigned int VAO, VBO, EBO;
} Renderer;

// Initialize the renderer
bool renderer_init(Renderer* renderer, App* app);

// Begin a new frame
void renderer_begin_frame(Renderer* renderer);

// Draw the canvas
void renderer_draw_canvas(Renderer* renderer, Canvas* canvas);

// End the frame
void renderer_end_frame(App* app);

// Clean up renderer resources
void renderer_cleanup(Renderer* renderer);

#endif // RENDERER_H