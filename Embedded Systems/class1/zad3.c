#include <avr/io.h>
#include <util/delay.h>

#define LED_PORT PORTD
#define DELAY 1000
#define __BV(bit) (1 << (bit))
#define LEDs_NUM 8

int main() {
  UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);  
  DDRD = 0xff;
  while (1) {
    for(int i = 0; i < LEDs_NUM; i++){
      LED_PORT = __BV(i);
      _delay_ms(DELAY); 
    }
    for(int i = LEDs_NUM - 2; i > 0; i--){
      LED_PORT = __BV(i);
      _delay_ms(DELAY); 
    }
  }
}