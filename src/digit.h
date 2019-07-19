#ifndef __STC_CLOCK__DIGIT__
#define __STC_CLOCK__DIGIT__

#include "utils.h"

void DigitInit(void);

/**
 * Show four numbers on digital screen
 *
 * @param num Array containing 6 numbers, including hour, minute and second, to
 * be shown on digital screen. For example, num = {1, 2, 3, 4, 5, 6} will show
 * "12:34" on screen, and the number of seconds is 56.
 */
void DigitShowTime(void);
void DigitShowFixTime(void);
void DigitShowDate(void);
extern u8 DigitNum[6];

#endif  // !__STC_CLOCK__DIGIT__
