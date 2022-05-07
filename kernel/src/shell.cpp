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
    else if (strcmp(input, "ls"))
    {
        ls();
    }
    else if (strcmp(input, "volinfo"))
    {
        volInfo();
    }
    else if (strcmp(input, "neofetch"))
    {
        GlobalRenderer->Print("SSSSSS   EEEEEE  SSSSSS  HH  HH    root@SeshOS\n");
        GlobalRenderer->Print("SSSSSS   EEEEEE  SSSSSS  HH  HH    -----------\n");
        GlobalRenderer->Print("SSS      EE      SSS     HH  HH    OS: SeshOS 0.1.0\n");
        GlobalRenderer->Print("SSS      EE      SSS     HH  HH    Kernel: 0.1.0\n");
        GlobalRenderer->Print("SSSSSS   EEEEEE  SSSSSS  HHHHHH    Shell: SeSH (Sesh SHell)\n");
        GlobalRenderer->Print("SSSSSS   EEEEEE  SSSSSS  HHHHHH    Resolution: "); 
        GlobalRenderer->Print(to_string((uint64_t)GlobalRenderer->TargetFramebuffer->Width));
        GlobalRenderer->Print("x");
        GlobalRenderer->Print(to_string((uint64_t)GlobalRenderer->TargetFramebuffer->Height));
        GlobalRenderer->Print("\n");
        GlobalRenderer->Print("   SSS   EE         SSS  HH  HH    \n");
        GlobalRenderer->Print("   SSS   EE         SSS  HH  HH    \n");
        GlobalRenderer->Print("SSSSSS   EEEEEE  SSSSSS  HH  HH    \n");
        GlobalRenderer->Print("SSSSSS   EEEEEE  SSSSSS  HH  HH    \n");
        GlobalRenderer->Print("                                   \n");
        GlobalRenderer->Print("                 OOOOOO  SSSSSS    \n");
        GlobalRenderer->Print("    II  II       OO  OO  SSSSSS    \n");
        GlobalRenderer->Print("    II  II       OO  OO  SSS       \n");
        GlobalRenderer->Print("    II  II       OO  OO  SSS       \n");
        GlobalRenderer->Print("  \\\\      //     OO  OO  SSSSSS    \n");
        GlobalRenderer->Print("   \\\\====//      OO  OO  SSSSSS    \n");
        GlobalRenderer->Print("                 OO  OO     SSS    \n");
        GlobalRenderer->Print("                 OO  OO     SSS    \n");
        GlobalRenderer->Print("                 OO  OO  SSSSSS    \n");
        GlobalRenderer->Print("                 OOOOOO  SSSSSS    \n");
    }
    else
    {
        GlobalRenderer->Print("Unknown command: \"");
        GlobalRenderer->Print(input);
        GlobalRenderer->Print("\"\n");
    }
}


Shell *newShell;