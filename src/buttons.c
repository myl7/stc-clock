#include "buttons.h"

#include "utils.h"

void ButtonInit(void) {
  P0M0 = 0X00;
  P0M1 = 0X00;
  P5M0 = 0x00;
  P5M1 = 0x00;
}
