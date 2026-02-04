CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -g
TARGET = asciify
BUILD_DIR = out

$(BUILD_DIR)/$(TARGET): main.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ main.c

clean:
	rm -r $(BUILD_DIR)
