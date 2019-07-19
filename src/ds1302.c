#include "ds1302.h"

#include "utils.h"

sbit DSIO = P6 ^ 0;
sbit RST = P6 ^ 1;
sbit SCLK = P5 ^ 3;

const u8 code DS1302_READ_ADDR[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d};
const u8 code DS1302_WRITE_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};

u8 Ds1302Time[7] = {0x00, 0x00, 0x12, 0x12, 0x07, 0x04, 0x18};

u8 Ds1302Read(u8 addr) {
  u8 i, dat_tmp, dat = 0;
  RST = 0;
  SCLK = 0;
  RST = 1;
  for (i = 0; i < 8; ++i) {
    DSIO = addr & 0x01;
    addr >>= 1;
    SCLK = 1;
    SCLK = 0;
  }
  for (i = 0; i < 8; ++i) {
    dat_tmp = DSIO;
    dat = (dat >> 1) | (dat_tmp << 7);
    SCLK = 1;
    SCLK = 0;
  }
  RST = 0;
  SCLK = 1;
  DSIO = 0;
  DSIO = 1;
  return dat;
}
void Ds1302Write(u8 addr, u8 dat) {
  u8 i;
  RST = 0;
  SCLK = 0;
  RST = 1;
  for (i = 0; i < 8; ++i) {
    DSIO = addr & 0x01;
    addr >>= 1;
    SCLK = 1;
    SCLK = 0;
  }
  for (i = 0; i < 8; ++i) {
    DSIO = dat & 0x01;
    dat >>= 1;
    SCLK = 1;
    SCLK = 0;
  }
  RST = 0;
}

void Ds1302Init(void) {
  u8 is_read_allowed, i;
  is_read_allowed = Ds1302Read(0x81);
  if (is_read_allowed == 0x80) {
    Ds1302Write(0x8E, 0X00);
    for (i = 0; i < 7; ++i) {
      Ds1302Write(DS1302_WRITE_ADDR[i], Ds1302Time[i]);
    }
    Ds1302Write(0x8E, 0x80);
  }
}

void Ds1302ReadTime(void) {
  u8 i;
  for (i = 0; i < 7; i++) {
    Ds1302Time[i] = Ds1302Read(DS1302_READ_ADDR[i]);
  }
}
void Ds1302WriteTime(void) {
  u8 i;
  Ds1302Write(0x8E, 0X00);
  for (i = 0; i < 7; i++) {
    Ds1302Write(DS1302_WRITE_ADDR[i], Ds1302Time[i]);
  }
  Ds1302Write(0x8E, 0x80);
}
