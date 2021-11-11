#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "ws2812.h"
#include "hsv_rgb.h"

#define MAX_STATE 360

uint8_t colors[3];

uint16_t state = 0;

int main() {
  DDRB = 1<<PB4;

  // main loop
  while(1) {
    state = (state+1)%MAX_STATE;

    getRGB(state, 200, colors);

    // Allow changes to the clock prescaler
    CLKPR = 1<<CLKPCE;
    //  CLKPR[3:0] sets the clock division factor, set it to x/2, so 4.8MHz
    CLKPR = 1;

    cli();
    ws2812_set_single(colors[0], colors[1], colors[2]);
    sei();

    _delay_ms(100);

    // Allow changes to the clock prescaler
    CLKPR = 1<<CLKPCE;
    //  CLKPR[3:0] sets the clock division factor, set it to no scale, so 9.6MHz
    CLKPR = 0;

  }
  return 0;
}
