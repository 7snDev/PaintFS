#include "stack_stroke.h"
#include "stroke.h"
#include <stdlib.h>

void initStackStorke(StackStroke *s) {
  s->length = 0;
  s->current = 0;
  s->capacity = 8;
  s->strokes = malloc( sizeof(Stroke) * s->capacity);
}

void pushStroke(StackStroke *ss, Stroke *s) {
  if (ss->length >= ss->capacity && ss->current >= ss->length) {
    ss->capacity *= 2;
    ss->strokes = realloc(ss->strokes, sizeof(Stroke) * ss->capacity);
  }
  ss->strokes[ss->current++] = copyStroke(s);
  if (ss->length + 1 == ss->current)
    ss->length++;
}

void undo(StackStroke *s) {
  if (s->current > 0)
    s->current--;
}

void redo(StackStroke *s) {
  if (s->current < s->length)
    s->current++;
}

void freeStackStroke(StackStroke *s) {
  for (long i = 0; i < s->length; i++)
    freeStroke(&s->strokes[i]);
  free(s->strokes);
  s->length = 0;
  s->capacity = 0;
  s->current = 0;
}
