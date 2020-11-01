#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

int cycle = 500;

char toggle_red()		/* always toggle! */
{
  static char state = 0;

  switch (state) {
  case 0:
    red_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 0;
    state = 0;
    break;
  }
  return 1;			/* always changes an led */
}

char toggle_green()	/* only toggle green if red is on!  */
{
  char changed = 0;
  if (red_on) {
    green_on ^= 1;
    changed = 1;
  }
  return changed;
}


void state_advance()		/* alternate between toggling red & green */
{
  char changed = 0;  

  static enum {R=0, G=1} color = G;
  switch (color) {
  case R: changed = toggle_red(); color = G; break;
  case G: changed = toggle_green(); color = R; break;
  }
  led_changed = changed;
  led_update();
}

void red_is_on()
{
  red_on = 1;
  led_changed = 1;
  led_update();
}

void red_off()
{
  red_on = 0;
  led_changed = 1;
  led_update();
}

void green_is_on()
{
  green_on = 1;
  led_changed = 1;
  led_update();
}

void green_off()
{
  green_on = 0;
  led_changed = 1;
  led_update();
}

void frequency_up()
{
  cycle += 225;
  buzzer_set_period(cycle);
}

void frequency_down()
{
  cycle -= 450;
  buzzer_set_period(cycle);
}

void siren_state()
{
  static int blink_count = 0;
  static char state = 0;
  switch(state){
  case 0:
    green_is_on();
    if(++blink_count % 15 == 0)
      {
	frequency_up();
      }
    if(cycle == 5000)
      {
	blink_count = 0;
	state = 1;
	green_off();
	red_is_on();
      }
    break;
  case 1:
    if(++blink_count % 15 == 0)
      {
	frequency_down();
      }
    if(cycle == 500)
      {
	blink_count = 0;
	state = 0;
	red_off();
	green_is_on();
      }
    break;
  }
}

  

