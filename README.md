# dsoquad-BIOS

This is a port of SYS ( AKA The BIOS) to gcc.


## Current status

Based on SYS 1.50.  It seems to work with the official APP1 although `USB_Init` does not work yet.


## Files and folders

folder    | notes
----------|-------------------------------------------------------------------
`stm/`    | `core_cm3` and the standard peripheral library for STM32F10x parts
`USBLib/` | A USB device library, aptly named
`src/`    | The BIOS


## Credits

This project would not have been possible without the support and encouragement of jpa.
