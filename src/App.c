#include "App.h"
#include <stdio.h>
#include <stdlib.h>

// Global variables for window dimensions 
static int game_width;
static int game_height;

// Initialize the application window and OpenGL context
bool app_init(App* app, int width, int height, const char* title) {
    // Store initial dimensions
    app->width = width;
    app->height = height;
    app->title = title;
    game_width = width;
    game_height = height;

    // Initialize GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return false;
    }

    // Set OpenGL version to 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Center window on screen
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    int screenWidth = mode->width;
    int screenHeight = mode->height;
    int windowPosX = (screenWidth - width) / 2;
    int windowPosY = (screenHeight - height) / 2;

    // Create a window
    app->window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (app->window == NULL) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return false;
    }
    
    glfwMakeContextCurrent(app->window);
    glfwSetFramebufferSizeCallback(app->window, framebuffer_size_callback);

    // Load OpenGL functions using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        glfwTerminate();
        return false;
    }

    glfwSetWindowPos(app->window, windowPosX, windowPosY);
    return true;
}

// Check if the application should close
bool app_should_close(App* app) {
    return glfwWindowShouldClose(app->window);
}

// Poll for window events
void app_poll_events(void) {
    glfwPollEvents();
}

// End frame and swap buffers
void app_swap_buffers(App* app) {
    glfwSwapBuffers(app->window);
}

// Terminate the application
void app_terminate(App* app) {
    glfwDestroyWindow(app->window);
    glfwTerminate();
}

// Get window dimensions
void app_get_dimensions(App* app, int* width, int* height) {
    *width = game_width;
    *height = game_height;
}

// Get window aspect ratio
float app_get_aspect_ratio(App* app) {
    return (float)game_width / (float)game_height;
}

// Get cursor position in window coordinates
void app_get_cursor_position(App* app, double* xpos, double* ypos) {
    glfwGetCursorPos(app->window, xpos, ypos);
}

// Check if a mouse button is pressed
bool app_is_mouse_button_pressed(App* app, int button) {
    return glfwGetMouseButton(app->window, button) == GLFW_PRESS;
}

// Check if a key is pressed
bool app_is_key_pressed(App* app, int key) {
    return glfwGetKey(app->window, key) == GLFW_PRESS;
}

// Callback for window resizing
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    game_width = width;
    game_height = height;
    glViewport(0, 0, width, height);
}