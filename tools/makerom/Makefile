.POSIX:
.SUFFIXES:
.PHONY: main run clean

# Source code location and files to watch for changes.
SRC_DIR     := src
BUILD_DIR   := build
SRC_MAIN    := $(SRC_DIR)/main.c
SRC_OBJ     :=
OBJECTS     := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_OBJ))
WATCH_SRC   := $(shell find $(SRC_DIR) -name "*.c" -or -name "*.s" -or -name "*.h")
INC_DIRS    := $(shell find $(SRC_DIR) -type d)
INC_FLAGS   := $(addprefix -I,$(INC_DIRS))

# Output names and executables.
TARGET := makerom
BIN    := $(BUILD_DIR)/$(TARGET)

# Main compilation tool paths.
CC       := gcc
LD       := ld
AS       := as
OBJDUMP  := objdump

# Compiler and linker configuration.
CFLAGS         := -Wall -Wextra -pedantic
CFLAGS         += -DBIN_NAME=\"$(TARGET)\"
CFLAGS         += $(INC_FLAGS)
LDFLAGS        :=
LDLIBS         :=
RELEASE_CFLAGS := -O2 -DNDEBUG
DEBUG_CFLAGS   := -O0 -DDEBUG -g

# Setup debug/release builds.
DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CFLAGS += $(DEBUG_CFLAGS)
else
    CFLAGS += $(RELEASE_CFLAGS)
endif

main: $(BIN)

# Compile and link everything in one go.
$(BIN): $(SRC_MAIN) $(OBJECTS) $(WATCH_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(BIN) $(SRC_MAIN) $(OBJECTS) $(LDLIBS)

# Run the program
run: $(BIN)
	./$(BIN)

# Remove build directory.
clean:
	rm -rf $(BUILD_DIR)

# Create the build directory.
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Inference rules for C files.
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@
