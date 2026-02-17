#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL_stdinc.h>

#define THROW(msg) throwError(msg, __FILE__, __LINE__)

void throwError(const char *error, const char *file, int line);
void intToColor(int num, Uint8 *r, Uint8 *g, Uint8*b, Uint8 *a);

#endif
