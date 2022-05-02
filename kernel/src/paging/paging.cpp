#include "paging.h"

void PageDirectoryEntry::SetFlag(PT_Flag flag, bool enabled){
    uint64_t bitSelector = (uint64_t)1 << flag;
    Value &= ~bitSelector;
    if (enabled){
        Value |= bitSelector;
    }
}

bool PageDirectoryEntry::GetFlag(PT_Flag flag){
    uint64_t bitSelector = (uint64_t)1 << flag;
    return Value & bitSelector > 0 ? true : false;
}

uint64_t PageDirectoryEntry::GetAddress(){
    return (Value & 0x000ffffffffff000) >> 12;
}

void PageDirectoryEntry::SetAddress(uint64_t address){
    address &= 0x000000ffffffffff;
    Value &= 0xfff0000000000fff;
    Value |= (address << 12);
}

uint64_t freeMemory;
uint64_t reservedMemory;
uint64_t usedMemory;
bool Initialized = false;
PageFrameAllocator GlobalAllocator;

void PageFrameAllocator::ReadEFIMemoryMap(EFI_MEMORY_DESCRIPTOR* mMap, size_t mMapSize, size_t mMapDescSize){
    if (Initialized) return;

    Initialized = true;

    uint64_t mMapEntries = mMapSize / mMapDescSize;

    void* largestFreeMemSeg = NULL;
    size_t largestFreeMemSegSize = 0;

    for (int i = 0; i < mMapEntries; i++){
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)mMap + (i * mMapDescSize));
        if (desc->type == 7){ // type = EfiConventionalMemory
            if (desc->numPages * 4096 > largestFreeMemSegSize)
            {
                largestFreeMemSeg = desc->physAddr;
                largestFreeMemSegSize = desc->numPages * 4096;
            }
        }
    }

    uint64_t memorySize = GetMemorySize(mMap, mMapEntries, mMapDescSize);
    freeMemory = memorySize;
    uint64_t bitmapSize = memorySize / 4096 / 8 + 1;

    InitBitmap(bitmapSize, largestFreeMemSeg);

    ReservePages(0, memorySize / 4096 + 1);
    for (int i = 0; i < mMapEntries; i++){
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)mMap + (i * mMapDescSize));
        if (desc->type == 7){ // efiConventionalMemory
            UnreservePages(desc->physAddr, desc->numPages);
        }
    }
    ReservePages(0, 0x100); // reserve between 0 and 0x100000
    LockPages(PageBitmap.Buffer, PageBitmap.Size / 4096 + 1);
}

void PageFrameAllocator::InitBitmap(size_t bitmapSize, void* bufferAddress){
    PageBitmap.Size = bitmapSize;
    PageBitmap.Buffer = (uint8_t*)bufferAddress;
    for (int i = 0; i < bitmapSize; i++){
        *(uint8_t*)(PageBitmap.Buffer + i) = 0;
    }
}
uint64_t pageBitmapIndex = 0;
void* PageFrameAllocator::RequestPage(){
    for (; pageBitmapIndex < PageBitmap.Size * 8; pageBitmapIndex++){
        if (PageBitmap[pageBitmapIndex] == true) continue;
        LockPage((void*)(pageBitmapIndex * 4096));
        return (void*)(pageBitmapIndex * 4096);
    }

    return NULL; // Page Frame Swap to file
}

void PageFrameAllocator::FreePage(void* address){
    uint64_t index = (uint64_t)address / 4096;
    if (PageBitmap[index] == false) return;
    if (PageBitmap.Set(index, false)){
        freeMemory += 4096;
        usedMemory -= 4096;
        if (pageBitmapIndex > index) pageBitmapIndex = index;
    }
}

void PageFrameAllocator::FreePages(void* address, uint64_t pageCount){
    for (int t = 0; t < pageCount; t++){
        FreePage((void*)((uint64_t)address + (t * 4096)));
    }
}

void PageFrameAllocator::LockPage(void* address){
    uint64_t index = (uint64_t)address / 4096;
    if (PageBitmap[index] == true) return;
    if (PageBitmap.Set(index, true)){
        freeMemory -= 4096;
        usedMemory += 4096;
    }
}

void PageFrameAllocator::LockPages(void* address, uint64_t pageCount){
    for (int t = 0; t < pageCount; t++){
        LockPage((void*)((uint64_t)address + (t * 4096)));
    }
}

