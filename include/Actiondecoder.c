#include "Actiondecoder.h"
#include "wayFinding.h"
// #include "motorDriver.h"


int decode(step * way, Direct * actions)
{
  enum status drt;
  int i;
  for (i = 0; way[i].dx != ROF; i++)
  {
    if (way[i].dx == -1 && drt != _WEST)
    {
      drt = _WEST;
      actions[i] = W;
      break;
    }
    if (way[i].dx == 1 && drt != _EAST)
    {
      drt = _EAST;
      actions[i] = E;
      break;
    }
    if (way[i].dy == 1 && drt != _SOUTH)
    {
      drt = _SOUTH;
      actions[i] = S;
      break;
    }
    if (way[i].dy == -1 && drt != _NORTH)
    {
      drt = _SOUTH;
      actions[i] = N;
    }
  }
  i++;
  actions[i] = ROF;
  return 0;
}
