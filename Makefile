# makefile

# Paths
SRC_DIR = src
BUILD_DIR = build
FLASH_DIR = flash

# Tools
CC = arm-none-eabi-gcc

# Flags

# File names
SRC = $(SRC_DIR)/main.c
OBJ = $(BUILD_DIR)/main.o
PRJ_DUMP = $(BUILD_DIR)/prj.lst

ELF = $(BUILD_DIR)/prj.elf
HEX = $(FLASH_DIR)/prj.hex

all: $(HEX)

# Compile
$(OBJ): $(SRC) 
	$(CC) -c $< -o $@

# Link
$(ELF): $(OBJ)
	$(CC) -mmcu=$(MCU) $^ -o $@

#.c into .o
build: $(OBJ)
$(OBJ): $(SRC) 
	$(CC) -c $< -o $@

clean:
	rm -f $(BUILD_DIR)/*.o
