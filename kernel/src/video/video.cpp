#include "video.h"
#include "window.h"

int width =  GlobalRenderer->TargetFramebuffer->Width;
int height = GlobalRenderer->TargetFramebuffer->Height;
unsigned char *framebuffer = (unsigned char *) malloc(width * height * sizeof(unsigned char));

void* address = GlobalRenderer->TargetFramebuffer->BaseAddress;
unsigned int pps = GlobalRenderer->TargetFramebuffer->PixelsPerScanLine;

void memcpy(uint8_t *source, uint8_t *dest, int nbytes) {
    int i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}

static inline void putPixel(int x, int y, uint32_t pixel)
{
    //*((uint32_t*)(GlobalRenderer->TargetFramebuffer->BaseAddress + 4 * GlobalRenderer->TargetFramebuffer->PixelsPerScanLine * y + 4 * x)) = pixel;
    framebuffer[(x * 4) + (y * pps * 4)] = pixel;
    memcpy(framebuffer, (uint8_t*)GlobalRenderer->TargetFramebuffer->BaseAddress, sizeof(framebuffer));
}

void drawRect(int startx, int starty, int width, int height, uint32_t VGA_COLOR)
{
    int endx = startx + width;
    int endy = starty + height;

    for (int x = startx; x < endx; x++)
    {
        for (int y = starty; y < endy; y++)
        {
            putPixel(x, y, VGA_COLOR);
            //GlobalRenderer->PutPix(x, y, VGA_COLOR);
        }
    }
}

uint8_t drawImage(uint32_t *icon, int posx, int posy)
{
    int x = posx;
    int y = posy;
    for (int i = 0; icon[i] != 3; i++)
    {
        if(icon[i] == 2)
        {
            x = posx;
            y++;
        }
        else
        {
            GlobalRenderer->PutPix(x, y, icon[i]);
            x++;
        }
    }
}