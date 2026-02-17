#include "stroke.h"
#include <stdlib.h>
#include <memory.h>

void initStroke(Stroke *s, int color, float brush) {
  s->length = 0;
  s->capacity = 8;
  s->color = color;
  s->brush_size = brush;
  s->x_points = malloc( sizeof(int) * s->capacity);
  s->y_points = malloc( sizeof(int) * s->capacity);
}

void addPoint(Stroke *s, int x, int y) {
  if (s->length >= s->capacity) {
    s->capacity *= 2;
    s->x_points = realloc(s->x_points, sizeof(int) * s->capacity);
    s->y_points = realloc(s->y_points, sizeof(int) * s->capacity);
  }
  s->x_points[s->length] = x;
  s->y_points[s->length] = y;
  s->length++;
}

void freeStroke(Stroke *s) {
  free(s->x_points);
  free(s->y_points);

  s->x_points = NULL;
  s->y_points = NULL;
  s->length = 0;
  s->capacity = 0;
}

Stroke copyStroke(Stroke *src) {
  Stroke cp;
  cp.length = src->length;
  cp.color = src->color;
  cp.brush_size = src->brush_size;
  cp.capacity = src->capacity;
  cp.x_points = malloc(sizeof(int) * cp.length);
  cp.y_points = malloc(sizeof(int) * cp.length);
  memcpy(cp.x_points, src->x_points, sizeof(int) * cp.length);
  memcpy(cp.y_points, src->y_points, sizeof(int) * cp.length);
  return cp;
}
