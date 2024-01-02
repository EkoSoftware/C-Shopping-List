# Compiler and Flags
CC = gcc
CFLAGS = -g -Wall -Wextra -pedantic -std=c11

# Source files and executable
SRC := main.c functions.c
OBJ := $(SRC:.c=.o)
EXECUTABLE := Inventory.exe

# Build rule
all: $(EXECUTABLE)

# Link objects
$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(EXECUTABLE)

# Compile Source files to Object files
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXECUTABLE)