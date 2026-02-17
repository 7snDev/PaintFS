#ifndef STACK_STROKE_H
#define STACK_STROKE_H

#include "stroke.h"

typedef struct {
  Stroke *strokes;
  long length;
  int current;
  long capacity;
} StackStroke;

void initStackStorke(StackStroke *s);
void pushStroke(StackStroke *ss, Stroke *s);
void undo(StackStroke *s);
void redo(StackStroke *s);
void freeStackStroke(StackStroke *s);

#endif
