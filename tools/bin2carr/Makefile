.POSIX:
.SUFFIXES:

# Source code location and files to watch for changes.
SRC_DIR        := src
SRC_MAIN       := $(SRC_DIR)/main.c
WATCH_SRC      := $(wildcard $(SRC_DIR)/*.c)
WATCH_SRC      += $(wildcard $(SRC_DIR)/*.h)

# Output library names and executables.
BIN_NAME       := bin2carr
BUILD_DIR      := build
BIN            := $(BUILD_DIR)/$(BIN_NAME)

# Compiler and linker configuration.
CC             := gcc
CFLAGS         := -Wall -Wextra -pedantic -std=c99 -DBIN_NAME=\"$(BIN_NAME)\"
LDFLAGS        := -lm
LDLIBS         :=
RELEASE_CFLAGS := -DNDEBUG -O2
DEBUG_CFLAGS   := -DDEBUG -g

.PHONY: static clean run

# Setup debug/release builds.
#     make clean && make <target> DEBUG=0
#     make clean && make <target> DEBUG=1
DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CFLAGS += $(DEBUG_CFLAGS)
else
    CFLAGS += $(RELEASE_CFLAGS)
endif

static: $(BUILD_DIR) $(BIN)

$(BIN): $(SRC_MAIN) $(WATCH_SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(BIN) $(SRC_MAIN) $(LDLIBS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run: $(BIN)
	exec $(BIN)

clean:
	rm -r $(BUILD_DIR)
