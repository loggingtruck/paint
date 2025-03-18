#ifndef APP_H
#define APP_H

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>

typedef struct App {
    GLFWwindow* window;
    int width;
    int height;
    const char* title;
} App;

// Initialize the application window and OpenGL context
bool app_init(App* app, int width, int height, const char* title);

// Check if the application should close
bool app_should_close(App* app);

// Poll for window events
void app_poll_events(void);

// Swap buffers
void app_swap_buffers(App* app);

// Terminate the application
void app_terminate(App* app);

// Get window dimensions
void app_get_dimensions(App* app, int* width, int* height);

// Get window aspect ratio
float app_get_aspect_ratio(App* app);

// Get cursor position in window coordinates
void app_get_cursor_position(App* app, double* xpos, double* ypos);

// Check if a mouse button is pressed
bool app_is_mouse_button_pressed(App* app, int button);

// Check if a key is pressed
bool app_is_key_pressed(App* app, int key);

// Callback for window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#endif // APP_H