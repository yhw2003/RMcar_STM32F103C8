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
  //When attached flag 1. When go back, flag 2.
  int attached[9][12] = {0};
  

}