#include "fileio.h"

void exportCanvas(SDL_Surface *surface, const char *path) {
  SDL_SaveBMP(surface, path);
  SDL_FreeSurface(surface);
}
