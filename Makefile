CC = gcc
CFLAGS = -Wall -Wextra -O3 -march=native -g -Iinclude `pkg-config --cflags sdl2`
LDFLAGS = `pkg-config --libs sdl2`

SRC = $(wildcard src/*.c)
BUILDDIR = build
OBJ = $(patsubst src/%.c,$(BUILDDIR)/%.o,$(SRC))
TARGET = $(BUILDDIR)/PaintFS

build: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

$(BUILDDIR)/%.o: src/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR)/*
