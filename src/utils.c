#include "utils.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>

void throwError(const char *msg, const char *file, int line) {
  fprintf(stderr, "[%s:%d] %s", file, line, msg);

  const char *sdlError = SDL_GetError();
  if (sdlError && *sdlError)
    fprintf(stderr, "[SDL] %s", sdlError);
  SDL_Quit();
  exit(EXIT_FAILURE);
}

void intToColor(int num, Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a) {
  *r = (num >> 24) & 0xFF;
  *g = (num >> 16) & 0xFF;
  *b = (num >> 8) & 0xFF;
  *a = num & 0xFF;
}
