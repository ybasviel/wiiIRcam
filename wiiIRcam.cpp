#include "wiiIRcam.h"

void wiiIRcam::write2byte(uint8_t a, uint8_t b) {
  Wire.beginTransmission(WIIMOTE_ADDR);
  Wire.write(a);
  Wire.write(b);
  Wire.endTransmission();
  delay(70);
}

void wiiIRcam::writeNbyte(uint8_t n, uint8_t *a) {
  Wire.beginTransmission(WIIMOTE_ADDR);
  for(uint8_t i = 0; i < n; i++){
    Wire.write(a[i]);
  }
  Wire.endTransmission();
  delay(70);
}

void wiiIRcam::begin() {

  Wire.begin();
  Wire.setClock(WIIMOTE_I2C_CLOCK);
  Wire.setWireTimeout(2500, true);


  write2byte(0x30, 0x01);
  write2byte(0x30, 0x08);
  write2byte(0x06, 0x90);
  write2byte(0x08, 0xC0);
  write2byte(0x1A, 0x40);
  write2byte(0x33, 0x33);
  delay(100);
}

void wiiIRcam::begin(uint8_t sensitivity){
  Wire.begin();
  Wire.setClock(WIIMOTE_I2C_CLOCK);
  Wire.setWireTimeout(2500, true);

  uint8_t p0, p1, p2, p3;
  if(sensitivity == 0){
    p0 = 0x72;
    p1 = 0x20;
    p2 = 0x1f;
    p3 = 0x03;
  } else if(sensitivity == 1){
    p0 = 0xc8;
    p1 = 0x36;
    p2 = 0x35;
    p3 = 0x03;
  } else if(sensitivity == 2){
    p0 = 0xaa;
    p1 = 0x64;
    p2 = 0x63;
    p3 = 0x03;
  } else if(sensitivity == 3){
    p0 = 0x96;
    p1 = 0xb4;
    p2 = 0xb3;
    p3 = 0x04;
  } else {
    p0 = 0x96;
    p1 = 0xfe;
    p2 = 0xfe;
    p3 = 0x05;
  }

  write2byte(0x30, 0x01);

  uint8_t cmd1[] = {0x00, 0x02, 0x00, 0x00, 0x71, 0x01, 0x00, p0 };
  writeNbyte(8, (uint8_t*)cmd1);
  
  uint8_t cmd2[] = {0x07, 0x00, p1 };
  writeNbyte(3, (uint8_t*)cmd2);
  
  uint8_t cmd3[] = {0x1a, p2, p3 };
  writeNbyte(3, (uint8_t*)cmd3);
  
  write2byte(0x33, 0x03);
  write2byte(0x30, 0x08);
}

bool wiiIRcam::get() {
  uint8_t buf[16];
  uint8_t s;

  uint8_t idx = 0;

  Wire.beginTransmission(WIIMOTE_ADDR);
  Wire.write(0x36);
  uint8_t res = Wire.endTransmission();
  uint8_t num = Wire.requestFrom(WIIMOTE_ADDR, 16);
  while (Wire.available()) {
    buf[idx++] = Wire.read();
  }

  if (res == 0 && num == 16) {

    this->x1 = buf[1];
    this->y1 = buf[2];
    s = buf[3];
    this->x1 += (s & 0x30) << 4;
    this->y1 += (s & 0xC0) << 2;

    this->x2 = buf[4];
    this->y2 = buf[5];
    s = buf[6];
    this->x2 += (s & 0x30) << 4;
    this->y2 += (s & 0xC0) << 2;

    this->x3 = buf[7];
    this->y3 = buf[8];
    s = buf[9];
    this->x3 += (s & 0x30) << 4;
    this->y3 += (s & 0xC0) << 2;

    this->x4 = buf[10];
    this->y4 = buf[11];
    s = buf[12];
    this->x4 += (s & 0x30) << 4;
    this->y4 += (s & 0xC0) << 2;
    
    return true;
  } else {
    return false;
  }
}