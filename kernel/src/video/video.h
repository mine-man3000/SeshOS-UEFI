#pragma once
#include <stdint.h>
#include "../memory/memory.h"
#include "../memory/heap.h"
#include "../renderer.h"

void initGUI();
void drawRect(int startx, int starty, int width, int height, uint32_t VGA_COLOR);

struct Pixel
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};