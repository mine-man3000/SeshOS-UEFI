#include "kernelUtil.h"
#include "memory/heap.h"
#include "scheduling/pit.h"
#include "shell.h"
#include "fs/fat12.h"

extern "C" void _start(BootInfo *bootInfo)
{

    KernelInfo kernelInfo = InitializeKernel(bootInfo);

    initFAT(bootInfo);

    GlobalRenderer->Print("\n\nWelcome to SeshOS!\n");

    //ConvertFileNames();

    for (int i = 0; i < 10; i++)
    {
        
    }
    

    newShell->PrintPrompt();

    while (true)
    {
        asm("hlt");
    }
}