
NAME = BIOS-gcc

PARTS += core_cm3.o
PARTS += misc.o stm32f10x_dma.o stm32f10x_gpio.o stm32f10x_rcc.o stm32f10x_tim.o stm32f10x_adc.o stm32f10x_usart.o stm32f10x_dac.o stm32f10x_flash.o stm32f10x_fsmc.o stm32f10x_spi.o
PARTS += USB_core.o USB_init.o USB_int.o USB_mem.o USB_regs.o
# Left out: Authenticate.o 2FAT12.o
PARTS += ASM.o Config.o FAT12.o LCD.o Ident.o Memory.o \
  USB_bot.o USB_endp.o USB_prop.o USB_scsi.o BIOS.o Ext_Flash.o \
  Function.o Interrupt.o Main.o scsi_data.o USB_desc.o USB_istr.o USB_pwr.o

DELIVERABLES = SYS.HEX

CFLAGS += -Istm -DSTM32F10X_HD -DUSE_STDPERIPH_DRIVER -IUSBLib -Isrc

# Processor type
CFLAGS += -mcpu=cortex-m3 -mthumb -mno-thumb-interwork

# Optimization & debug settings
CFLAGS += -fno-common -Os -std=gnu99 -ffunction-sections

# Compiler warnings
CFLAGS += -Wall -Wno-unused

# Default linker arguments (disables GCC-provided startup.c, creates .map file)
LFLAGS += -nostartfiles -Wl,-Map=$(NAME).map# -Wl,-gc-sections

AFLAGS = -mcpu=cortex-m3

.SILENT:

# Names of the toolchain programs
CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

# Tell make where to find transitional files:
VPATH = stm:USBLib:src

# How to make .HEX files from .elf files:
%.HEX: %.elf
	$(OBJCOPY) -O ihex $< $@

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@

%.elf: %.lds $(PARTS)
	$(CC) $(CFLAGS) -o $@ $(PARTS) ${LFLAGS} ${LIBS} -T $<

# Rebuild all parts if any header or the Makefile changes:
.c.o: *.h Makefile
	$(CC) $(CFLAGS) -c -o $@ $<

.S.o:
	$(CC) $(AFLAGS) -c -o $@ $<

all: $(DELIVERABLES)
	$(SIZE) SYS.elf

clean:
	rm -f $(DELIVERABLES) $(NAME).map $(PARTS)

