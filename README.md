What I want to do: 
- [X] Booting 
- [ ] Basic GUI 
- [X] Mouse Detection 
- [X] Buttons
- [X] Keyboard Driver
- [ ] Window system
- [ ] Read From FAT32
- [ ] Terminal
- [ ] Port *Something*

What I need to do:
- [X] Load an IDT so that exceptions and interrupts can be handled.
- [X] Write a physical memory allocator, a good starting point is a bitmap allocator.
- [X] Write a virtual memory manager that can map, remap and unmap pages.
- [X] Begin parsing ACPI tables, the most important one is the MADT since it contains information about the APIC.
- [ ] Start up the other CPUs. stivale2 provides a facility to make this less painful.
- [ ] Set up an interrupt controller such as the APIC.
- [X] Configure a timer such as the Local APIC timer, the PIT, or the HPET.
- [ ] Implement a scheduler to schedule threads in order make multitasking possible.
- [ ] Design a virtual file system (VFS) and implement it. The traditional UNIX VFS works  when porting software
- [ ] Implement a simple virtual file system like a memory-only tmpf
- [ ] Decide how to abstract devices. UNIX likes usually go for a /dev virtual filesystem 
- [ ] Get a userland going by loading executables from your VFS and running them in ring 3. Set up a way to run sys calls.
- [X] Write a PCI driver.
- [X] Add support for a storage medium, the easiest and most common ones are AHCI and NVMe.