void PageFrameAllocator::UnreservePage(void* address){
    uint64_t index = (uint64_t)address / 4096;
    if (PageBitmap[index] == false) return;
    if (PageBitmap.Set(index, false)){
        freeMemory += 4096;
        reservedMemory -= 4096;
        if (pageBitmapIndex > index) pageBitmapIndex = index;
    }
}

void PageFrameAllocator::UnreservePages(void* address, uint64_t pageCount){
    for (int t = 0; t < pageCount; t++){
        UnreservePage((void*)((uint64_t)address + (t * 4096)));
    }
}

void PageFrameAllocator::ReservePage(void* address){
    uint64_t index = (uint64_t)address / 4096;
    if (PageBitmap[index] == true) return;
    if (PageBitmap.Set(index, true)){
        freeMemory -= 4096;
        reservedMemory += 4096;
    }
}

void PageFrameAllocator::ReservePages(void* address, uint64_t pageCount){
    for (int t = 0; t < pageCount; t++){
        ReservePage((void*)((uint64_t)address + (t * 4096)));
    }
}

uint64_t PageFrameAllocator::GetFreeRAM(){
    return freeMemory;
}
uint64_t PageFrameAllocator::GetUsedRAM(){
    return usedMemory;
}
uint64_t PageFrameAllocator::GetReservedRAM(){
    return reservedMemory;
}

PageMapIndexer::PageMapIndexer(uint64_t virtualAddress){
    virtualAddress >>= 12;
    P_i = virtualAddress & 0x1ff;
    virtualAddress >>= 9;
    PT_i = virtualAddress & 0x1ff;
    virtualAddress >>= 9;
    PD_i = virtualAddress & 0x1ff;
    virtualAddress >>= 9;
    PDP_i = virtualAddress & 0x1ff;
}


PageTableManager g_PageTableManager = NULL;

PageTableManager::PageTableManager(PageTable* PML4Address){
    this->PML4 = PML4Address;
}

void PageTableManager::MapMemory(void* virtualMemory, void* physicalMemory){
    PageMapIndexer indexer = PageMapIndexer((uint64_t)virtualMemory);
    PageDirectoryEntry PDE;

    PDE = PML4->entries[indexer.PDP_i];
    PageTable* PDP;
    if (!PDE.GetFlag(PT_Flag::Present)){
        PDP = (PageTable*)GlobalAllocator.RequestPage();
        memset(PDP, 0, 0x1000);
        PDE.SetAddress((uint64_t)PDP >> 12);
        PDE.SetFlag(PT_Flag::Present, true);
        PDE.SetFlag(PT_Flag::ReadWrite, true);
        PML4->entries[indexer.PDP_i] = PDE;
    }
    else
    {
        PDP = (PageTable*)((uint64_t)PDE.GetAddress() << 12);
    }
    
    
    PDE = PDP->entries[indexer.PD_i];
    PageTable* PD;
    if (!PDE.GetFlag(PT_Flag::Present)){
        PD = (PageTable*)GlobalAllocator.RequestPage();
        memset(PD, 0, 0x1000);
        PDE.SetAddress((uint64_t)PD >> 12);
        PDE.SetFlag(PT_Flag::Present, true);
        PDE.SetFlag(PT_Flag::ReadWrite, true);
        PDP->entries[indexer.PD_i] = PDE;
    }
    else
    {
        PD = (PageTable*)((uint64_t)PDE.GetAddress() << 12);
    }

    PDE = PD->entries[indexer.PT_i];
    PageTable* PT;
    if (!PDE.GetFlag(PT_Flag::Present)){
        PT = (PageTable*)GlobalAllocator.RequestPage();
        memset(PT, 0, 0x1000);
        PDE.SetAddress((uint64_t)PT >> 12);
        PDE.SetFlag(PT_Flag::Present, true);
        PDE.SetFlag(PT_Flag::ReadWrite, true);
        PD->entries[indexer.PT_i] = PDE;
    }
    else
    {
        PT = (PageTable*)((uint64_t)PDE.GetAddress() << 12);
    }

    PDE = PT->entries[indexer.P_i];
    PDE.SetAddress((uint64_t)physicalMemory >> 12);
    PDE.SetFlag(PT_Flag::Present, true);
    PDE.SetFlag(PT_Flag::ReadWrite, true);
    PT->entries[indexer.P_i] = PDE;
}