#include "Renderer.h"
#include <stdlib.h>

// Vertex and fragment shader sources
static const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec2 aPos;\n"
    "uniform vec2 offset;\n"
    "uniform vec2 scale;\n"
    "void main() {\n"
    "   gl_Position = vec4(aPos.x * scale.x + offset.x, aPos.y * scale.y + offset.y, 0.0, 1.0);\n"
    "}\0";

static const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec3 color;\n"
    "void main() {\n"
    "   FragColor = vec4(color, 1.0);\n"
    "}\0";

// Initialize the renderer
    bool renderer_init(Renderer* renderer, App* app) {
    renderer->app = app;
    
    // Create shader program
    if (!shader_create(&renderer->shader, vertexShaderSource, fragmentShaderSource)) {
        return false;
    }
    
    // Set up vertex data and buffers for a single pixel (square)
    // Make the vertices slightly larger to avoid gaps
    float vertices[] = {
        -0.51f, -0.51f,  // Slight overlap to avoid gaps
         0.51f, -0.51f,
         0.51f,  0.51f,
        -0.51f,  0.51f
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    // Create and initialize vertex objects
    glGenVertexArrays(1, &renderer->VAO);
    glGenBuffers(1, &renderer->VBO);
    glGenBuffers(1, &renderer->EBO);

    glBindVertexArray(renderer->VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, renderer->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    return true;
}

// Begin a new frame
void renderer_begin_frame(Renderer* renderer) {
    // Clear the screen with white
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // White background
    glClear(GL_COLOR_BUFFER_BIT);
}

// Draw the canvas
void renderer_draw_canvas(Renderer* renderer, Canvas* canvas) {
    int width, height;
    app_get_dimensions(renderer->app, &width, &height);
    float windowAspect = (float)width / (float)height;
    float canvasAspect = 1.0f; // Canvas is square
    
    // Size of the square canvas in the window (in normalized device coordinates)
    float canvasSize, canvasX, canvasY;
    if (windowAspect >= canvasAspect) {
        // Window is wider than canvas - use height to determine the canvas size
        canvasSize = 2.0f; // Use full height (-1 to 1)
        canvasX = canvasSize * windowAspect / 2.0f;
        canvasY = 1.0f;
    } else {
        // Window is taller than canvas - use width to determine the canvas size
        canvasSize = 2.0f * windowAspect; // Use full width (-windowAspect to windowAspect)
        canvasX = 1.0f;
        canvasY = canvasSize / windowAspect / 2.0f;
    }
    
    // Calculate pixel size
    float pixelScaleX = (canvasSize / canvas->size);
    float pixelScaleY = pixelScaleX; // Keep pixels square
    
    // Activate shader
    shader_use(&renderer->shader);
    
    // Set the scale uniforms for square pixels
    shader_set_uniform_vec2(&renderer->shader, "scale", pixelScaleX, pixelScaleY);
    
    // Draw each pixel
    for (int y = 0; y < canvas->size; y++) {
        for (int x = 0; x < canvas->size; x++) {
            // Only draw black pixels
            if (canvas_get_pixel(canvas, x, y) == COLOR_BLACK) {
                // Set the color to black
                shader_set_uniform_vec3(&renderer->shader, "color", 0.0f, 0.0f, 0.0f);

                // Calculate the position of the pixel in normalized device coordinates
                float xPos, yPos;
                
                if (windowAspect >= canvasAspect) {
                    // Window is wider than canvas - center horizontally
                    float canvasLeftEdge = -canvasX;
                    xPos = canvasLeftEdge + (x + 0.5f) * pixelScaleX;
                    yPos = 1.0f - (y + 0.5f) * pixelScaleY;
                } else {
                    // Window is taller than canvas - center vertically
                    float canvasTopEdge = canvasY;
                    xPos = -1.0f + (x + 0.5f) * pixelScaleX;
                    yPos = canvasTopEdge - (y + 0.5f) * pixelScaleY;
                }

                // Draw the pixel
                glBindVertexArray(renderer->VAO);
                shader_set_uniform_vec2(&renderer->shader, "offset", xPos, yPos);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }
        }
    }
}

// End the frame
void renderer_end_frame(App* app) {
    app_swap_buffers(app);
}

// Clean up renderer resources
void renderer_cleanup(Renderer* renderer) {
    glDeleteVertexArrays(1, &renderer->VAO);
    glDeleteBuffers(1, &renderer->VBO);
    glDeleteBuffers(1, &renderer->EBO);
    shader_delete(&renderer->shader);
}