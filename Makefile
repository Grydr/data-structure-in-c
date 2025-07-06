SRC_DIR := src
BIN_DIR := bin

CC := gcc
CFLAGS := -Wall -Wextra -Wpedantic
OPTIMIZATION := -O2

DEBUG ?= 0

ifeq ($(DEBUG), 1)
CFLAGS += -g
endif

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
EXE_FILES := $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%,$(SRC_FILES))

all: $(EXE_FILES)

$(BIN_DIR)/%: $(SRC_DIR)/%.c | dir
	$(CC) $(CFLAGS) $(OPTIMIZATION) $< -o $@

dir:
	@mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR)

.PHONY:
	dir clean