# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Iinclude -g

# Platform-specific settings
ifeq ($(OS),Windows_NT)
    RM = del
    TARGET = turing.exe
    SEP = /
else
    RM = rm -f
    TARGET = turing
    SEP = /
endif

# Source files
SOURCES = $(wildcard src$(SEP)*.c)

# Build the executable
$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

# Clean the build
clean:
	$(RM) $(TARGET)

# Rebuild the project
re: clean $(TARGET)

# Phony targets
.PHONY: clean re
