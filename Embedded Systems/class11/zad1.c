#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

#include "pid.h"

/*! \brief P, I and D parameter values
 *
 * The K_P, K_I and K_D values (P, I and D gains)
 * need to be modified to adapt to the application at hand
 */
//! \xrefitem todo "Todo" "Todo list"
#define K_P     10.00
//! \xrefitem todo "Todo" "Todo list"
#define K_I     0.30
//! \xrefitem todo "Todo" "Todo list"
#define K_D     0.50

//! Parameters for regylator
struct PID_DATA pidData;

#define BUFSIZE 100

struct buffer {
  char tab[100];
  volatile uint16_t read_pos;
  volatile uint16_t write_pos;
  volatile uint16_t elements;
} input_buffer, output_buffer;

// struct buffer input_buffer;
// struct buffer output_buffer;

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
  ICR1 = 255;
  TCCR1A = _BV(COM1A1) | _BV(WGM11);
  TCCR1B = _BV(WGM12) | _BV(WGM13) 
  TCCR1B|= _BV(CS10) | _BV(CS12);
}

// inicjalizacja ADC
void adc_init()
{
  ADMUX   = _BV(REFS0)| _BV(REFS1); // referencja AVcc, wejście ADC0
  DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
  ADCSRA |= _BV(ADIE); // wlacz ADC interrupt
  DDRB   |= _BV(PB1);
}

FILE uart_file;

int main()
{
  // zainicjalizuj UART
  uart_init();
  adc_init();
  timer1_init();
  sei();
  
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;

  int16_t inputValue, measurmentValue, inpTemp;
  int16_t referenceValue;
  pid_Init(K_P * SCALING_FACTOR, K_I * SCALING_FACTOR , K_D * SCALING_FACTOR , &pidData);
  
  printf("Wpisz oczekiwana temperature\r\n");
  scanf("%hd", &inpTemp);

  referenceValue = ((inpTemp * 0.01 + 0.5) * 1024.0) / 1.1;
  printf("Oczekiwana temperatura: %hd\r\nOczekiwane ADC: %hd\r\n", inpTemp, referenceValue);
  while(1){
    ADCSRA |= _BV(ADSC); // wykonaj konwersję
    while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
    ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)

    measurmentValue = (int16_t)ADC;

    inputValue = pid_Controller(referenceValue, measurmentValue, &pidData);

    OCR1A = inputValue;
    printf("input value: %hd\r\n", inputValue);
    printf("Obecne ADC: %hd Oczekiwane ADC: %hd Obecna temp: %f\r\n", measurmentValue, referenceValue, (((float)measurmentValue * (1.1 / 1024.0)) - 0.5)/0.01);
  }
}