#ifndef _WAYFINDING_H_
#define _WAYFINDING_H_

#define ROF -400
#define UnFind -401

typedef enum _POINT_TYPE {
  STOP, ROAD, MAIN_POINT
} POINT_TYPE;

typedef enum _direct {
  N, E, S, W
} Direct;

typedef struct _position
{
  int x;
  int y;
} position;

typedef struct _step
{
int dx;
int dy;
} step;

void goEast(position * POS);
void goWest(position * POS);
void goSouth(position * POS);
void goNorth(position * POS);
void fresh();
step * getWAY(position * thisPOS, const position * target, step * way);

#endif