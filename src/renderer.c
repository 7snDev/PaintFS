#include "renderer.h"
#include <SDL2/SDL.h>
#include "SDL_render.h"
#include "utils.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *circle;

SDL_Texture* CreateCircle(SDL_Renderer *renderer, int r) {
  int size = r * 2;
  SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, size, size, 32, SDL_PIXELFORMAT_RGBA32);
  Uint32 *pixels = (Uint32 *)surface->pixels;
  float r2 = r * r;

  for (int x = 0; x < size; x++) {
    for (int y = 0; y < size; y++) {
      int dx = x - r;
      int dy = y - r;
      if (dx*dx + dy*dy <= r2)
        pixels[y * size + x] = 0xffffffff;
      else
        pixels[y * size + x] = 0;
     }
  }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
    return tex;
}

void rendererInit(int width, int height) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    THROW("SDL init failed");

  window = SDL_CreateWindow("PaintFS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE);
  if (!window)
    THROW("Failed to create window");
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  circle = CreateCircle(renderer, 5);
}

void rendererClear() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}

void rendererPresent() {
  SDL_RenderPresent(renderer);
}

void rendererDrawStroke(const Stroke *s) {
  if (s->length == 0) return;
  Uint8 r, g, b, a;
  intToColor(s->color, &r, &g, &b, &a);
  SDL_SetTextureColorMod(circle, r, g, b);
  SDL_SetTextureBlendMode(circle, a);
  
  SDL_Rect rect = {0, 0, s->brush_size * 2, s->brush_size * 2};
  if (s->length == 1) {
    rect.x = s->x_points[0] - s->brush_size;
    rect.y = s->y_points[0] - s->brush_size;
    SDL_RenderCopy(renderer, circle, NULL, &rect);
    return;
  }
  for (long i = 1; i < s->length; i++) {
    int x1 = s->x_points[i - 1];
    int y1 = s->y_points[i - 1];
    int x2 = s->x_points[i];
    int y2 = s->y_points[i];
    
    float dx = x2 - x1;
    float dy = y2 - y1;
    float distance = sqrt(dx*dx + dy*dy);
    
    int steps = (int)(distance / (s->brush_size * 0.25f));
    if (steps < 1) steps = 1;
    
    for (int j = 0; j <= steps; j++) {
        rect.x = x1 + (dx * j / steps) - s->brush_size;
        rect.y = y1 + (dy * j / steps) - s->brush_size;
        SDL_RenderCopy(renderer, circle, NULL, &rect);
    }
  }
}

void rendererDrawAll(const StackStroke *s, int count) {
  if (s->length == 0 || count == 0 || s->length < count) return;
  for (int i = 0; i < count; i++)
    rendererDrawStroke(&s->strokes[i]);
}

SDL_Surface* exportSurface() {
  int width, height;
  SDL_GetWindowSize(window, &width, &height);
  SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32);
  SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_RGBA32, surface->pixels, surface->pitch);
  return surface;
}

void rendererDestroy() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
