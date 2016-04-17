//VARIABLES AND DEFINES HERE - NEEDED BY THE WS2812 DRIVER CODE
#define WS2812_pin 8 // only digital pin 8 works right now
#define NUM_LEDS (256)// total number of RGB LEDs

//Unions and structs
typedef union Color 
{
  unsigned long longColor;
  struct{
    byte a,b,g,r;
  } rgb;
} Color;

typedef union SubPixel 
{
  struct
  {
    byte sub;
    byte pixel;
  };
  unsigned short subShort;
} SubPixel;

typedef struct Bullet
{
  SubPixel x;
  SubPixel y;
  float dX, dY;
  Color color;
  Bullet * nextBullet;
} Bullet;

typedef struct Player
{
  byte x, y;
  byte mask[25];
  Color color;
  Bullet * bulletList;
} Player;


//Function Prototypes
void RGB_update(int LED, byte RED, byte GREEN, byte BLUE);//function to drive LEDs
void rotateRight();
void shiftRight(char wrap);
void getPixel(byte x, byte y, Color * cPtr);
void setPixel(byte x, byte y, union Color c);
void setColor(union Color * color, byte r, byte g, byte b);
void drawRect(byte x, byte y, byte w, byte h, union Color c);
void drawCircle(byte x, byte y, byte d, union Color c);
void blit(byte * ar, byte x, byte y, byte w, byte h);

