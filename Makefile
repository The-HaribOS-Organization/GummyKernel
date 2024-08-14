GCCPARAMS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Iinclude -fno-stack-protector
GCCLINKING = -ffreestanding -O2 -nostdlib -lgcc
NASMPARAMS = -felf32

SRCS := $(wildcard src/*.c) $(wildcard src/**/*.c) $(wildcard src/*.asm) $(wildcard src/**/*.asm)
OBJ_DIR := obj
OBJS := $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(patsubst src/%.asm, $(OBJ_DIR)/%.o, $(SRCS)))
LINKFILE = linker.ld


gummykernel: $(OBJS) gummybin.bin gummybin.iso

$(OBJ_DIR)/%.o: src/%.c
	@ mkdir -p $(@D)
	i686-elf-gcc $(GCCPARAMS) -c $< -o $@

$(OBJ_DIR)/%.o: src/%.asm
	@ mkdir -p $(@D)
	nasm $(NASMPARAMS) $< -o $@

gummybin.bin: $(OBJFILES) $(LINKFILE)
	i686-elf-gcc -T $(LINKFILE) -o $@ $(OBJS) $(GCCLINKING)

gummybin.iso:
	cp gummybin.bin iso/boot/gummybin.bin
	grub-mkrescue -o gummybin.iso iso

clean:
	rm -rv gummybin.bin
	rm -rv obj/*
	rm -rv gummybin.iso
	rm -rv iso/boot/gummybin.bin

run:
	qemu-system-i386 -cdrom gummybin.iso -M smm=off -d int -audiodev pa,id=snd0 -machine pcspk-audiodev=snd0 -serial pty

.PHONY: gummykernel boot_file gummybin gummyiso clean run run-debug