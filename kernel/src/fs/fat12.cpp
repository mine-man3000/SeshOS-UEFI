#include "fat12.h"

AHCI::Port newPort;

void FillBPB()
{
    GlobalRenderer->Print("Function Called");

    newPort.Configure();

    GlobalRenderer->Print("Configured");

    newPort.buffer = (uint8_t *)GlobalAllocator.RequestPage();
    
    GlobalRenderer->Print("Page Requested");
    
    memset(newPort.buffer, 0, 0x1000);

    GlobalRenderer->Print("Memory Set");

    newPort.Read(0, 4, newPort.buffer);
    for (int t = 0; t < 1024; t++){
        GlobalRenderer->PutChar(newPort.buffer[t]);
    }    
}