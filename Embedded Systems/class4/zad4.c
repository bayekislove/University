#include <avr/io.h>
#include <util/delay.h>

#define DETPIN PB0
#define LEDPIN PB1
#define RESPIN PB5

void timer1_init()
{
  // ustaw tryb licznika
  // COM1A = 10   -- non-inverting mode
  // COM1A = 11   -- inverting mode
  // WGM1  = 1110 -- fast PWM top=ICR1
  // CS1   = 101  -- prescaler 1024
  // ICR1  = 15624

  TCCR1A |= _BV(COM1A0); //Toggle OC1A/OC1B on Compare Match.
  TCCR1B |= _BV(WGM12); //CTC
  TCCR1B |= _BV(CS10); //clkI/O/1 (No prescaling)
  // str 126 -> 37900 = (16000000)/(1*(1+TOP)) -> TOP = 421 // 2 = 210
  OCR1A = 210;

  DDRB |= _BV(RESPIN); 
  DDRB &= ~_BV(DETPIN);
}

int main()
{
  // uruchom licznik
  timer1_init();

  while(1){
    DDRB |= _BV(LEDPIN);
    _delay_us(600);
    PORTB = (PORTB & _BV( DETPIN ) ) ? ( PORTB | _BV( RESPIN ) ) : ( PORTB & ~_BV( RESPIN ) );
    DDRB &= ~_BV(LEDPIN);
    _delay_us(100);
  }
}
