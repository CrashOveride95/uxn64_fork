.POSIX:
.SUFFIXES:
.PHONY: main run clean

# Paths for SDK.
SDK_BASE     := /opt/n64sdk
SDK_BIN      := $(SDK_BASE)/bin
LIBULTRA_DIR := $(SDK_BASE)/libultra
LIBULTRA_INC := $(LIBULTRA_DIR)/usr/include
LIBULTRA     := $(LIBULTRA_DIR)/usr/lib/libgultra.a
EMULATOR     := ares

# Source code location and files to watch for changes.
SRC_DIR     := src
BUILD_DIR   := build
SRC_MAIN    := $(SRC_DIR)/main.c $(SRC_DIR)/entry.s
SRC_LN      := $(SRC_DIR)/linker.ld
SRC_OBJ     :=
UXN_ROM_C   := $(BUILD_DIR)/rom.c
UXN_ROM     := $(SRC_DIR)/uxn/bin/screen.rom
OBJECTS     := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_OBJ))
WATCH_SRC   := $(shell find $(SRC_DIR) \
			   -name "*.c" -or \
			   -name "*.s" -or \
			   -name "*.h" -or \
			   -name "**.ld")
INC_DIRS    := $(shell find $(SRC_DIR) -type d)
INC_DIRS    += $(BUILD_DIR)
INC_DIRS    += $(LIBULTRA_INC)
INC_FLAGS   := $(addprefix -I,$(INC_DIRS))

# Output names and executables.
TARGET := uxn64
ELF    := $(BUILD_DIR)/$(TARGET).elf
BIN    := $(BUILD_DIR)/$(TARGET).bin
ROM    := $(BUILD_DIR)/$(TARGET).n64

# Target tools.
TOOLS_BIN2CARR := tools/bin2carr/build/bin2carr
TOOLS_MAKEROM  := tools/makerom/build/makerom

# Main compilation tool paths.
CC       := $(SDK_BIN)/mips32-elf-gcc
LD       := $(SDK_BIN)/mips32-elf-ld
AS       := $(SDK_BIN)/mips32-elf-as
OBJDUMP  := $(SDK_BIN)/mips32-elf-objdump
OBJCOPY  := $(SDK_BIN)/mips32-elf-objcopy

# Compiler and linker configuration.
CFLAGS         := -Wall -Wextra -pedantic
CFLAGS         += -mabi=32 -mfix4300
CFLAGS         += -ffreestanding -G 0
CFLAGS         += $(INC_FLAGS)
CFLAGS         += -DF3DEX_GBI_2
LDFLAGS        := -nostdlib
LDLIBS         := $(LIBULTRA) $(SDK_BASE)/lib/gcc/mips32-elf/13.0.0/libgcc.a
RELEASE_CFLAGS := -O2 -DNDEBUG -D_FINALROM
DEBUG_CFLAGS   := -O0 -DDEBUG -D_FINALROM

# Setup debug/release builds.
DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CFLAGS += $(DEBUG_CFLAGS)
else
    CFLAGS += $(RELEASE_CFLAGS)
endif

main: $(ROM)

# Compile the elf file.
$(ELF): $(SRC_MAIN) $(UXN_ROM_C) $(WATCH_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(ELF) -T $(SRC_LN) $(SRC_MAIN) $(LDLIBS)

# Create the valid .n64 rom from the elf file.
$(BIN): $(ELF) $(WATCH_SRC) | $(BUILD_DIR)
	$(OBJCOPY) -O binary $(ELF) $(BIN)

$(ROM): $(BIN) $(TOOLS_MAKEROM) $(WATCH_SRC) | $(BUILD_DIR)
	$(TOOLS_MAKEROM) $(BIN) -o $(ROM)

# Build the uxn rom's C file.
$(UXN_ROM_C): $(TOOLS_BIN2CARR) | $(BUILD_DIR)
	./$(TOOLS_BIN2CARR) -n uxn_rom -e u8 -o $(UXN_ROM_C) $(UXN_ROM)

# Build the tools.
$(TOOLS_BIN2CARR):
	make -C tools/bin2carr

$(TOOLS_MAKEROM):
	make -C tools/makerom

# Test the output .n64 in an emulator.
run: $(ROM)
	$(EMULATOR) $(ROM)

# Remove build directory.
clean:
	rm -rf $(BUILD_DIR)

# Create the build directory.
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Inference rules for C files.
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

# Inference rules for assembly files.
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.s | $(BUILD_DIR)
	$(AS) $(AFLAGS) -o $@ -c $<
