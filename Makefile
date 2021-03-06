ARCH = x86_64
GCC_FLAGS = -I ./src/intf -I ./src/impl/include \
	-I ./src/impl/$(ARCH)/include -ffreestanding \
    -mcmodel=large -mno-red-zone -mno-sse -mno-sse2 \
	-g -fno-threadsafe-statics -Werror
LD_FLAGS = -ffreestanding -nostdlib -lgcc -n -g
GCC_PATH = ../cross/bin/$(ARCH)-elf-g++
LD_PATH = ../cross/bin/$(ARCH)-elf-g++
x86_64_ISO = ./dist/x86_64/kernel.iso
x86_64_BIN = ./dist/x86_64/kernel.bin
x86_64_ELF = ./dist/x86_64/kernel.elf

# *** KERNEL ***
kernel_src_files := $(shell find src/impl/kernel -name *.cpp)
kernel_obj_files := $(patsubst src/impl/kernel/%.cpp, build/kernel/%.o, $(kernel_src_files))

$(kernel_obj_files): build/kernel/%.o : src/impl/kernel/%.cpp
	mkdir -p $(dir $@) && \
	$(GCC_PATH) $(GCC_FLAGS) -c $(patsubst build/kernel/%.o, src/impl/kernel/%.cpp, $@) -o $@

# *** DRIVERS ***
driver_src_files := $(shell find src/impl/drivers -name *.cpp)
driver_obj_files := $(patsubst src/impl/drivers/%.cpp, build/drivers/%.o, $(driver_src_files))

$(driver_obj_files): build/drivers/%.o : src/impl/drivers/%.cpp
	mkdir -p $(dir $@) && \
	$(GCC_PATH) $(GCC_FLAGS) -c $(patsubst build/drivers/%.o, src/impl/drivers/%.cpp, $@) -o $@

# *** INCLUDES ***
include_src_files := $(shell find src/impl/include -name *.cpp)
include_obj_files := $(patsubst src/impl/include/%.cpp, build/include/%.o, $(include_src_files))

$(include_obj_files): build/include/%.o : src/impl/include/%.cpp
	mkdir -p $(dir $@) && \
	$(GCC_PATH) $(GCC_FLAGS) -c $(patsubst build/include/%.o, src/impl/include/%.cpp, $@) -o $@

# *** x86_64 ***
x86_64_GCC_FLAGS = -I src/impl/x86_64/include

x86_64_cpp_src_files := $(shell find src/impl/x86_64 -name *.cpp)
x86_64_cpp_obj_files := $(patsubst src/impl/x86_64/%.cpp, build/x86_64/%.o, $(x86_64_cpp_src_files))

x86_64_asm_src_files := $(shell find src/impl/x86_64 -name *.asm)
x86_64_asm_obj_files := $(patsubst src/impl/x86_64/%.asm, build/x86_64/%.o, $(x86_64_asm_src_files))

x86_64_obj_files := $(x86_64_cpp_obj_files) $(x86_64_asm_obj_files)

$(x86_64_cpp_obj_files): build/x86_64/%.o : src/impl/x86_64/%.cpp
	mkdir -p $(dir $@) && \
	$(GCC_PATH) $(x86_64_GCC_FLAGS) $(GCC_FLAGS) -c $(patsubst build/x86_64/%.o, src/impl/x86_64/%.cpp, $@) -o $@

$(x86_64_asm_obj_files): build/x86_64/%.o : src/impl/x86_64/%.asm
	mkdir -p $(dir $@) && \
	nasm -f elf64 $(patsubst build/x86_64/%.o, src/impl/x86_64/%.asm, $@) -o $@

$(x86_64_BIN): $(kernel_obj_files) $(driver_obj_files) $(include_obj_files) $(x86_64_obj_files)
	mkdir -p dist/x86_64 && \
	$(LD_PATH) $(LD_FLAGS) -o dist/x86_64/kernel.bin -T targets/x86_64/link.ld $(kernel_obj_files) $(driver_obj_files) $(include_obj_files) $(x86_64_obj_files) && \
	cp $(x86_64_BIN) targets/x86_64/iso/boot/kernel.bin 

$(x86_64_ELF): $(kernel_obj_files) $(driver_obj_files) $(include_obj_files) $(x86_64_obj_files)
	mkdir -p dist/x86_64 && \
	$(LD_PATH) $(LD_FLAGS) -elf64-x86-64 -o dist/x86_64/kernel.elf -T targets/x86_64/link.ld $(kernel_obj_files) $(driver_obj_files) $(include_obj_files) $(x86_64_obj_files) && \
	cp $(x86_64_ELF) targets/x86_64/iso/boot/kernel.elf 

$(x86_64_ISO): $(x86_64_BIN)
	grub-mkrescue /usr/lib/grub/i386-pc -o $(x86_64_ISO) targets/x86_64/iso 

.PHONY: build
build: $(x86_64_ISO)
	ctags --recurse=yes --exclude=.git --exclude=BUILD src

.PHONY: run
run: $(x86_64_ISO)
	qemu-system-x86_64 -cpu qemu64 -cdrom $(x86_64_ISO) -smp cores=2

.PHONY: debug
debug: $(x86_64_ELF) $(x86_64_ISO)
	qemu-system-x86_64 -s -S -cpu qemu64 -cdrom $(x86_64_ISO) -smp cores=2

.PHONY: clean
clean:
	rm -r dist build
	rm targets/x86_64/iso/boot/kernel.*




