#include "digit.h"

#include "utils.h"

const u8 code DIGIT_TABLE[10] = {  // clang-format off
  0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90
};  // clang-format on
const u8 code DIGIT_POS[4] = {0x10, 0x08, 0x04, 0x02};

u8 DigitNum[6];

static u8 second_pre = 0;
static u8 dot_status = 0;

static u8 get_second(void) {
  return 10 * DigitNum[4] + DigitNum[5];
}

void DigitInit(void) {
  P2M0 = 0X00;
  P2M1 = 0X00;
  P4M0 = 0X1E;
  P4M1 = 0X00;
}

void DigitShowTime(void) {
  u8 i;
  if (second_pre != get_second()) {
    second_pre = get_second();
    dot_status ^= 1;
  }
  for (i = 0; i < 4; ++i) {
    if (i == 1) {
      P2 = DIGIT_TABLE[DigitNum[i]] & ~(dot_status << 7);
    } else {
      P2 = DIGIT_TABLE[DigitNum[i]];
    }
    P4 = DIGIT_POS[i];
    delay_1ms();
  }
}
void DigitShowFixTime(void) {
  u8 i;
  for (i = 0; i < 4; ++i) {
    if (i == 1) {
      P2 = DIGIT_TABLE[DigitNum[i]] & 0x7f;
    } else {
      P2 = DIGIT_TABLE[DigitNum[i]];
    }
    P4 = DIGIT_POS[i];
    delay_1ms();
  }
}
void DigitShowDate(void) {
  u8 i;
  for (i = 0; i < 4; ++i) {
    P2 = DIGIT_TABLE[DigitNum[i]];
    P4 = DIGIT_POS[i];
    delay_1ms();
  }
}
