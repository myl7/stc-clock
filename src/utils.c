#include "utils.h"

void delay_ijk(u8 i_, u8 j_, u8 k_) {
  u8 i, j, k;
  for (i = i_; i > 0; --i)
  for (j = j_; j > 0; --j)
  for (k = k_; k > 0; --k);
}
void delay_50us(void) {
  delay_ijk(7, 3, 5);
}
void delay_1ms(void) {
  delay_ijk(2, 6, 248);
}
