#include <msp430.h>
#include "stateMachines.h"

char button_state;

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char blink_count = 0;
  if(++blink_count == 1){
    main_state();
    blink_count = 0;
  }
}
