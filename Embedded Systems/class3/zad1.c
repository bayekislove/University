#include <avr/io.h>
#include <avr/pgmspace.h>

#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <inttypes.h>
#include <stdio.h>

#define BUZZ PB5
#define BUZZ_DDR DDRB
#define BUZZ_PORT PORTB

#define A 0
#define H 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define Ab 7
#define Fup 8

#define WHOLE   0
#define HALF    1
#define QUARTER 2
#define EIGTH   3

const int NoteToHz[] = {440,494,261,293,330,349,391,415,698};
const int NoteToLength[] = {4000,2000,1000,500};

#define TONE(step, delay) \
    for (uint16_t i = 0; i < (uint32_t)1000 * (delay) / (step) / 2; i++) { \
      BUZZ_PORT |= _BV(BUZZ); \
      _delay_us(step); \
      BUZZ_PORT &= ~_BV(BUZZ); \
      _delay_us(step); \
    }

const uint8_t melody[] PROGMEM = {
  A, QUARTER,
  A, QUARTER,
  A, QUARTER,
  E, EIGTH,
  C, EIGTH,
  A, QUARTER,
  E, EIGTH,
  C, EIGTH,
  A, HALF,
  E, QUARTER,
  E, QUARTER,
  E, QUARTER,
  Fup, EIGTH,
  C, EIGTH,
  Ab, QUARTER,
  F, EIGTH,
  C, EIGTH,
  A, HALF
};

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

// inicjalizacja UART
void uart_init()
{
  // ustaw baudrate
  UBRR0 = UBRR_VALUE;
  // włącz odbiornik i nadajnik
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);
  // ustaw format 8n1
  UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

// transmisja jednego znaku
int uart_transmit(char data, FILE *stream)
{
  // czekaj aż transmiter gotowy
  while(!(UCSR0A & _BV(UDRE0)));
  UDR0 = data;
  return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream)
{
  // czekaj aż znak dostępny
  while (!(UCSR0A & _BV(RXC0)));
  return UDR0;
}

FILE uart_file;

//Hz = 1/s -> s = 1/Hz
int main() {
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;

  BUZZ_DDR |= _BV(BUZZ);
  int hz; int len;

  while (1) {
    for(uint8_t i = 0; i < sizeof(melody); i += 2){
      //printf("Przeczytalem hz: %d, przeczytalem len %d \r\n", NoteToHz[pgm_read_byte(&melody[i])], pgm_read_byte(&melody[i + 1]));
      hz = NoteToHz[pgm_read_byte(&melody[i])];
      len = NoteToLength[pgm_read_byte(&melody[i + 1])] / 2;
      //printf("Hz to: %d, len: %d \r\n", hz, len);
      TONE(1000000/hz, len);
      _delay_us(len*100);
    }
  }
}