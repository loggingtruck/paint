#include "InputHandler.h"
#include <stdbool.h>

// Initialize input handler
void input_handler_init(InputHandler* handler, App* app, Canvas* canvas) {
    handler->app = app;
    handler->canvas = canvas;
}

// Process input events
void input_handler_process(InputHandler* handler) {
    input_handler_process_keyboard(handler);
    input_handler_process_mouse(handler);
}

// Handle mouse input for drawing on canvas
void input_handler_process_mouse(InputHandler* handler) {
    // Check if either mouse button is pressed
    if (app_is_mouse_button_pressed(handler->app, GLFW_MOUSE_BUTTON_LEFT) || 
        app_is_mouse_button_pressed(handler->app, GLFW_MOUSE_BUTTON_RIGHT)) {
        
        double xpos, ypos;
        app_get_cursor_position(handler->app, &xpos, &ypos);
        
        // Convert cursor position to canvas grid coordinates
        int gridX, gridY;
        if (input_handler_window_to_canvas(handler, xpos, ypos, &gridX, &gridY)) {
            // Set pixel value based on which mouse button is pressed
            if (app_is_mouse_button_pressed(handler->app, GLFW_MOUSE_BUTTON_LEFT)) {
                canvas_set_pixel(handler->canvas, gridX, gridY, COLOR_BLACK);
            } else if (app_is_mouse_button_pressed(handler->app, GLFW_MOUSE_BUTTON_RIGHT)) {
                canvas_set_pixel(handler->canvas, gridX, gridY, COLOR_WHITE);
            }
        }
    }
}

// Handle keyboard input
void input_handler_process_keyboard(InputHandler* handler) {
    // Close application on ESC key
    if (app_is_key_pressed(handler->app, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(handler->app->window, true);
    }
}

// Convert window coordinates to canvas grid coordinates
bool input_handler_window_to_canvas(InputHandler* handler, double xpos, double ypos, int* gridX, int* gridY) {
    int width, height;
    app_get_dimensions(handler->app, &width, &height);
    
    // Convert window coordinates to normalized device coordinates
    float ndcX = (2.0f * xpos / width - 1.0f);
    float ndcY = (1.0f - 2.0f * ypos / height);

    // Calculate canvas position and size
    float windowAspect = (float)width / (float)height;
    float canvasAspect = 1.0f; // Canvas is square
    
    float canvasSize, canvasX, canvasY;
    float canvasLeft, canvasTop;
    float canvasSizeX, canvasSizeY;
    
    if (windowAspect >= canvasAspect) {
        // Window is wider than canvas
        canvasSize = 2.0f;
        canvasX = canvasSize * windowAspect / 2.0f;
        canvasY = 1.0f;
        
        // Center horizontally
        canvasLeft = -canvasX;
        canvasTop = canvasY;
        canvasSizeX = canvasSize * windowAspect;
        canvasSizeY = canvasSize;
    } else {
        // Window is taller than canvas
        canvasSize = 2.0f * windowAspect;
        canvasX = 1.0f;
        canvasY = canvasSize / windowAspect / 2.0f;
        
        // Center vertically
        canvasLeft = -canvasX;
        canvasTop = canvasY;
        canvasSizeX = canvasSize;
        canvasSizeY = canvasSize / windowAspect;
    }

    // Translate to canvas coordinates (0 to 1)
    float canvasRelX = (ndcX - canvasLeft) / canvasSizeX;
    float canvasRelY = (canvasTop - ndcY) / canvasSizeY;

    // Convert to grid coordinates
    *gridX = (int)(canvasRelX * handler->canvas->size);
    *gridY = (int)(canvasRelY * handler->canvas->size);

    // Check if the coordinates are within the canvas bounds
    return canvas_is_valid_coord(handler->canvas, *gridX, *gridY);
}