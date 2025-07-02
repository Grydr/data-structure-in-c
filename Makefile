BUILD_DIR := build
SRC_DIR := src
BIN_DIR := bin

CC := gcc
CFLAGS := -Wall -Wextra -Wpedantic
OPTIMIZATION := -O2

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJS_FILES := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))
EXE_FILES := $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%,$(SRC_FILES))

$(EXE_FILES): $(OBJS_FILES) | dir
	$(CC) $(CFLAGS) $(OPTIMIZATION) $^ -o $@ 

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | dir 
	$(CC) $(CFLAGS) $(OPTIMIZATION) -c $< -o $@ 

dir:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)

clean:
	rm -rf build

.PHONY:
	dir clean