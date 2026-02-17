#ifndef STROKE_H
#define STROKE_H

typedef struct {
  int *x_points;
  int *y_points;
  long length;
  long capacity;
  int color;
  float brush_size;
} Stroke;

void initStroke(Stroke *s, int color, float brush);
void addPoint(Stroke *s, int x, int y);
void freeStroke(Stroke *s);
Stroke copyStroke(Stroke *src);

#endif
