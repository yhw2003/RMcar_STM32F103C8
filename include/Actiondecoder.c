#include "Actiondecoder.h"
#include "wayFinding.h"
enum status {
  TURN_LEFT, TURN_RIGHT, GO_STRAIGHT, TURN_DOUBLE,
};


enum status decode(step * way,Direct * direction,position * thisPOS,int length)
{
  enum status ret;
  // while(way++->dx != EOF)
  // {
    if (way->dx)
    {
      if (way->dx < 0)
      {
        switch (*direction)
        {
        case N: ret = TURN_LEFT; 
            break;
        case W: break;
        case S: ret = TURN_RIGHT;
            break;
        case E: ret = TURN_DOUBLE;
            break;
        }
        *direction = W;
        while (way++->dx == -1);
      }
      if (way->dx > 0)
      {
        switch (*direction)
        {
        case N: ret = TURN_RIGHT; 
            break;
        case W: ret = TURN_DOUBLE;
            break;
        case S: ret = TURN_LEFT;
            break;
        case E: break;
        }
        *direction = W;
        while (way++->dx == -1);
      }
      
    } else if (way->dy)
    {

    }
  // }
}