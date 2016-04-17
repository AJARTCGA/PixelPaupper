#include <stdlib.h>

/*void drawPlayer(Player * p)
{
  float i, j;
  int r1, r2;
  Color c2;
  r1 = p -> r1 * p ->r1;
  r2 = p -> r2 * p ->r2;
  for(i = 0; i <= 15; i++)
  {
    for(j = 0; j <= 15; j++)
    {
      if (r1/ ((i-p->x1)*(i-p->x1) + (j-p->y1)*(j-p->y1)) + r2 /((i-p->x2)*(i-p->x2) + (j-p->y2)*(j-p->y2)) >= 1)
      {
        setPixel(i, j, p -> color);
      }  
    }
  }
  c2.longColor = 0x10000000;
  setPixel(p -> x1, p -> y1, c2);
  setPixel(p -> x2, p -> y2, c2);
  if(p -> bulletList != NULL)
  {
    drawBullet(p -> bulletList);
  }
}*/

void drawPlayer(Player * p, byte doClear)
{
  byte i, j;
  byte count = 0;
  static Color clearColor;
  
  for(i = p->x; i <= p->x + 4; i++)
  {
    for(j = p->y; j <= p->y + 4; j++)
    {
      //Serial.println(p->mask[i + j * 5]);
      if(p->mask[count])
      {
        if (doClear)
        {
          setPixel(i, j, clearColor);
        }
        else
        {
          setPixel(i, j, p->color);
        }
      }
      count++;
    }
  }
  if(p -> bulletList != NULL)
  {
    drawBullet(p -> bulletList);
  }
}

void drawPlayers(Player * p1, Player * p2)
{
  drawPlayer(p1, 1);
  drawPlayer(p2, 1);
  setBlendMode(ADD_BLEND);
  drawPlayer(p1, 0);
  drawPlayer(p2, 0);
  setBlendMode(NO_BLEND);
  setPixel(p1->x+2, p1->y+2, p1->coreColor);
  setPixel(p2->x+2, p2->y+2, p2->coreColor);
}

void drawBullet(Bullet * b)
{
  setPixel(b -> x.pixel, b -> y.pixel, b -> color);
  if ( b -> nextBullet != NULL)
  {
    drawBullet(b -> nextBullet);
  }
}

void updateBullet(Bullet * b)
{
  b -> x.subShort += b -> dX;
  b -> y.subShort += b -> dY;
  if(b -> x.pixel >= 15 || b -> x.pixel <= 0)
  {
    b -> dX *= -1;
  }
  if(b -> y.pixel >= 15 || b -> y.pixel <= 0)
  {
    b -> dY *= -1;
  }
}

void updatePlayer(Player * p)
{
  if(p -> bulletList)
  {
    updateBullet(p -> bulletList);
  }
}

byte checkHitPlayerBullet(Player * p, Bullet * b)
{
  static byte r, c;
  if (b->isDead)
  {
    return 0;
  }
  if (b->x.pixel >= p->x && (r = b->x.pixel - p->x) <= 4)
  {
    if (b->y.pixel >= p->y && (c = b->y.pixel - p->y) <= 4)
    {
      if (p->mask[5*r + c])
      {
        p->mask[5*r + c] = 0;
        b->isDead = 1;
        return 1;
      }
      else
      {
        return 0;
      }
    }
  }
}

void playerShootBullet(Player * p)
{
  Bullet b;
  Color c;
  c.longColor = 0x00101000;
  b.x.pixel = p->x;
  b.y.pixel = p->y;
  b.dY = -1;
  b.nextBullet = NULL;
  b.color = c;
  addBullet(&(p -> bulletList), &b);
}

void addBullet(Bullet ** bList, Bullet * b)
{
  while(*bList != NULL)
  {
    bList = &((*bList) -> nextBullet);
  }
  (*bList) = b;
}

void rotatePlayer(Player * p)
{
  byte i, j;
  byte tempArray[25]; 
  for(i = 0; i < 5; i++)
  {
    for(j = 0; j < 5; j++)
    {
      tempArray[j + (-i + 4) * 5]  = p->mask[i + j * 5];
    }
  }
  memcpy(p->mask, tempArray, 25);
}
