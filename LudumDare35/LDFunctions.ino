<<<<<<< HEAD
=======
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

>>>>>>> origin
void drawPlayer(Player * p, byte doClear)
{
  byte i, j;
  byte count = 0;
  static Color clearColor;
  
  for(i = p->x; i <= p->x; i++)
  {
    for(j = p->y; j <= p->y; j++)
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
  setPixel(p1->x, p1->y, p1->coreColor);
  setPixel(p2->x, p2->y, p2->coreColor);
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
  Serial.print(b->x.pixel);
  Serial.print(" ");
  Serial.print(b->y.pixel);
  Serial.print(" ");
  Serial.print(b->dX);
  Serial.print(" ");
  Serial.print(b->dY);
  Serial.print("\n");
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
  if (b->x.pixel >= p->x && (b->x.pixel - p->x)=c <= 4)
  {
    if (b->y.pixel >= p->y && (b->y.pixel - p->y)=r <= 4)
    {
      return p->mask[5*r+c];
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

void drawEnemy(Enemy * e)
{
  byte i, j;
  byte count = 0;
  
  for(j = e->y; j <= e->y + 3; j++)
  {
    for(i = e->x; i <= e->x + 3; i++)
    {
      if(e->mask[count])
      {
        setPixel(i, j, e->color);
      }
      count++;
    }
  }
  if(e -> bulletList != NULL)
  {
    drawBullet(e -> bulletList);
  }
}

