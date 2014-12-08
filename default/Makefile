###############################################################################
# Makefile for the project TermProject
###############################################################################

## General Flags
PROJECT = TermProject
MCU = atmega128
TARGET = TermProject.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99     -DF_CPU=14745600UL -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=TermProject.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects that must be built in order to link
OBJECTS = TermProject.o TextLCD.o TextLCD_Buffer.o TOUR.o OLED.o TIMER3.o imagesData.o imageData2.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) TermProject.hex TermProject.eep TermProject.lss size

## Compile
TermProject.o: ../TermProject.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

TextLCD.o: ../TextLCD.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

TextLCD_Buffer.o: ../TextLCD_Buffer.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

TOUR.o: ../TOUR.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

OLED.o: ../OLED.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

TIMER3.o: ../TIMER3.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

imagesData.o: ../imagesData.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

imageData2.o: ../imageData2.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) TermProject.elf dep/* TermProject.hex TermProject.eep TermProject.lss TermProject.map


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

