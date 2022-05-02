#pragma once

#include <stdint.h>
#include "renderer.h"
#include "cstr.h"
#include "memory/memory.h"
#include "paging/paging.h"
#include "userinput/mouse.h"
#include "acpi.h"
#include "pci.h"

struct BootInfo
{
	Framebuffer *framebuffer;
	PSF1_FONT *psf1_Font;
	EFI_MEMORY_DESCRIPTOR *mMap;
	uint64_t mMapSize;
	uint64_t mMapDescSize;
	ACPI::RSDP2 *rsdp;
};

extern uint64_t _KernelStart;
extern uint64_t _KernelEnd;

struct KernelInfo
{
	PageTableManager *pageTableManager;
};

KernelInfo InitializeKernel(BootInfo *BootInfo);
void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);
void io_wait();