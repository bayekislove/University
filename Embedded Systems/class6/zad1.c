#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

volatile uint8_t got;

ISR(USART_RX_vect){
  UDR0 = UDR0; //odczyt bajtu i przekierowanie bajtu na wyjscie
}

ISR(USART_TX_vect){ }

void init_interrupt(){
  UCSR0B = _BV(RXCIE0) | _BV(TXCIE0);
  sei();
}

int main() {
  init_interrupt()
  while(1){
    sleep_mode();
  }
}
