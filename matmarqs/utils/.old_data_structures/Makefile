# Simple Makefile for Stack Utility Library
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -g
LDFLAGS = 
TARGET = test_stack
LIB = stack

# Source files
SRCS = stack.c test_stack.c
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Build test executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

# Compile .c files to .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Build static library
lib$(LIB).a: stack.o
	ar rcs $@ $^

# Build shared library
lib$(LIB).so: stack.o
	$(CC) -shared -o $@ $^

# Run tests
test: $(TARGET)
	./$(TARGET)

# Clean build artifacts
clean:
	rm -f $(TARGET) *.o *.a *.so

# Phony targets
.PHONY: all test clean
