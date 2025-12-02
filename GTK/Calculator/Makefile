# -----------------------------
#   Scientific Calculator Build
#   Auto Build + Auto Run
# -----------------------------

CC = gcc
CFLAGS = -Wall -g `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0` -lm

TARGET = scientific_calculator
SRC = scientific_calculator.c

all: build run

build: $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS) $(LIBS)

run:
	./$(TARGET)

clean:
	rm -f $(TARGET)
