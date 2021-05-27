ENTRY(start)

/*mmio        = 0xfffffffff8000000;
fb          = 0xfffffffffc000000;
bootboot    = 0xffffffffffe00000;
environment = 0xffffffffffe01000;
PHDRS
{
    boot PT_LOAD; 
}
    */

SECTIONS
{
    . = 1M;

    .boot : 
    {
        KEEP(*(.multiboot_header))
    }

    .text :
    {
        *(.text)
    }
}

