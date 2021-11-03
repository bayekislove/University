#include <avr/io.h>
#include <util/delay.h>

#define LED PB0
#define LED_DDR DDRB
#define LED_PORT PORTB

#define BTN PB1
#define BTN_PIN PINB
#define BTN_PORT PORTB

int main() {
  BTN_PORT |= _BV(BTN);
  LED_DDR |= _BV(LED);
  uint8_t circular_buffer[100] = {0};
  int i = 0;
  while (1) {
    LED_PORT |= _BV(LED);

    if( circular_buffer[i] == 1 ){
      LED_PORT &= ~_BV(LED);
      circular_buffer[i] = 0;
    }
    if (BTN_PIN & _BV(BTN)){
      circular_buffer[i] = 1;
    }
    i = (i+1) % 100;
    _delay_ms(10);
  }
}