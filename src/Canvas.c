#include "Canvas.h"
#include <string.h>

// Initialize canvas
void canvas_init(Canvas* canvas, int size) {
    canvas->size = size;
    // Initialize all pixels to white (0)
    memset(canvas->data, COLOR_WHITE, sizeof(canvas->data));
}

// Set pixel value
void canvas_set_pixel(Canvas* canvas, int x, int y, int value) {
    if (canvas_is_valid_coord(canvas, x, y)) {
        canvas->data[y][x] = value;
    }
}

// Get pixel value
int canvas_get_pixel(Canvas* canvas, int x, int y) {
    if (canvas_is_valid_coord(canvas, x, y)) {
        return canvas->data[y][x];
    }
    return COLOR_WHITE; // Default to white for invalid coords
}

// Check if coordinates are within canvas bounds
bool canvas_is_valid_coord(Canvas* canvas, int x, int y) {
    return x >= 0 && x < canvas->size && y >= 0 && y < canvas->size;
}

// Clean up canvas
void canvas_cleanup(Canvas* canvas) {
    //TOOD (very unlikely to do :) )
}

