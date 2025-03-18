#include "Main.h"
#include "Canvas.h"
#include "Renderer.h"
#include "InputHandler.h"
#include <stdio.h>

int main() {
    // Initialize the application
    App app;
    if (!app_init(&app, 880, 880, "32x32 Pixel Art Canvas")) {
        fprintf(stderr, "Failed to initialize application\n");
        return 1;
    }

    // Create canvas
    Canvas canvas;
    canvas_init(&canvas, CANVAS_SIZE);

    // Create renderer
    Renderer renderer;
    if (!renderer_init(&renderer, &app)) {
        fprintf(stderr, "Failed to initialize renderer\n");
        app_terminate(&app);
        return 1;
    }

    // Initialize input handler
    InputHandler input_handler;
    input_handler_init(&input_handler, &app, &canvas);

    // Main loop
    while (!app_should_close(&app)) {
        // Handle inputs
        input_handler_process(&input_handler);
        
        // Render
        renderer_begin_frame(&renderer);
        renderer_draw_canvas(&renderer, &canvas);
        renderer_end_frame(&app);

        // Poll events
        app_poll_events();
    }

    // Cleanup
    renderer_cleanup(&renderer);
    canvas_cleanup(&canvas);
    app_terminate(&app);

    return 0;
}