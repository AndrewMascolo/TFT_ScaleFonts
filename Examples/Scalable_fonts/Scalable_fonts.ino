// Use IDE 1.0.6 or 1.5.x
#include <UTFT.h>
#include <UTouch.h>
#include <TFT_ScaleFonts.h>

extern uint8_t SmallFont[];

UTFT    myGLCD(CTE70, 25, 26, 27, 28);
UTouch  myTouch( 6, 5, 4, 3, 2);

TFT_ScaleFonts myFont(&myGLCD);

void setup()
{
  Serial.begin(115200);
  myGLCD.InitLCD(LANDSCAPE);
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  myGLCD.fillScr(0x0);
  myGLCD.setColor(0xFFFF); // font color = white
  
  myFont.printNumI(100, 50, 10, 3, 10); // value, x, y, length (_ _ _), scale = x10 of small font

  myGLCD.printNumI(100, 50, 200, 3); // using the same length
}

void loop()
{

}
