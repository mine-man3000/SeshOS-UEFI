#pragma once

#include <stdint.h>
#include <stddef.h>

struct EFI_MEMORY_DESCRIPTOR
{
    uint32_t type;
    void *physAddr;
    void *virtAddr;
    uint64_t numPages;
    uint64_t attribs;
};

extern const char *EFI_MEMORY_TYPE_STRINGS[];

uint64_t GetMemorySize(EFI_MEMORY_DESCRIPTOR *mMap, uint64_t mMapEntries, uint64_t mMapDescSize);
void memset(void *start, uint8_t value, uint64_t num);

class Bitmap
{
    public:
        size_t Size;
        uint8_t *Buffer;
        bool operator[](uint64_t index);
        bool Set(uint64_t index, bool value);
        bool Get(uint64_t index);
};