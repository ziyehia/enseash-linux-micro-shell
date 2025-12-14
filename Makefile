# Compiler
CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude

# Directories
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# Source files
SRC = $(wildcard $(SRC_DIR)/*.c)

# Object files (build/*.o)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))

# Executable name
TARGET = $(BIN_DIR)/my_program

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

# Compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create build/ and bin/ directories if they don't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean everything
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Optional: format code
indent:
	indent -linux -i4 -nut -ts2 $(SRC_DIR)/*.c

.PHONY: all clean indent
