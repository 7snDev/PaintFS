#include "input.h"
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_mouse.h"
#include <SDL2/SDL.h>

void inputUpdate(InputState *state) {
  SDL_Event e;

  while (SDL_PollEvent(&e)) {
    switch (e.type) {
      case SDL_QUIT:
        state->quit = true;
        break;
      case SDL_MOUSEBUTTONDOWN:
        if (e.button.button == SDL_BUTTON_LEFT)
          state->left_click = true;
        else if (e.button.button == SDL_BUTTON_RIGHT)
          state->right_click = true;
        state->mouse_x = e.button.x;
        state->mouse_y = e.button.y;
        break;
      case SDL_MOUSEBUTTONUP:
        if (e.button.button == SDL_BUTTON_LEFT)
          state->left_click = false;
        else if (e.button.button == SDL_BUTTON_RIGHT)
          state->right_click = false;
        break;
      case SDL_MOUSEMOTION:
        state->motion = true;
        state->mouse_x = e.motion.x;
        state->mouse_y = e.motion.y;
        break;
      case SDL_KEYDOWN:
        if (e.key.keysym.sym == SDLK_LCTRL) 
          state->ctrl = true;
        else if (e.key.keysym.sym == SDLK_LSHIFT)
          state->shift = true;
        else if (e.key.keysym.sym == SDLK_z)
          state->z = true;
        else if (e.key.keysym.sym == SDLK_s)
          state->s = true;
        break;
      case SDL_KEYUP:
        if (e.key.keysym.sym == SDLK_LCTRL)
          state->ctrl = false;
        else if (e.key.keysym.sym == SDLK_LSHIFT)
          state->shift = false;
        else if (e.key.keysym.sym == SDLK_z)
          state->z = false;
        else if (e.key.keysym.sym == SDLK_s)
          state->s = false;
        break;
      case SDL_MOUSEWHEEL:
        state->wheel = true;
        state->y_wheel = e.wheel.y;
        break;
    }
  }
}

