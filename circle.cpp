#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAXLINE 22

char *screen[MAXLINE];
char init_OK = 0;

int screen_init()
{
  int i;
  for (i=0; i<MAXLINE; i++)
  {
    screen[i] = (char *)calloc(80, sizeof(char));
    if (screen[i]==NULL) return 0;
    memset(screen[i], ' ', 79);
  }
  init_OK = 1;
  return 1;
}

void screen_print()
{
  int i;
  for (i=0; i<MAXLINE; i++) printf("%s\r\n", screen[i]);
}

void screen_outxy(int x, int y, char *s)
{
  while (*s) memset(screen[y-1]+x++ -1, *s++, 1);
}

void screen_free()
{
  int i;
  for (i=0; i<MAXLINE; i++) free(screen[i]);
}

void line(int x0, int y0, int x1, int y1)
{
  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
  int err = (dx>dy ? dx : -dy)/2, e2;
  for(;;)
  {
    screen_outxy(x0+1,y0+1, "*");
    if (x0==x1 && y0==y1) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
}

void circle(int x0, int y0, int radius)
{
  int x = radius, y = 0;
  int radiusError = 1-x;
  while(x >= y)
  {
    screen_outxy(x + x0, y + y0, "*");
    screen_outxy(y + x0, x + y0, "*");
    screen_outxy(-x + x0, y + y0, "*");
    screen_outxy(-y + x0, x + y0, "*");
    screen_outxy(-x + x0, -y + y0, "*");
    screen_outxy(-y + x0, -x + y0, "*");
    screen_outxy(x + x0, -y + y0, "*");
    screen_outxy(y + x0, -x + y0, "*");
    y++;
    if (radiusError<0)
      radiusError += 2 * y + 1;
    else
    {
      x--;
      radiusError+= 2 * (y - x + 1);
    }
  }
}

int main()
{
  printf("Bresenham's Line & Circle\n");
  if (!screen_init()) exit(1);
  screen_outxy(6, 4, "circle");
  circle(5, 17, 3);
  screen_print();
  screen_free();
  return 0;
}