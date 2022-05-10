#include "video.h"

void* address = GlobalRenderer->TargetFramebuffer->BaseAddress;
int width =  GlobalRenderer->TargetFramebuffer->Width;
int height = GlobalRenderer->TargetFramebuffer->Height;

unsigned char *framebuffer = (unsigned char *) malloc(width * height * sizeof(unsigned char));

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
    GlobalRenderer->ClearColor = 0xff0000a4;
    GlobalRenderer->Clear();

    drawRect(0, 850, 1600, 50, 0xffa4a4a4);

    drawWindow(10, 10, 1000, 200, "Hello World", 0xffffffff);
}

void drawRect(int startx, int starty, int width, int height, uint32_t VGA_COLOR)
{
    int endx = startx + width;
    int endy = starty + height;

    for (int x = startx; x < endx; x++)
    {
        for (int y = starty; y < endy; y++)
        {
            GlobalRenderer->PutPix(x, y, VGA_COLOR);
        }        
    }
}

void drawWindow(int x, int y, int width, int height, const char* name, uint32_t VGA_COLOR)
{
    drawRect(x, y, width, height, 0xffa4a4a4);
    drawRect(x + 1, y, width - 2, height - 1, VGA_COLOR);
    drawRect(x, y, width, 16, 0xff0000ff);
    GlobalRenderer->Color = 0x00000000;
    GlobalRenderer->CursorPosition = {x + 2, y - 1};
    GlobalRenderer->Print(name);
}