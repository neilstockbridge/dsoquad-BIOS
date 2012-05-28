
# dsoquad-BIOS

This is intended to be a port of SYS ( AKA The BIOS) to gcc.  Currently it compiles ( albeit with warnings) and links and looks about the right size, but if you flash it you will get only a white screen on startup.

folder    | notes
----------|-------------------------------------------------------------------
`stm/`    | `core_cm3` and the standard peripheral library for STM32F10x parts
`USBLib/` | A USB device library, aptly named
`src/`    | The BIOS
