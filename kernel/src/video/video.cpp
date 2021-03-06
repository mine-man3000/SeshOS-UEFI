#include "video.h"
#include "window.h"
#include "../scheduling/pit.h"


int width =  GlobalRenderer->TargetFramebuffer->Width;
int height = GlobalRenderer->TargetFramebuffer->Height;
unsigned char *framebuffer = (unsigned char *) malloc(width * height * sizeof(unsigned char));


void memcpy(uint8_t *source, uint8_t *dest, int nbytes)
{
    for (int i = 0; i < nbytes; i++)
    {
        *(dest + i) = *(source + i);
    }
}

static inline void putPixel(int x, int y, uint32_t pixel)
{
    void* address = GlobalRenderer->TargetFramebuffer->BaseAddress;
    unsigned int pps = GlobalRenderer->TargetFramebuffer->PixelsPerScanLine;

    *((uint32_t*)(address + 4 * pps * y + 4 * x)) = pixel;
    //framebuffer[4 * pps * y + 4 * x] = pixel;
    //memcpy(framebuffer, (uint8_t*)GlobalRenderer->TargetFramebuffer->BaseAddress, sizeof(framebuffer));
}

void drawRectDiag(int startx, int starty, int endx, int endy, uint32_t VGA_COLOR)
{
    int x = startx;
    for (int y = starty; y < endy; y+=2)
    {
        putPixel(x, y, VGA_COLOR);  
        x++;
    }
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
        if(icon[i] == 2 || icon[i] == '2')
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

void nComIntro()
{
    //draw big N
    drawRect(72, 10, 25, 250, 0xffffffff);

    PIT::Sleepd(1);

    drawRect(197, 10, 25, 250, 0xffffffff);
    for (int i = 0; i < 50; i++)
    {
        drawRectDiag(97, 10+i, 160, 210+i, 0xffffffff);
    }

    //draw small N
    drawRect(10, 270, 5, 30, 0xffffffff);
    for (int i = 0; i < 5; i++)
    {
        drawRectDiag(15, 270+i, 20, 295+i, 0xffffffff);        
    }
    drawRect(28, 270, 5, 30, 0xffffffff);

    //draw the O

    drawRect(38, 270, 18, 5, 0xffffffff);

    drawRect(38, 270, 5, 25, 0xffffffff);
    drawRect(56, 270, 5, 30, 0xffffffff);


    drawRect(38, 295, 18, 5, 0xffffffff);

    //draw the W

    drawRect(66, 270, 5, 25, 0xffffffff);
    drawRect(66, 295, 18, 5, 0xffffffff);

    drawRect(75, 270, 5, 25, 0xffffffff);

    drawRect(84, 270, 5, 30, 0xffffffff);

    drawRect(66, 295, 18, 5, 0xffffffff);

    //skip space and draw the L

    drawRect(118, 270, 5, 25, 0xffffffff);
    drawRect(118, 295, 18, 5, 0xffffffff);

    //draw O

    drawRect(142, 270, 18, 5, 0xffffffff);

    drawRect(142, 270, 5, 25, 0xffffffff);
    drawRect(160, 270, 5, 30, 0xffffffff);

    drawRect(142, 295, 18, 5, 0xffffffff);

    //draw A

    drawRect(170, 270, 5, 30, 0xffffffff);
    drawRect(188, 270, 5, 30, 0xffffffff);

    drawRect(170, 285, 18, 5, 0xffffffff);
    drawRect(170, 270, 18, 5, 0xffffffff);

    //draw the D

    drawRect(198, 270, 18, 5, 0xffffffff);

    drawRect(198, 270, 5, 25, 0xffffffff);
    drawRect(216, 275, 5, 20, 0xffffffff);

    drawRect(198, 295, 18, 5, 0xffffffff);

    //draw the I

    drawRect(226, 270, 5, 5,  0xffffffff);

    drawRect(226, 280, 5, 20,  0xffffffff);

    //draw the final N

    drawRect(236, 270, 5, 30, 0xffffffff);
    for (int i = 0; i < 5; i++)
    {
        drawRectDiag(241, 270+i, 20, 295+i, 0xffffffff);        
    }
    drawRect(254, 270, 5, 30, 0xffffffff);

    //draw the G

    drawRect(264, 295, 18, 5, 0xffffffff);
    drawRect(264, 270, 5, 30, 0xffffffff);
    drawRect(264, 270, 18, 5, 0xffffffff);
    drawRect(273, 285, 9, 5,  0xffffffff);
    drawRect(277, 285, 5, 10, 0xffffffff);
}