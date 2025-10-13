# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

# The final executable name
TARGET = jobfinder

# List of all source files
SOURCES = main.c utils.c file_handler.c user_management.c job_management.c application_management.c ui.c

# Automatically generate object file names from source files
OBJECTS = $(SOURCES:.c=.o)

# Default rule: build the executable
all: $(TARGET)

# Rule to link object files into the final executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Rule to compile a .c file into a .o file
# The -c flag means compile but do not link
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean up build files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Phony targets are not actual files
.PHONY: all clean