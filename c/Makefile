# Compiler and flags
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Wno-comment
OUTDIR = out

# Source files
SRCS = main.c $(wildcard f32/*.c)

# Object files (placed in the out/ directory)
OBJS = $(patsubst %.c,$(OUTDIR)/%.o,$(SRCS))

# Output binary
TARGET = main

# Default target
all: $(TARGET)

# Build the target binary
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Rule for creating object files
$(OUTDIR)/%.o: %.c
	@mkdir -p $(dir $@) # Create directory structure for object files
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(OUTDIR) $(TARGET)

# Rebuild target
rebuild: clean all

# Phony targets to avoid conflicts with files of the same name
.PHONY: all clean rebuild