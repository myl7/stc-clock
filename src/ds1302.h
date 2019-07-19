#ifndef __STC_CLOCK__DS1302__
#define __STC_CLOCK__DS1302__

#include "utils.h"

void Ds1302Init(void);

void Ds1302ReadTime(void);
void Ds1302WriteTime(void);
extern u8 Ds1302Time[7];

#endif  // !__STC_CLOCK__DS1302__
