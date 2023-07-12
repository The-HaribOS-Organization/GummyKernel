# User defined variables
GNU-EFI_LOCALIZATION = ../gnu-efi

# Compilers & Linker
AS = nasm
ASFLAGS = -f elf64

CXX = clang
CXXFLAGS = -Wextra -Wall -target x86_64-unknown-windows -ffreestanding -fshort-wchar -mno-red-zone
INCLUDE_HEADERS = -I include -I $(GNU-EFI_LOCALIZATION)/inc/ -I $(GNU-EFI_LOCALIZATION)/inc/x86_64 -I $(GNU-EFI_LOCALIZATION)/inc/protocol

LD = ld
LDFILE = kernel.ld 

# Files
C_SRCS := $(shell find src -name "*.c")

OBJ_DIR := obj
C_OBJS := $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(C_SRCS))

# Need to fill up when a new asm file is added -> new line in asmFiles
ASM_OBJS := obj/apic/msr.o \
			obj/hardwareCommunication/io.o


BUILD_DIR = bin

# Linker
LDFLAGS = -T $(LDFILE) -static -Bsymbolic -nostdlib

all: cFiles asmFiles build

cFiles: $(C_OBJS)

$(OBJ_DIR)/%.o: src/%.c
	@ mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE_HEADERS) -c $< -o $@

asmFiles:
	$(AS) $(ASFLAGS) src/apic/msr.asm -o obj/apic/msr.o
	$(AS) $(ASFLAGS) src/hardwareCommunication/io.asm -o obj/hardwareCommunication/io.o

build:
	@ mkdir -p $(BUILD_DIR)
	$(LD) $(LDFLAGS) -o $(BUILD_DIR)/kernel.elf $(C_OBJS) $(ASM_OBJS)

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BUILD_DIR)

.PHONY: all cFiles asmFiles build clean
