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

void Shell::TestCMD(char* input)
{
    if (strcmp(input, "ver"))
    {
        GlobalRenderer->Print("SeshOS version 0.1.0\n");
    }
    else if (strcmp(input, "help"))
    {
        GlobalRenderer->Print("List of available commands:\n");
        GlobalRenderer->Print("    ver: shows the version of SeshOS\n");
        GlobalRenderer->Print("    help: shows this menu\n");
        GlobalRenderer->Print("    clear: clears the screen\n");
    }
    else if (strcmp(input, "clear"))
    {
        GlobalRenderer->Clear();
    }
    else
    {
        GlobalRenderer->Print("Unknown command: \"");
        GlobalRenderer->Print(input);
        GlobalRenderer->Print("\"\n");
    }
}


Shell *newShell;