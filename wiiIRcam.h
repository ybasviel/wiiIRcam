#pragma once

#include <Arduino.h>
#include <Wire.h>

#define WIIMOTE_ADDR 0x58

#define WIIMOTE_X_MAX 1023
#define WIIMOTE_X_MIN 0

#define WIIMOTE_Y_MAX 754
#define WIIMOTE_Y_MIN 0

#define WIIMOTE_I2C_CLOCK 400000

class wiiIRcam{
  public:

  uint16_t x1, x2, x3, x4;
  uint16_t y1, y2, y3, y4;

  void begin();
  void begin(uint8_t sensitivity);
  bool get();

  private:
  void write2byte(uint8_t a, uint8_t b);
  void writeNbyte(uint8_t n, uint8_t *a);
};