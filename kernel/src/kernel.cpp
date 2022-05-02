#include "kernelUtil.h"
#include "memory/heap.h"
#include "scheduling/pit.h"

extern "C" void _start(BootInfo *bootInfo)
{

    KernelInfo kernelInfo = InitializeKernel(bootInfo);

    GlobalRenderer->Print("\n\nWelcome to SeshOS!\n");

    GlobalRenderer->Color = 0x00ff0000;
    GlobalRenderer->Print("root@SeshOS");
    GlobalRenderer->Color = 0x000000ff;
    GlobalRenderer->Print(" /");
    GlobalRenderer->Color = 0xffffffff;
    GlobalRenderer->Print(" # ");

    while (true)
    {
        asm("hlt");
    }
}
