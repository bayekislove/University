#include "FreeRTOS.h"
#include "task.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "uart.h"
#include "queue.h"
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#ifndef BAUD
#define BAUD 9600
#endif
#include <util/setbaud.h>

int uart_transmit(char c, FILE *stream);
int uart_receive(FILE *stream);

FILE uart_file = FDEV_SETUP_STREAM(uart_transmit, uart_receive, _FDEV_SETUP_RW);
QueueHandle_t input_buffer;
QueueHandle_t output_buffer;

uint16_t input_elements;
uint16_t output_elements;

#define BUFSIZE 50

void uart_init() {
  input_buffer = xQueueCreate(BUFSIZE, 1);
  output_buffer = xQueueCreate(BUFSIZE, 1);
  input_elements = 0;
  output_elements = 0;

  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;
#if USE_2X
  UCSR0A |= _BV(U2X0);
#else
  UCSR0A &= ~(_BV(U2X0));
#endif
  UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
  UCSR0B = _BV(RXEN0) | _BV(TXEN0); /* Enable RX and TX */
  UCSR0B |= _BV(RXCIE0);
  sei();
}

ISR(USART_RX_vect){
  uint8_t k = UDR0;
  while( xQueueSendFromISR( input_buffer, &k, 0 ) != pdPASS) {}
  input_elements++;
}

ISR(USART_UDRE_vect){
  uint8_t k;
  uint8_t res;
  if( (res = xQueueReceiveFromISR( output_buffer, &k, 20 )) == pdPASS ){
    UDR0 = k;
    output_elements--;
  } else if ( res == errQUEUE_EMPTY ){
    UCSR0B &= ~_BV(UDRE0); 
  }
}

int uart_transmit(char c, FILE *stream) {
  // czekaj dopoki bufor pelny
  while( xQueueSend(output_buffer, &c, 0) != pdPASS ) { };
  
  output_elements++;
  if( output_elements > 0 )
    UCSR0B |= _BV(UDRE0);
}

int uart_receive(FILE *stream) {
  char k;
  // // czekaj aż znak dostępny
  while( xQueueReceive(input_buffer, &k, 20) != pdPASS ) {};

  input_elements--;
  return k;
}