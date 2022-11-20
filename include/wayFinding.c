#include "wayFinding.h"



POINT_TYPE map[9][12] = 
{ //0          //1         //2         //3             //4         //5            //6       //7            //8       //9             //10           //11
  {STOP,       MAIN_POINT, STOP,       MAIN_POINT,     STOP,       MAIN_POINT,    STOP,     MAIN_POINT,    STOP,     MAIN_POINT,     STOP,          MAIN_POINT},//0
  {STOP,       ROAD,       STOP,       ROAD,           STOP,       ROAD,          STOP,     ROAD,          STOP,     ROAD,           STOP,          ROAD},//1
  {STOP,       ROAD ,      ROAD,       ROAD,           ROAD,       ROAD,          ROAD,     ROAD,          ROAD,     ROAD,           STOP,          ROAD},//2
  {STOP,       STOP,       STOP,       STOP,           STOP,       ROAD,          STOP,     STOP,          STOP,     STOP,           STOP,          ROAD},//3
  {STOP,       STOP,       STOP,       STOP,           STOP,       ROAD,          ROAD,     ROAD,          ROAD,     ROAD,           ROAD,          ROAD},//4
  {STOP,       STOP,       STOP,       STOP,           STOP,       ROAD,          STOP,     STOP,          STOP,     STOP,           STOP,          ROAD},//5
  {MAIN_POINT, ROAD,       ROAD,       ROAD,           ROAD,       ROAD,          ROAD,     ROAD,          ROAD,     ROAD,           ROAD,          MAIN_POINT},//6
  {STOP,       STOP,       STOP,       STOP,           STOP,       ROAD,          STOP,     STOP,          STOP,     STOP,           STOP,          STOP},//7
  {STOP,       STOP,       STOP,       STOP,           STOP,       ROAD,          ROAD,     ROAD,          ROAD,     ROAD,           ROAD,          MAIN_POINT}//8
};

// position thisPOS = {
//   .x = 6,
//   .y = 4,
// };
// position target = {
//   .x = 0,
//   .y = 0,
// };

int cnt = 0;
step way[25] = {0};
int attached[9][12] = {0};

POINT_TYPE getPOINT(int x,int y)
{
  return map[y][x];
}

step * getWAY(position * thisPOS, const position * target/* , step * lastStep */)
{
  //When attached flag 1. When go back, flag 2.
  attached[thisPOS->y][thisPOS->x] = 1;
  //When found the target
  if (thisPOS->x+1 == target->x && thisPOS->y == thisPOS->y)
  {
    way[cnt].dx = 1;
    way[cnt].dy = 0;
    cnt++;
    way[cnt].dy = EOF;
    way[cnt].dx  =EOF;
    return way;
  }
  if (thisPOS->x-1 == target->x && thisPOS->y == thisPOS->y)
  {
    way[cnt].dx = -1;
    way[cnt].dy = 0;
    cnt++;
    way[cnt].dy = EOF;
    way[cnt].dx  =EOF;
    return way;
  }
  if (thisPOS->x == target->x && thisPOS->y+1 == thisPOS->y)
  {
    way[cnt].dx = 0;
    way[cnt].dy = 1;
    cnt++;
    way[cnt].dy = EOF;
    way[cnt].dx  =EOF;
    return way;
  }
  if (thisPOS->x+1 == target->x && thisPOS->y-1 == thisPOS->y)
  {
    way[cnt].dx = 0;
    way[cnt].dy = -1;
    cnt++;
    way[cnt].dy = EOF;
    way[cnt].dx  =EOF;
    return way;
  }
  


  if (getPOINT(thisPOS->x,thisPOS->y-1) == ROAD && attached[thisPOS->y-1][thisPOS->x] == 0)
  {
    goNorth(thisPOS);
    way[cnt].dx = 0;
    way[cnt].dy = -1;
    cnt++;
    return getWAY(thisPOS,target);
  }
  if (getPOINT(thisPOS->x,thisPOS->y+1) == ROAD && attached[thisPOS->y+1][thisPOS->x] == 0)
  {
    goSouth(thisPOS);
    way[cnt].dx = 0;
    way[cnt].dy = +1;
    cnt++;
    return getWAY(thisPOS,target);
  }
  if (getPOINT(thisPOS->x-1,thisPOS->y) == ROAD && attached[thisPOS->y][thisPOS->x-1] == 0)
  {
    goWest(thisPOS);
    way[cnt].dx = -1;
    way[cnt].dy = 0;
    cnt++;
    return getWAY(thisPOS,target);
  }
  if (getPOINT(thisPOS->x+1,thisPOS->y) == ROAD && attached[thisPOS->y][thisPOS->x+1] == 0)
  {
    goEast(thisPOS);
    way[cnt].dx = +1;
    way[cnt].dy = 0;
    cnt++;
    return getWAY(thisPOS,target);
  }

  //No direction to go
  if (attached[thisPOS->y-1][thisPOS->x] == 1)
  {
    attached[thisPOS->y-1][thisPOS->x] = 2;
    goNorth(thisPOS);
    cnt--;
    return getWAY(thisPOS,target);
  }
  if (attached[thisPOS->y+1][thisPOS->x] == 1)
  {
    attached[thisPOS->y+1][thisPOS->x] = 2;
    goSouth(thisPOS);
    cnt--;
    return getWAY(thisPOS,target);
  }
  if (attached[thisPOS->y][thisPOS->x+1] == 1)
  {
    attached[thisPOS->y][thisPOS->x+1] = 2;
    goEast(thisPOS);
    cnt--;
    return getWAY(thisPOS,target);
  }
  if (attached[thisPOS->y][thisPOS->x-1] == 1)
  {
    attached[thisPOS->y][thisPOS->x-1] = 2;
    goWest(thisPOS);
    cnt--;
    return getWAY(thisPOS,target);
  }
  //DFS
  // getWAY(thisPOS,target);
}


void fresh()
{
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 12; j++)
    {
      attached[i][i] = 0;
    }
    
  }
}

void goNorth(position * POS)
{
  POS->y -= 1;
}

void goSouth(position * POS)
{
  POS->y += 1;
}

void goWest(position * POS)
{
  POS->x -= 1;
}

void goEast(position * POS)
{
  POS->x += 1;
}