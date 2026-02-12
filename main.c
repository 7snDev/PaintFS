#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_surface.h"
#include "TinyPngOut.h"

#define WIDTH 900
#define HEIGHT 600

typedef struct {
  int x, y, r;
} Circle;

void DrawCircle(SDL_Surface *surface, Circle circle, Uint32 pixel) {
  float r2 = circle.r * circle.r;
  SDL_Rect rect = { circle.x - circle.r, circle.y - circle.r, circle.r + circle.x, circle.r + circle.y };
  Uint32 *pixels = (Uint32 *)surface->pixels;
  for (int x = rect.x; x < rect.w; x++) {
    for (int y = rect.y; y < rect.h; y++) {
      if (y > HEIGHT || y < 0 || x > WIDTH || x < 0)
        continue;

      int dx = x - circle.x;
      int dy = y - circle.y;
      if (dx*dx + dy*dy < r2) {
        pixels[(y * surface->pitch / 4) + x] = pixel;
      }
    }
  }
}

void exportImg(SDL_Surface *surface, char* path) {
  SDL_SaveBMP(surface, path);
}

int main() {

  SDL_Window *window = SDL_CreateWindow("Paint FS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
  SDL_Surface *surface = SDL_GetWindowSurface(window);

  Circle brush = { 450, 300, 10 };
  Uint32 color = 0xffffff;
  Uint32 colors[2] = { 0xffffff, 0 };

  SDL_Event event;
  bool running = true;
  bool bdown = false;
  bool ctrl = false;
  while (running) {
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT)
      running = false;
    if (event.type == SDL_MOUSEBUTTONDOWN) {
      bdown = true;
      brush.x = event.button.x;
      brush.y = event.button.y;
      if (event.button.button == SDL_BUTTON_LEFT)
        color = colors[0];
      else if (event.button.button == SDL_BUTTON_RIGHT)
        color = colors[1];
    }
    if (event.type == SDL_MOUSEWHEEL) {
      brush.r += event.wheel.y;
      if (brush.r < 1) 
        brush.r = 1;
      if (brush.r > 100)
        brush.r = 100;
    }
    if (event.type == SDL_MOUSEBUTTONUP) 
      bdown = false;
    if (event.type == SDL_MOUSEMOTION && bdown) {
      brush.x = event.motion.x;
      brush.y = event.motion.y;
    }
    if (event.type == SDL_KEYDOWN) {
      if (event.key.keysym.sym == SDLK_s && ctrl)
        exportImg(surface, "./img.png");
      else if (event.key.keysym.sym == SDLK_LCTRL) 
        ctrl = true;
    }
    if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_LCTRL)
      ctrl = false;
    if (bdown) 
      DrawCircle(surface, brush, color);

    SDL_UpdateWindowSurface(window);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
