//========------------**********!SUBLIMINAL!********--------==============//
#include <graphics.h>
#include <stdlib.h>       // For Random.
#include <conio.h>        // For kbhit.
#include <dos.h>          // For delay
#include "msgs.h"
#include "words.h"

#define XMAX 640
#define YMAX 480
#define MIN_TIME 50
#define DEF_TIME 200      // Milliseconds
#define MAX_TIME 1000
#define INC_TIME 50

#define PLUS(c)  ( ((c) == '+') || ((c) == '=') )
#define MINUS(c) ((c) == '-')

int setup(void);
void message(int d);
void cleanup(void);

msgs m;                   // Global.

void main(void)
{
  int delay;
  char ch;

  delay = DEF_TIME;

  m.load(word_list);

  if (setup())
    return;

  while(kbhit())
   getch();

  do
   {
    while (! kbhit())
      message(delay);
    ch = getch();
    if (MINUS(ch) &&
        (delay >= MIN_TIME))
      delay -= INC_TIME;
    if (PLUS(ch) &&
        (delay <= MAX_TIME))
      delay += INC_TIME;
   }
  while (ch == '-' || ch == '+');

  cleanup();

  cputs("\n\n\n(C) 1995   N.A.A. MATHEWSON");

}

int setup(void)
{
  int gdriver = DETECT, gmode, errorcode;
  errorcode = registerbgidriver(EGAVGA_driver);
  if (errorcode < 0)
    return 1;
  initgraph(&gdriver, &gmode, "");
  errorcode = graphresult();
  if (errorcode != grOk)
    return 2;
  errorcode = registerbgifont(triplex_font);
  if (errorcode < 0)
    return 3;
  errorcode = registerbgifont(sansserif_font);
  if (errorcode < 0)
    return 5;
   clearviewport();
  settextjustify(LEFT_TEXT,TOP_TEXT);
  setcolor(WHITE);
  setfillstyle(SOLID_FILL, BLACK);
  return 0;
}

void message(int d)
{
  static int x, y, msg, n, dx, dy;
  msg = random(m.n());
  switch (random(2))
   {
    case 0 : n = SANS_SERIF_FONT;
	     break;
    case 1 : n = TRIPLEX_FONT;
	     break;
   };
  settextstyle(n,0,random(5)+1);
  dx = textwidth(m[msg]);
  dy = textheight(m[msg]) + 20;
  x=random(XMAX-dx);
  y=random(YMAX-dy);
  if (x < 0)
    return;
  outtextxy(x,y,m[msg]);
  delay(d);
  bar(x,y,x+dx,y+dy);
}

void cleanup(void)
{
  closegraph();
}

