#ifndef CANVAS_H
#define CANVAS_H

#include <stdbool.h>

// Canvas size definition
#define CANVAS_SIZE 32 // 32x32 grid

// Canvas colors
#define COLOR_WHITE 0
#define COLOR_BLACK 1

typedef struct Canvas { // &Canvas -> struct Canvas
    int data[CANVAS_SIZE][CANVAS_SIZE];
    int size;
} Canvas;

// Initialize canvas
void canvas_init(Canvas* canvas, int size);

// Set pixel value
void canvas_set_pixel(Canvas* canvas, int x, int y, int value);

// Get pixel value
int canvas_get_pixel(Canvas* canvas, int x, int y);

// Check if coordinates are within canvas bounds
bool canvas_is_valid_coord(Canvas* canvas, int x, int y);

// Clean up canvas
void canvas_cleanup(Canvas* canvas);

#endif // CANVAS_H