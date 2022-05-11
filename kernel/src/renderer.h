#pragma once
#include <stdint.h>
#include <stddef.h>

struct Framebuffer
{
	void* BaseAddress;
	size_t BufferSize;
	unsigned int Width;
	unsigned int Height;
	unsigned int PixelsPerScanLine;
};

#pragma once
struct PSF1_HEADER
{
	unsigned char magic[2];
	unsigned char mode;
	unsigned char charsize;
} ;

struct PSF1_FONT
{
	PSF1_HEADER* psf1_Header;
	void* glyphBuffer;
} ;

struct Point
{
    long X;
    long Y;
};

class BasicRenderer
{
    public:
    BasicRenderer(Framebuffer* targetFramebuffer, PSF1_FONT* psf1_Font);
    Point CursorPosition;
    Framebuffer* TargetFramebuffer;
    PSF1_FONT* PSF1_Font;
    uint32_t MouseCursorBuffer[16 * 16];
    uint32_t MouseCursorBufferAfter[16 * 16];
    unsigned int Color;
    unsigned int ClearColor;
    void Print(const char* str);
    void PutChar(char chr, unsigned int xOff, unsigned int yOff);
    void PutChar(char chr);
    inline void PutPix(uint32_t x, uint32_t y, uint32_t colour);
    uint32_t GetPix(uint32_t x, uint32_t y);
    void ClearChar();
    void Clear();
    void Next();
    void DrawOverlayMouseCursor(uint8_t* mouseCursor, Point position, uint32_t colour);
    void ClearMouseCursor(uint8_t* mouseCursor, Point position);
    bool MouseDrawn;
};

extern BasicRenderer* GlobalRenderer;
void Panic(const char* panicMessage);