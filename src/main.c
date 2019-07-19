#include <string.h>

#include "utils.h"

#include "beep.h"
#include "digit.h"
#include "ds1302.h"
#include "uart.h"
#include "buttons.h"
#include "switch.h"

static void ds1302_to_digitnum_time(void) {
  u8 i;
  for (i = 0; i < 3; i++) {
    DigitNum[5 - 2 * i] = (Ds1302Time[i] & 0x0f) >> 0;
    DigitNum[5 - 2 * i - 1] = (Ds1302Time[i] & 0xf0) >> 4;
  }
}
static void ds1302_to_digitnum_date(void) {
  u8 i;
  for (i = 0; i < 2; i++) {
    DigitNum[3 - 2 * i] = (Ds1302Time[i + 3] & 0x0f) >> 0;
    DigitNum[3 - 2 * i - 1] = (Ds1302Time[i + 3] & 0xf0) >> 4;
  }
}
static void ds1302_to_digitnum_year(void) {
  DigitNum[0] = 2;
  DigitNum[1] = 0;
  DigitNum[2] = (Ds1302Time[6] & 0xf0) >> 4;
  DigitNum[3] = (Ds1302Time[6] & 0x0f) >> 0;
}
static void alarm_to_digitnum_time(u8 *alarm) {
  u8 i;
  for (i = 0; i < 2; ++i) {
    DigitNum[2 * i] = alarm[i] / 10;
    DigitNum[2 * i + 1] = alarm[i] % 10;
  }
}

static u8 is_digitnum_oclock(void) {
  return !(DigitNum[2] + DigitNum[3] + DigitNum[4]) && DigitNum[5] < 2;
}
static u8 is_alarm(u8 *alarm) {
  return (DigitNum[0] * 10 + DigitNum[1]) == alarm[0]
    && (DigitNum[2] * 10 + DigitNum[3]) == alarm[1]
    && DigitNum[4] == 0
    && DigitNum[5] < 2;
}

void main() {
  u8 i;
  u8 button1_pre = 0, button1_num = 0;
  u8 button2_pre = 0, button2_num = 0;
  u8 alarm[2] = {0, 0};
  DigitInit();
  Ds1302Init();
  BeepInit();
  UartInit();
  ButtonInit();
  SwitchInit();
  while (1) {
    if (Switch1 == 0) {
      if (UartArgc >= 8) {
        ES = 0;
        memcpy(Ds1302Time, NewTime, 7 * sizeof(u8));
        Ds1302WriteTime();
        ES = 1;
        UartArgc = 0;
      }
      Ds1302ReadTime();
      if (Button1 == 1 && Button2 == 1) {
        ds1302_to_digitnum_time();
        DigitShowTime();
      } else if (Button1 == 0) {
        ds1302_to_digitnum_date();
        DigitShowDate();
      } else {
        ds1302_to_digitnum_year();
        DigitShowDate();
      }
      if (is_digitnum_oclock() || is_alarm(alarm)) {
        for (i = 0; i < 100; ++i) {
          Beep = 1;
          delay_50us();
          Beep = 0;
          delay_50us();
        }
      }
    } else {
      if (Button1 ^ button1_pre) {
        button1_pre = Button1;
        ++button1_num;
        if (button1_num == 2) {
          button1_num = 0;
          ++alarm[0];
          if (alarm[0] == 24) {
            alarm[0] = 0;
          }
        }
      } else if (Button2 ^ button2_pre) {
        button2_pre = Button2;
        ++button2_num;
        if (button2_num == 2) {
          button2_num = 0;
          ++alarm[1];
          if (alarm[1] == 60) {
            alarm[1] = 0;
          }
        }
      }
      alarm_to_digitnum_time(alarm);
      DigitShowFixTime();
    }
  }
}
