#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <inttypes.h>
#include <util/delay.h>

#include "pid.h"

/*! \brief P, I and D parameter values
 *
 * The K_P, K_I and K_D values (P, I and D gains)
 * need to be modified to adapt to the application at hand
 */
//! \xrefitem todo "Todo" "Todo list"
#define K_P     5.00
//! \xrefitem todo "Todo" "Todo list"
#define K_I     0.60
//! \xrefitem todo "Todo" "Todo list"
#define K_D     1.20

//! Parameters for regylator
struct PID_DATA pidData;

#define BUFSIZE 100

#define ADCONE ADMUX |= _BV(MUX0); ADCSRA |= _BV(ADSC);

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
  TCCR1A = _BV(COM1A1);
  TCCR1B = _BV(WGM13);
  TCCR1B|= _BV(CS10) | _BV(CS12);
  TIMSK1 = _BV(ICIE1) | _BV(TOIE1);
}

// inicjalizacja ADC
void adc_init()
{
  ADMUX   = _BV(REFS0)| _BV(REFS1); // referencja AVcc, wejście ADC0
  DIDR0   = _BV(ADC0D) | _BV(ADC1D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADIE); // wlacz ADC interrupt
  ADCSRA |= _BV(ADEN); // włącz ADC
  DDRB   |= _BV(PB1);
}

void timer1_init(){
  TCCR1A = _BV(COM1A1); // Clear OC1A/OC1B on Compare Match, set OC1A/OC1B at BOTTOM
  TCCR1B = _BV(WGM13); // PWM, Phase and Frequency Correct (Mode 8)
  TCCR1B |= _BV(CS11);
  ICR1 = 1023; // top
  TIMSK1 =  _BV(ICIE1);
}

ISR(ADC_VECT){
  if(curr_state == POT){
    adc_potentiometr = ADC;
  } else {
    ADMUX &= ~_BV(MUX0);
    ADCSRA |= _BV(ADSC);
    if(curr_state == CLOSED)
      adc_closed = ADC;
    else(curr_state == OPEN)
      adc_open = ADC;
    curr_state = POT;
  }
}

ISR(TIMER1_OVF_VECT){
  curr_state = OPEN;
  ADCONE;
}

ISR(TIMER1_CAPT_VECT){
  curr_state = CLOSED;
  ADCONE;
}

FILE uart_file;

//! Parameters for regylator
struct PID_DATA pidData;

uint16_t adc_open, adc_closed, adc_potentiometr;

enum ADC_TYPE{POT, OPEN, CLOSED};

uint8_t curr_state;

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

  pid_Init(K_P * SCALING_FACTOR, K_I * SCALING_FACTOR , K_D * SCALING_FACTOR , &pidData);
  int16_t inputValue;
  while(1){
    inputValue = pid_Controller(adc_closed, adc_potentiometr, &pidData);
    OCR1A = inputValue;

    printf("ADC_CLOSED: %hu ADC_OPEN: %hu ADC_POT: %hu\r\n", adc_closed, adc_open, adc_potentiometr);
    printf("PID: %hd\r\n\r\n", inputValue);
  }
}
