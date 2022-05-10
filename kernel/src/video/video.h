#pragma once
#include <stdint.h>
#include "../memory/memory.h"
#include "../memory/heap.h"
#include "../renderer.h"

void initGUI();
void drawRect(int startx, int starty, int width, int height, uint32_t VGA_COLOR);
void drawWindow(int x, int y, int width, int height, const char* name, uint32_t VGA_COLOR);