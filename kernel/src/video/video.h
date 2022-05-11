#pragma once
#include <stdint.h>
#include "../memory/memory.h"
#include "../memory/heap.h"
#include "../renderer.h"

void initGUI();
void drawRect(int startx, int starty, int width, int height, uint32_t VGA_COLOR);
uint8_t drawImage(uint32_t *icon, int posx, int posy);