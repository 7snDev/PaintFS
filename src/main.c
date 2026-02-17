#include "input.h"
#include "renderer.h"
#include "stack_stroke.h"
#include "stroke.h"
#include "fileio.h"
#include <stdlib.h>

#define INIT_WIDTH 900
#define INIT_HEIGHT 600

int main(int argc, char *argv[], char *envp[]) {
  rendererInit(INIT_WIDTH, INIT_HEIGHT);
  InputState input = { 0 };
  StackStroke history;
  initStackStorke(&history);
  Stroke currentStroke;
  int brush = 10;
  bool init = false;
  int color;

  while (!input.quit) {
    inputUpdate(&input);
    if (input.left_click || input.right_click) {
      if (input.left_click == true && input.right_click == false) {
        color = 0xFFFFFFFF;
      } else if (input.left_click == false && input.right_click == true) {
        color = 0x000000FF;
      } else {
        color = 0xFF00FFFF;
      }
      if (!init) {
        init = true;
        initStroke(&currentStroke, color, brush);
      }
      addPoint(&currentStroke, input.mouse_x, input.mouse_y);
    }
    if (!input.left_click && !input.right_click && init) {
      pushStroke(&history, &currentStroke);
      freeStroke(&currentStroke);
      init = false;
    }
    if (input.wheel) {
      brush += input.y_wheel;
      input.wheel = false;
    }
    if (input.s && input.ctrl) {
      exportCanvas(exportSurface(), "./img.bmp");
      input.s = false;
    }
    if (input.z && input.ctrl && input.shift) {
      redo(&history);
      input.z = false;
    }
    if (input.z && input.ctrl) {
      undo(&history);
      input.z = false;
    }

    rendererClear();
    rendererDrawAll(&history, history.current);
    if (init)
      rendererDrawStroke(&currentStroke);
    rendererPresent();
  }
  rendererDestroy();
  freeStroke(&currentStroke);
  freeStackStroke(&history);
  return EXIT_SUCCESS;
}
