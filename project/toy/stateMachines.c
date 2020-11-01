#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"

char button_state;

void dim(){
  static char state = 0;

  switch(state){
  case 0:
    red_on = 1;
    green_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 0;
    green_on = 0;
    state = 0;
    break;
  }
  led_update();
}

void ring_up(){
  static long cycle = 5000;
  buzzer_set_period(cycle);
  cycle = cycle - 10;
  if(cycle == 0){
    cycle = 5000;
  }
}

void ring_down(){
  static long cycle = 0;
  buzzer_set_period(cycle);
  cycle = cycle + 10;
  if(cycle == 5000){
    cycle = 0;
  }
}

void main_state()
{
  switch(button_state){
  case 1:
    green_on = 1;
    red_on = 0;
    ring_up();
    break;
  case 2:
    green_on = 0;
    red_on = 1;
    ring_down();
    break;
  case 3:
    buzzer_set_period(0);
    dim();
    dim();
    break;
  case 4:
    buzzer_set_period(0);
    red_on = 0;
    green_on = 0;
  }
  led_changed = 1;
  led_update();
}
