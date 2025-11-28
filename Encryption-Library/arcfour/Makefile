# Compiler and flags
CC = gcc
CFLAGS = -O2 -Wall
AR = ar
INSTALL_DIR_INCLUDE = /usr/local/include
INSTALL_DIR_LIB = /usr/local/lib

# Library name
LIBNAME = librc4.a

# Source files
SRC = rc4.c
OBJ = rc4.o

# Default target: build library
all: $(LIBNAME)

# Compile object file
$(OBJ): $(SRC) rc4.h
	$(CC) $(CFLAGS) -c $(SRC)

# Create static library
$(LIBNAME): $(OBJ)
	$(AR) rcs $(LIBNAME) $(OBJ)

# Install library to system directories
install: $(LIBNAME)
	sudo cp rc4.h $(INSTALL_DIR_INCLUDE)/
	sudo cp $(LIBNAME) $(INSTALL_DIR_LIB)/
	sudo ldconfig

# Clean object files and library
clean:
	rm -f $(OBJ) $(LIBNAME)
