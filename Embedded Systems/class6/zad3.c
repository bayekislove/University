#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include <stdio.h>
#include <inttypes.h>

#include "zad3.h"

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

volatile int counter = 0;

// inicjalizacja SPI
void spi_init()
{
    // ustaw piny MOSI, SCK i ~SS jako wyjścia
    DDRB |= _BV(DDB3) | _BV(DDB5) | _BV(DDB2);
    // włącz SPI w trybie master z zegarem 250 kHz
    SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPR1);
}

// transfer jednego bajtu
uint8_t spi_transfer(uint8_t data)
{
    // rozpocznij transmisję
    SPDR = data;
    // czekaj na ukończenie transmisji
    while (!(SPSR & _BV(SPIF)));
    // wyczyść flagę przerwania
    SPSR |= _BV(SPIF);
    // zwróć otrzymane dane
    return SPDR;
}

void install_sample(int8_t sample){
    PORTB &= ~_BV( DDB2 ); //bit na niski ->  No data can be transferred into the device with CS high.
    spi_transfer( (0b0111 << 4) | (sample >> 4) );
    spi_transfer( sample << 4 );
    PORTB |= _BV( DDB2 ); //bit na wysoki
}

void timer0_init(){
    TCCR0A = _BV(WGM01); //CTC, TOP in OCRA
    TCCR0B = _BV(CS01);  //clkI/O/8 (From prescaler) 
    OCR0A = 124;         //wyliczenia mam na kartce

    TIMSK0 = _BV(OCIE0A); //Timer/Counter0 Compare Match A
}

ISR(TIMER0_COMPA_vect){
    install_sample( pgm_read_word( &samples[counter] ) - 127 );
    counter++;
    if (counter == 20000 + 1)
        counter = 0;
}

int main()
{
    // zainicjalizuj UART
    uart_init();
    // skonfiguruj strumienie wejścia/wyjścia
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;
    // zainicjalizuj SPI
    spi_init();
    timer0_init();
    sei(); 

    while(1){ };  
}
