#include "switch.h"

#include "utils.h"

void SwitchInit(void) {
  P0M0 = 0x00;
  P0M1 = 0x00;
}
