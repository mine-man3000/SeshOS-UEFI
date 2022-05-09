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
   TwoStrings twoStrings = strsplit(input, ' ');
    if (strcmp(input, "ver"))
    {
        GlobalRenderer->Print("SeshOS version 0.2.0\n");
    }
    else if (strcmp(input, "help"))
    {
        GlobalRenderer->Print("List of available commands:\n");
        GlobalRenderer->Print("    ver:         shows the version of SeshOS\n");
        GlobalRenderer->Print("    help:        shows this menu\n");
        GlobalRenderer->Print("    clear:       clears the screen\n");
        GlobalRenderer->Print("    volinfo:     shows information about the rootfs disk\n");
        GlobalRenderer->Print("    ls:          shows the files in the selected directory (currently only rootdir)\n");
        GlobalRenderer->Print("    neofetch:    only a Linux user would understand\n");
        GlobalRenderer->Print("    mem:         Shows you the ammount of RAM the system is using\n");
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
        uint64_t freeMem = GlobalAllocator.GetFreeRAM() / 1024 / 1024;
        uint64_t UsedMem = GlobalAllocator.GetUsedRAM() / 1024 / 1024;
        uint64_t ResvMem = GlobalAllocator.GetReservedRAM() / 1024 / 1024;

        uint64_t totMem = freeMem + UsedMem + ResvMem;
        uint64_t width  = GlobalRenderer->TargetFramebuffer->Width;
        uint64_t height = GlobalRenderer->TargetFramebuffer->Height;

        GlobalRenderer->Print("SSSSSS   EEEEEE  SSSSSS  HH  HH    root@SeshOS\n");
        GlobalRenderer->Print("SSSSSS   EEEEEE  SSSSSS  HH  HH    -----------\n");
        GlobalRenderer->Print("SSS      EE      SSS     HH  HH    OS: SeshOS 0.2.0\n");
        GlobalRenderer->Print("SSS      EE      SSS     HH  HH    Kernel: 0.2.0\n");
        GlobalRenderer->Print("SSSSSS   EEEEEE  SSSSSS  HHHHHH    Shell: SESH (SEsh SHell)\n");
        GlobalRenderer->Print("SSSSSS   EEEEEE  SSSSSS  HHHHHH    Resolution: "); GlobalRenderer->Print(to_string((uint64_t)width)); GlobalRenderer->Print("x"); GlobalRenderer->Print(to_string((uint64_t)height)); GlobalRenderer->Print("\n");
        GlobalRenderer->Print("   SSS   EE         SSS  HH  HH    Memory: "); GlobalRenderer->Print(to_string((uint64_t)UsedMem + ResvMem)); GlobalRenderer->Print("MB / "); GlobalRenderer->Print(to_string((uint64_t)totMem)); GlobalRenderer->Print("MB\n");
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
    else if (strcmp(input, "mem"))
    {
        uint64_t freeMem = GlobalAllocator.GetFreeRAM() / 1024 / 1024;
        uint64_t UsedMem = GlobalAllocator.GetUsedRAM() / 1024 / 1024;
        uint64_t ResvMem = GlobalAllocator.GetReservedRAM() / 1024 / 1024;

        uint64_t totMem = freeMem + UsedMem + ResvMem;

        GlobalRenderer->Print("Free RAM: ");
        GlobalRenderer->Print(to_string((uint64_t)freeMem));
        GlobalRenderer->Print(" MB\nUsed RAM: ");
        GlobalRenderer->Print(to_string((uint64_t)UsedMem));
        GlobalRenderer->Print(" MB\nReserved RAM: ");
        GlobalRenderer->Print(to_string((uint64_t)ResvMem));
        GlobalRenderer->Print(" MB\nTotal RAM: ");
        GlobalRenderer->Print(to_string((uint64_t)totMem));
        GlobalRenderer->Print(" MB\n");
    }
    else if (strcmp(twoStrings.a, "cat"))
    {
        if(strlen(twoStrings.b) == 0)
        {
            GlobalRenderer->Print("ERROR: NO INPUT FILE SPECIFIED\n");
        }
        else
        {
            ConvertFileNames();
        }
    }
    else if (strcmp(input, "")){}
    else
    {
        GlobalRenderer->Print("Unknown command: \"");
        GlobalRenderer->Print(input);
        GlobalRenderer->Print("\"\n");
    }
}


Shell *newShell;

qemu-system-x86_64 -drive file=kernel/bin/CustomOS.img -m 1G -drive if=pflash,format=raw,unit=0,file="OVMF_CODE.fd",readonly=on -drive if=pflash,format=raw,unit=1,file="OVMF_VARS.fd" -net none