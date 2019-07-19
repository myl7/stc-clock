#ifndef __STC_CLOCK__SWITCH__
#define __STC_CLOCK__SWITCH__

#include "utils.h"

sbit Switch1 = P0 ^ 0;
sbit Switch2 = P0 ^ 1;
sbit Switch3 = P0 ^ 2;
sbit Switch4 = P0 ^ 3;

void SwitchInit(void);

#endif  // !__STC_CLOCK__SWITCH__
