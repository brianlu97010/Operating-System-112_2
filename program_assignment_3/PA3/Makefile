# Makefile for Reader-Writer Implementation

# Compiler
CC = clang

# Targets
TARGETS = reader_writer writer reader

# Source files
SRC_READER_WRITER = reader_writer.c
SRC_WRITER = writer.c
SRC_READER = reader.c

# Object files
OBJ_READER_WRITER = $(SRC_READER_WRITER:.c=.o)
OBJ_WRITER = $(SRC_WRITER:.c=.o)
OBJ_READER = $(SRC_READER:.c=.o)

# Include semaphore header
INCLUDES = -I.

# CFLAGS
CFLAGS = -Wall -g

# LDFLAGS
LDFLAGS = -lm

# Default target
all: $(TARGETS)

# Compile and link reader_writer
reader_writer: $(OBJ_READER_WRITER)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compile and link writer
writer: $(OBJ_WRITER)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compile and link reader
reader: $(OBJ_READER)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Object files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

# Clean up
clean:
	rm -f $(TARGETS) *.o

# Run the program
run: all
	./reader_writer 100

.PHONY: all clean run

