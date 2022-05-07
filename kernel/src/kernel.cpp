#include "kernelUtil.h"
#include "memory/heap.h"
#include "scheduling/pit.h"
#include "shell.h"
#include "fs/fat12.h"

extern "C" void _start(BootInfo *bootInfo)
{

    KernelInfo kernelInfo = InitializeKernel(bootInfo);

    GlobalRenderer->Print("\n\nWelcome to SeshOS!\n");

    uint64_t freeMem = GlobalAllocator.GetFreeRAM() / 1024 / 1024;
    uint64_t UsedMem = GlobalAllocator.GetUsedRAM() / 1024 / 1024;
    uint64_t ResvMem = GlobalAllocator.GetReservedRAM() / 1024 / 1024;

    uint64_t totMem = freeMem + UsedMem + ResvMem;



    GlobalRenderer->Print("Free RAM: ");
    GlobalRenderer->Print(to_string((uint64_t)freeMem));
    GlobalRenderer->Print(" MB out of ");
    GlobalRenderer->Print(to_string((uint64_t)totMem));
    GlobalRenderer->Print(" MB\n");

    newShell->PrintPrompt();

    while (true)
    {
        asm("hlt");
    }
}