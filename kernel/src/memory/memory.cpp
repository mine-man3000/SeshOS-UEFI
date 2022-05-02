#include "memory.h"

const char *EFI_MEMORY_TYPE_STRINGS[]{

    "EfiReservedMemoryType",
    "EfiLoaderCode",
    "EfiLoaderData",
    "EfiBootServicesCode",
    "EfiBootServicesData",
    "EfiRuntimeServicesCode",
    "EfiRuntimeServicesData",
    "EfiConventionalMemory",
    "EfiUnusableMemory",
    "EfiACPIReclaimMemory",
    "EfiACPIMemoryNVS",
    "EfiMemoryMappedIO",
    "EfiMemoryMappedIOPortSpace",
    "EfiPalCode",
};

uint64_t GetMemorySize(EFI_MEMORY_DESCRIPTOR *mMap, uint64_t mMapEntries, uint64_t mMapDescSize)
{

    static uint64_t memorySizeBytes = 0;
    if (memorySizeBytes > 0)
        return memorySizeBytes;

    for (int i = 0; i < mMapEntries; i++)
    {
        EFI_MEMORY_DESCRIPTOR *desc = (EFI_MEMORY_DESCRIPTOR *)((uint64_t)mMap + (i * mMapDescSize));
        memorySizeBytes += desc->numPages * 4096;
    }

    return memorySizeBytes;
}

void memset(void *start, uint8_t value, uint64_t num)
{
    for (uint64_t i = 0; i < num; i++)
    {
        *(uint8_t *)((uint64_t)start + i) = value;
    }
}

bool Bitmap::operator[](uint64_t index)
{
    return Get(index);
}

bool Bitmap::Get(uint64_t index)
{
    if (index > Size * 8)
        return false;
    uint64_t byteIndex = index / 8;
    uint8_t bitIndex = index % 8;
    uint8_t bitIndexer = 0b10000000 >> bitIndex;
    if ((Buffer[byteIndex] & bitIndexer) > 0)
    {
        return true;
    }
    return false;
}

bool Bitmap::Set(uint64_t index, bool value)
{
    if (index > Size * 8)
        return false;
    uint64_t byteIndex = index / 8;
    uint8_t bitIndex = index % 8;
    uint8_t bitIndexer = 0b10000000 >> bitIndex;
    Buffer[byteIndex] &= ~bitIndexer;
    if (value)
    {
        Buffer[byteIndex] |= bitIndexer;
    }
    return true;
}