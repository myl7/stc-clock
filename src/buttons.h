#ifndef __STC_CLOCK__BOTTUNS__
#define __STC_CLOCK__BOTTUNS__

#include "utils.h"

sbit Button1 = P0 ^ 4;
sbit Button2 = P5 ^ 2;

void ButtonInit(void);

#endif  // !__STC_CLOCK__BOTTUNS__
