#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

FILE uart_file;

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

void timer1_init()
{
  //For measuring frequency only, the clearing of the ICF1 Flag is not required (if an interrupt handler is used).

  TCCR1B |= _BV(ICNC1); // ICNC1: Input Capture Noise Canceler
  TCCR1B |= _BV(CS12); // clkI/O/256 (From prescaler)
  TIMSK1  = _BV(ICIE1); //ICIE1: Timer/Counter1, Input Capture Interrupt Enable 
  sei();
}

volatile uint32_t last;
volatile uint32_t curr;

ISR(TIMER1_CAPT_vect){
    //When using the Input Capture interrupt, the ICR1 Register should be read as early in the interrupt handler routine as possible.
    last = curr;
    curr = ICR1;
}

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  
  timer1_init();
  while(1){
    sleep_cpu(); //nie ustawialismy zadnych bitow wiec jestesmy w trybie IDLE
    printf("Odczytana czestotliwosc: %"PRIu32"\r\n", 62500 / (curr - last));
    //printf("LAST: %"PRIu32", CURR: %"PRIu32"\r\n", last, curr);
  }
}