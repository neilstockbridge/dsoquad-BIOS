
MEMORY
{
  rom (rx) : ORIGIN = 0x08004000, LENGTH = 32K
  ram (rwx) : ORIGIN = 0x20003000, LENGTH = 32K /* Total size is 36K, leave 4K for stack */
}

_estack = 0x20000000 + 48K;

SECTIONS
{
  .  = 0x0;          /* From 0x00000000 */

  .text : {
    _vectors = .;
    *(.isr_vectors)  /* Vector table */
    . = 0x200;
    ASM.o
    *(.text*)        /* Program code */
    *(.rodata*)      /* Read only data */
    _etext = .;
    _sidata = _etext;
  } >rom

  .  = 0x20000000;   /* From 0x20000000 */

  .data : {
    _sdata = . ;
    *(.data)         /* Data memory */
    _edata = .;
  } >ram AT > rom

.bss : {
  _sbss = .;
  *(.bss)            /* Zero-filled run time allocate data memory */
  _ebss = .;
  } >ram AT > rom
}

