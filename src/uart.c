#include "uart.h"

#include "utils.h"

u8 UartArgc = 0;
u8 UartCmd;
u8 NewTime[7];

void UartInit(void) {
  T2H = 0xFD;
  T2L = 0xC0;
  AUXR = 0x15;
  SCON = 0x50;
  ES = 1;
  EA = 1;
}

void UartTimeInit(void) interrupt 4 {
  if (RI) {
    RI = 0;
    if (UartArgc == 0) {
      UartCmd = SBUF;
      ++UartArgc;
    } else {
      switch (UartCmd) {
      case 0x01:
        NewTime[UartArgc - 1] = SBUF;
        ++UartArgc;
        break;
      default:
        UartArgc = 0;
        break;
      }
    }
  }
}
