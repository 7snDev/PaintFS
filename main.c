#include <SDL2/SDL.h>
#include <stdbool.h>

#define WIDTH 900
#define HEIGHT 600

typedef struct {
  int x, y, r;
} Circle;

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

void DrawCircle(SDL_Renderer *renderer, SDL_Texture *circle, Circle brush, Uint8 r, Uint8 g, Uint8 b) {
 SDL_SetTextureColorMod(circle, r, g, b);
 SDL_Rect rect = { brush.x - brush.r, brush.y - brush.r, brush.r * 2, brush.r * 2 };
 SDL_RenderCopy(renderer, circle, NULL, &rect);
}

void exportImg(SDL_Renderer *renderer, char* path) {
  SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, WIDTH, HEIGHT, 32, SDL_PIXELFORMAT_RGBA32);
  SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_RGBA32, surface->pixels, surface->pitch);
  SDL_SaveBMP(surface, path);
  SDL_FreeSurface(surface);
}

int main() {

  SDL_Window *window = SDL_CreateWindow("Paint FS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_Texture *circle = CreateCircle(renderer, 10);
  Circle brush = { 450, 300, 10 };
  Uint8 color[3] = { 255, 255, 255 };

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
        for (char i = 0; i < 3; i++)
          color[i] = 255;
      else if (event.button.button == SDL_BUTTON_RIGHT)
        for (char i = 0; i < 3; i++)
          color[i] = 0;
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
      if (event.key.keysym.sym == SDLK_s && ctrl) {
        exportImg(renderer, "./img.bmp");
      }
      else if (event.key.keysym.sym == SDLK_LCTRL) 
        ctrl = true;
    }
    if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_LCTRL)
      ctrl = false;
    if (bdown) 
      DrawCircle(renderer, circle, brush, color[0], color[1], color[2]);
    
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
