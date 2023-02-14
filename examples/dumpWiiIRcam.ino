#include <wiiIRcam.h>

#define SENSITIVITY 2

wiiIRcam cam;

void setup()
{
  Serial.begin(115200);
  cam.begin(SENSITIVITY); // You can omit SENSITIVITY
}

void loop()
{
  char str[128];

  if (cam.get())
  {
    sprintf(str, "%d,%d,%d,%d,%d,%d,%d,%d\n", cam.x1, cam.y1, cam.x2, cam.y2, cam.x3, cam.y3, cam.x4, cam.y4);
    Serial.print(str);
  }
}