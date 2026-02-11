CC = gcc
CFLAGS = -Wall -Wextra -O3 -march=native
LINKINGFLAGS = `sdl2-config --cflags --libs`
FILES = main.c TinyPngOut.c 
TARGET = PaintFS

build:
	$(CC) $(CFLAGS) -o $(TARGET) $(FILES) $(LINKINGFLAGS)
clean:
	rm -rf $(TARGET)
