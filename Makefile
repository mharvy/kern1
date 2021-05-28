GCC_FLAGS = -I src/intf -ffreestanding -mcmodel=large -mno-red-zone -mno-sse -mno-sse2
LD_FLAGS = -ffreestanding -nostdlib -lgcc -n
GCC_PATH = ../cross-compiler/opt/cross/bin/x86_64-elf-g++
LD_PATH = ../cross-compiler/opt/cross/bin/x86_64-elf-g++
x86_64_ISO = ./dist/x86_64/kernel.iso
x86_64_BIN = ./dist/x86_64/kernel.bin

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

# *** x86_64 ***
x86_64_cpp_src_files := $(shell find src/impl/x86_64 -name *.cpp)
x86_64_cpp_obj_files := $(patsubst src/impl/x86_64/%.cpp, build/x86_64/%.o, $(x86_64_cpp_src_files))

x86_64_asm_src_files := $(shell find src/impl/x86_64 -name *.asm)
x86_64_asm_obj_files := $(patsubst src/impl/x86_64/%.asm, build/x86_64/%.o, $(x86_64_asm_src_files))

x86_64_obj_files := $(x86_64_cpp_obj_files) $(x86_64_asm_obj_files)

$(x86_64_cpp_obj_files): build/x86_64/%.o : src/impl/x86_64/%.cpp
	mkdir -p $(dir $@) && \
	$(GCC_PATH) $(GCC_FLAGS) -c $(patsubst build/x86_64/%.o, src/impl/x86_64/%.cpp, $@) -o $@

$(x86_64_asm_obj_files): build/x86_64/%.o : src/impl/x86_64/%.asm
	mkdir -p $(dir $@) && \
	nasm -f elf64 $(patsubst build/x86_64/%.o, src/impl/x86_64/%.asm, $@) -o $@

$(x86_64_BIN): $(kernel_obj_files) $(driver_obj_files) $(x86_64_obj_files)
	mkdir -p dist/x86_64 && \
	$(LD_PATH) $(LD_FLAGS) -o dist/x86_64/kernel.bin -T targets/x86_64/link.ld $(kernel_obj_files) $(driver_obj_files) $(x86_64_obj_files) && \
	cp $(x86_64_BIN) targets/x86_64/iso/boot/kernel.bin 

$(x86_64_ISO): $(x86_64_BIN)
	grub-mkrescue /usr/lib/grub/i386-pc -o $(x86_64_ISO) targets/x86_64/iso 

.PHONY: build-x86_64
build-x86_64: $(x86_64_ISO)

.PHONY: run-x86_64
run-x86_64: $(x86_64_ISO)
	qemu-system-x86_64 -cdrom $(x86_64_ISO)

.PHONY: clean
clean:
	rm -r build dist