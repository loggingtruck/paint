#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "app.h"
#include "canvas.h"
#include <GLFW/glfw3.h>

typedef struct InputHandler {
    App* app;
    Canvas* canvas;
} InputHandler;

// Initialize input handler
void input_handler_init(InputHandler* handler, App* app, Canvas* canvas);

// Process input events
void input_handler_process(InputHandler* handler);

// Handle mouse input for drawing on canvas
void input_handler_process_mouse(InputHandler* handler);

// Handle keyboard input
void input_handler_process_keyboard(InputHandler* handler);

// Convert window coordinates to canvas grid coordinates
bool input_handler_window_to_canvas(InputHandler* handler, double xpos, double ypos, int* gridX, int* gridY);

#endif // INPUT_HANDLER_H