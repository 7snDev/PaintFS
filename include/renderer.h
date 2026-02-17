#ifndef RENDERER_H
#define RENDERER_H

#include "stroke.h"
#include "stack_stroke.h"
#include <SDL2/SDL.h>

void rendererInit(int width, int height);
void rendererClear();
void rendererDrawStroke(const Stroke *stroke);
void rendererDrawAll(const StackStroke *strokes, int count);
SDL_Surface *exportSurface();
void rendererPresent();
void rendererDestroy();

#endif
