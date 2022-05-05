#include "shell.h"

void Shell::PrintPrompt()
{
    GlobalRenderer->Color = 0x00ff0000;
    GlobalRenderer->Print("root@SeshOS");
    GlobalRenderer->Color = 0x000000ff;
    GlobalRenderer->Print(" /");
    GlobalRenderer->Color = 0xffffffff;
    GlobalRenderer->Print(" # ");
}

void Shell::TestCMD(const char* input)
{
    GlobalRenderer->Print("You said \"");
    GlobalRenderer->Print(input);
    GlobalRenderer->Print("\"\n");
    if (input == "ver")
    {
        GlobalRenderer->Print("SeshOS version 0.1.0\n");
    }
}


Shell *newShell;