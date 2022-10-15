.POSIX:
.SUFFIXES:

# Paths for SDK.
SDK_BASE     := /opt/n64sdk
SDK_BIN      := $(SDK_BASE)/bin
LIBULTRA_DIR := $(SDK_BASE)/libultra
LIBULTRA_INC := $(LIBULTRA_DIR)/usr/include
LIBULTRA     := $(LIBULTRA_DIR)/usr/lib/libgultra.a

# Source code location and files to watch for changes.
SRC_DIR     := src
BUILD_DIR   := build
SRC_MAIN    := $(SRC_DIR)/onetri.c \
			   $(SRC_DIR)/dram_stack.c \
			   $(SRC_DIR)/rdp_output.c
SRC_OBJ     := $(SRC_DIR)/static.c \
			   $(SRC_DIR)/cfb.c \
			   $(SRC_DIR)/rsp_cfb.c
OBJECTS     := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_OBJ))

WATCH_SRC   := $(shell find $(SRC_DIR) -name "*.c" -or -name "*.s" -or -name "*.h")
INC_DIRS    := $(shell find $(SRC_DIR) -type d)
INC_DIRS    += $(LIBULTRA_INC)
INC_FLAGS   := $(addprefix -I,$(INC_DIRS))

datafiles = $(SRC_DIR)/static.c $(SRC_DIR)/cfb.c $(SRC_DIR)/rsp_cfb.c
dataobjects = $(datafiles:.c=.o)

# Output names and executables.
TARGET := blank
ELF    := $(BUILD_DIR)/$(TARGET).elf
BIN    := $(BUILD_DIR)/$(TARGET).n64

# Main compilation tool paths.
CC       := $(SDK_BIN)/mips32-elf-gcc
LD       := $(SDK_BIN)/mips32-elf-ld
AS       := $(SDK_BIN)/mips32-elf-as
OBJDUMP  := $(SDK_BIN)/mips32-elf-objdump
# TODO: Replace with internal tools to avoid dependencies.
SPICY    := $(SDK_BIN)/spicy
MAKEMASK := $(SDK_BIN)/makemask

# Compiler and linker configuration.
CFLAGS         := -Wall -Wextra -pedantic
CFLAGS         += -mabi=32 -mfix4300
CFLAGS         += -ffreestanding -G 0
CFLAGS         += $(INC_FLAGS)
CFLAGS         += -DF3DEX_GBI_2 -nostdlib -r
LDFLAGS        := -nostdlib -r
LDLIBS         := $(LIBULTRA) $(SDK_BASE)/lib/gcc/mips32-elf/13.0.0/libgcc.a
RELEASE_CFLAGS := -O2 -DNDEBUG -D_FINALROM
DEBUG_CFLAGS   := -O0 -DDEBUG -D_FINALROM

# Setup debug/release builds.
#     make clean && make <target> DEBUG=0
#     make clean && make <target> DEBUG=1
DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CFLAGS += $(DEBUG_CFLAGS)
else
    CFLAGS += $(RELEASE_CFLAGS)
endif

main: $(BIN)

$(ELF): $(SRC_MAIN) $(WATCH_SRC)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(ELF) $(SRC_MAIN) $(LDLIBS)

$(BIN): $(ELF) $(OBJECTS) $(WATCH_SRC)
	$(SPICY) -r $@ $(SRC_DIR)/spec \
		--as_command="$(SDK_BIN)/mips32-elf-as" \
		--cpp_command="$(SDK_BIN)/mips32-elf-gcc" \
		--ld_command="$(SDK_BIN)/mips32-elf-ld" \
		--objcopy_command="$(SDK_BIN)/mips32-elf-objcopy"
	$(MAKEMASK) $(BIN)

# Test the output .n64 in an emulator.
run: $(BIN)
	# TODO: Test roms with MAME or cen64 instead of mupen64 for better accuracy.
	mupen64plus $(BIN)

# Remove build directory.
clean:
	rm -rf $(BUILD_DIR)

.PHONY: main run clean

# Inference rules.
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@
