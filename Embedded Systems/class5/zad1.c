#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define LED PD2
#define LED_DDR DDRD
#define LED_PORT PORTD

#define BTN PD3
#define BTN_PIN PIND
#define BTN_PORT PORTD

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

// inicjalizacja UART
void uart_init()
{
  // ustaw baudrate
  UBRR0 = UBRR_VALUE;
  // wyczyść rejestr UCSR0A
  UCSR0A = 0;
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

void timer0_init(){
    //normal mode 
    TCCR0B = _BV(CS02); //prescaler 256
}

volatile uint8_t circular_buffer[244] = {0};
volatile int i = 0;

void init_interrupt(){
    TIMSK0 |= _BV(TOIE0);
    sei();
}

ISR(TIMER0_OVF_vect){
    LED_PORT &= ~_BV(LED);
    
    if( circular_buffer[i] == 1 ){
      LED_PORT |= _BV(LED);
      circular_buffer[i] = 0;
    }
    if (!(BTN_PIN & _BV(BTN))){
      circular_buffer[i] = 1;
    }
    i = (i + 1) % 244;
}

int main() {
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;

  BTN_PORT |= _BV(BTN);
  LED_DDR |= _BV(LED);
  set_sleep_mode(SLEEP_MODE_IDLE);
  timer0_init();
  init_interrupt();
           
  while(1){
    sleep_mode();
  }
}