#include "video.h"

void* address = GlobalRenderer->TargetFramebuffer->BaseAddress;
int width =  GlobalRenderer->TargetFramebuffer->Width;
int height = GlobalRenderer->TargetFramebuffer->Height;

unsigned char *framebuffer = (unsigned char *) malloc(width * height);

void memcpy(uint8_t *source, uint8_t *dest, int nbytes)
{
    int i;
    for (i = 0; i < nbytes; i++)
    {
        *(dest + i) = *(source + i);
    }
}

void initGUI()
{
    GlobalRenderer->ClearColor = 0x000000ff;
    GlobalRenderer->Clear();

    drawRect(0, height - (height - 40), width, height, 0xaaaaaaaa);
}

void drawRect(int startx, int starty, int width, int height, unsigned char VGA_COLOR)
{
    int endx = startx + width;
    int endy = starty + height;

    for (int i = startx; i < endx; i++)
    {
        for (int j = starty; j < endy; j++)
        {
            framebuffer[i + j * width] = VGA_COLOR;
        }        
    }
    memcpy(framebuffer, (uint8_t*)address, sizeof(framebuffer));
}