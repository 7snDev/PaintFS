#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

typedef struct {
  bool quit;
  bool left_click;
  bool right_click;
  bool ctrl;
  bool shift;
  bool z;
  bool s;
  bool wheel;
  bool motion;
  int y_wheel;
  int mouse_x;
  int mouse_y;
} InputState;

void inputUpdate(InputState *state);

#endif
