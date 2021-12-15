#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <avr/interrupt.h>

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

// inicjalizacja ADC
void adc_init()
{
  ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
  DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
  ADCSRA |= _BV(ADATE); // ADC Auto Trigger Enable
  ADCSRA |= _BV(ADIE); // ADC Interrupt Enable
  ADCSRB |= _BV(ADTS1); //External Interrupt Request 0
}

FILE uart_file;

uint32_t r = 0;

void button_interrupt_setup(){
    EICRA |= _BV(ISC00) | _BV(ISC01);   // ustaw wyzwalanie przerwania na INT0 zboczem narastajacym
    EIMSK |= _BV(INT0);                 // odmaskuj przerwania dla INT0
}

ISR(INT0_vect){ }

ISR(ADC_vect){
  r = 220.0 * ((1024.0 - (float)ADC) / (float)ADC) ;
}

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  
  adc_init();
  PORTD |= _BV(PD2); // pull up
  button_interrupt_setup();
  sei();
  while(1) {    
    printf("Odczytany opor fotorezystora: %"PRIu32", ADC: %"PRIu16"\r\n", r, ADC);
  }
}