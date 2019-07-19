/** Only #include this file in one .c file */
#ifndef __STC_CLOCK__BEEP__
#define __STC_CLOCK__BEEP__

#include "utils.h"

sbit Beep = P0 ^ 6;
void BeepInit(void);

#endif  // !__STC_CLOCK__BEEP__
