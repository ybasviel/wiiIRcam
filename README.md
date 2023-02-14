# wiiIRcam

Wii Remote Controller IR Camera Library for Arduino



## example

```cpp
#include <wiiIRcam.h>

#define SENSITIVITY 2

wiiIRcam cam;

void setup(){
    Serial.begin(115200);
    cam.begin(SENSITIVITY); // You can omit SENSITIVITY
}

void loop(){
    char str[128];

    if( cam.get() ){
        sprintf(str, "%d,%d,%d,%d,%d,%d,%d,%d\n", cam.x1, cam.y1, cam.x2, cam.y2, cam.x3, cam.y3, cam.x4, cam.y4);
        Serial.print(str);
    }
}
```

## References

1. kako, Kako Homepage, Wiiリモコンのポインティング用赤外線センサ部品の解析 [http://www.kako.com/neta/2007-001/2007-001.html](http://www.kako.com/neta/2007-001/2007-001.html)
2. kako, Kako Homepage, Wiiリモコンの赤外線センサをマイコンに接続して使ってみる (+マウス化)[http://www.kako.com/neta/2008-009/2008-009.html](http://www.kako.com/neta/2008-009/2008-009.html)