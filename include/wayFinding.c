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

position thisPOS = {
  .x = 6,
  .y = 4,
};
position target = {
  .x = 0,
  .y = 0,
};

int cnt = 0;
step way[25] = {0};

POINT_TYPE getPOINT(int x,int y)
{
  return map[y][x];
}

step * getWAY(const position * thisPOS, const position * target, step * lastStep)
{

  
  int This_cnt = cnt;
  position fp = {
    .x = thisPOS->x,
    .y = thisPOS->y
  };
  //gatTarget
  if (fp.x+1 == target->x && fp.y == target->y)
  {
    way[cnt].dx = 1;
    way[cnt].dy = 0;
    cnt++;
    way[cnt].dx = EOF;
    way[cnt].dy = EOF;
    return way;
  }
  if (fp.x == target->x && fp.y+1 == target->y)
  {
    way[cnt].dx = 0;
    way[cnt].dy = 1;
    cnt++;
    way[cnt].dx = EOF;
    way[cnt].dy = EOF;
    return way;
  }
  if (fp.x-1 == target->x && fp.y == target->y)
  {
    way[cnt].dx = -1;
    way[cnt].dy = 0;
    cnt++;
    way[cnt].dx = EOF;
    way[cnt].dy = EOF;
    return way;
  }
  if (fp.x == target->x && fp.y-1 == target->y)
  {
    way[cnt].dx = 0;
    way[cnt].dy = -1;
    cnt++;
    way[cnt].dx = EOF;
    way[cnt].dy = EOF;
    return way;
  }
  //Or not
  if(getPOINT(fp.x+1,fp.y) == ROAD)
  {
    position tp = {
      .x = fp.x + 1,
      .y = fp.y
    };
    way[cnt].dx = 1;
    way[cnt].dy = 0;
    getWAY(&tp,target,&way[cnt++]);
    if (way[cnt].dx == EOF && way[cnt].dy == EOF)
    {
      return way;
    }
  }
  if(getPOINT(fp.x,fp.y+1) == ROAD)
  {
    position tp = {
      .x = fp.x,
      .y = fp.y + 1 
    };
    way[cnt].dx = 0;
    way[cnt].dy = 1;
    getWAY(&tp,target,&way[cnt++]);
    if (way[cnt].dx == EOF && way[cnt].dy == EOF)
    {
      return way;
    }
  }
  if(getPOINT(fp.x-1,fp.y) == ROAD)
  {
    position tp = {
      .x = fp.x - 1,
      .y = fp.y 
    };
    way[cnt].dx = -1;
    way[cnt].dy = 0;
    getWAY(&tp,target,&way[cnt++]);
    if (way[cnt].dx == EOF && way[cnt].dy == EOF)
    {
      return way;
    }
  }
  if(getPOINT(fp.x,fp.y-1) == ROAD)
  {
    position tp = {
      .x = fp.x,
      .y = fp.y - 1 
    };  
    way[cnt].dx = 0;
    way[cnt].dy = -1;
    getWAY(&tp,target,&way[cnt++]);
    if (way[cnt].dx == EOF && way[cnt].dy == EOF)
    {
      return way;
    }
  }
  //When go into a error way
  if (fp.x+1 > 11 || fp.y+1 > 8 || fp.x -1 < 0 || fp.y-1 < 0)
  {
    if (getPOINT(fp.x+1,fp.y) != ROAD || getPOINT(fp.x-1,fp.y) != ROAD || getPOINT(fp.x,fp.y+1) != ROAD || getPOINT(fp.x,fp.y-1) != ROAD)
    {
      way[cnt].dx = UnFind;
      way[cnt].dy = UnFind;
    }
    
  }
  
}