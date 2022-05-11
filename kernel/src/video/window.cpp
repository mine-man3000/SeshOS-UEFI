#include "window.h"
#include "video.h"
#include "../cstr.h"

uint32_t closeIcon[] = 
{
    0x00ff0000, 0x00ff0000, 0x00ff0000, 0x00ff0000, 0x00ff0000, 0x00ff0000, 0x00ff0000, 0x00ff0000, 0x00ff0000, 0x00ff0000, 2,
    0x00ff0000, 0x00ff0000, 0x00ff0000, 0x00ff0000, 0x00ff0000, 0x00ff0000, 0x00ff0000, 0x00ff0000, 0x00ff0000, 0x00ff0000, 2,
    0x00ff0000, 0x00ff0000, 0xffffffff, 0xffffffff, 0x00ff0000, 0x00ff0000, 0xffffffff, 0xffffffff, 0x00ff0000, 0x00ff0000, 2,
    0x00ff0000, 0x00ff0000, 0xffffffff, 0xffffffff, 0x00ff0000, 0x00ff0000, 0xffffffff, 0xffffffff, 0x00ff0000, 0x00ff0000, 2,
    0x00ff0000, 0x00ff0000, 0x00ff0000, 0x00ff0000, 0xffffffff, 0xffffffff, 0x00ff0000, 0x00ff0000, 0x00ff0000, 0x00ff0000, 2,
    0x00ff0000, 0x00ff0000, 0x00ff0000, 0x00ff0000, 0xffffffff, 0xffffffff, 0x00ff0000, 0x00ff0000, 0x00ff0000, 0x00ff0000, 2,
    0x00ff0000, 0x00ff0000, 0xffffffff, 0xffffffff, 0x00ff0000, 0x00ff0000, 0xffffffff, 0xffffffff, 0x00ff0000, 0x00ff0000, 2,
    0x00ff0000, 0x00ff0000, 0xffffffff, 0xffffffff, 0x00ff0000, 0x00ff0000, 0xffffffff, 0xffffffff, 0x00ff0000, 0x00ff0000, 2,
    0x00ff0000, 0x00ff0000, 0x00ff0000, 0x00ff0000, 0x00ff0000, 0x00ff0000, 0x00ff0000, 0x00ff0000, 0x00ff0000, 0x00ff0000, 2,
    0x00ff0000, 0x00ff0000, 0x00ff0000, 0x00ff0000, 0x00ff0000, 0x00ff0000, 0x00ff0000, 0x00ff0000, 0x00ff0000, 0x00ff0000, 3,
};

void Window::DrawWindow()
{
    drawRect(m_Startx, m_Starty, m_Width, m_Height, 0xffa4a4a4);
    drawRect(m_Startx + 1, m_Starty, m_Width - 2, m_Height - 1, m_BackgroundColor);
    drawRect(m_Startx, m_Starty, m_Width, 16, 0xff0000ff);
    GlobalRenderer->Color = 0x00000000;
    GlobalRenderer->CursorPosition = {m_Startx + 2, m_Starty - 1};
    GlobalRenderer->Print(m_Name);
    drawImage(closeIcon, m_Startx + m_Width - 12, m_Starty + 2);
}

Window::Window(int x, int y, int width, int height, const char* name, uint32_t backgroundColor)
{   
    m_Width = width;
    m_Height = height;
    m_Startx = x;
    m_Starty = y;
    m_MouseX = GlobalMouse.pos.X;
    m_MouseY = GlobalMouse.pos.Y;

    int i = 0;
    for (; name[i] != '\0'; i++)
    {
        m_Name[i] = name[i];
    }
    m_Name[i] = '\0';

    m_BackgroundColor = backgroundColor;
    DrawWindow();
}

void Window::UpdateWindow()
{
    m_MouseX = GlobalMouse.pos.X;
    m_MouseY = GlobalMouse.pos.Y;

    DrawWindow();

    if (GlobalMouse.LeftDown /*&& m_MouseX > x && m_MouseX < x + width && m_MouseY > y && m_MouseY < x + height*/)
    {
        GlobalRenderer->Print("CLICK");
        m_Startx = m_MouseX;
        m_Starty = m_MouseY;
        DrawWindow();
    }
}