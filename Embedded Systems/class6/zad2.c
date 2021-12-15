#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdio.h>
#include <inttypes.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

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
  // wyczyść rejestr UCSR0A
  UCSR0A = 0;
  // włącz odbiornik i nadajnik
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);
  // ustaw format 8n1
  UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

ISR(USART_RX_vect){
  input_buffer.tab[input_buffer.write_pos] = UDR0;
  input_buffer.write_pos = (input_buffer.write_pos + 1) % BUFSIZE;
  input_buffer.elements++;
}

ISR(USART_TX_vect){ }

ISR(USART_UDRE_vect){
  UDR0 = output_buffer.tab[output_buffer.read_pos];
  output_buffer.read_pos = (output_buffer.read_pos + 1) % BUFSIZE;
  output_buffer.elements--;

  if( output_buffer.elements == 0 ){
    UCSR0B &= ~_BV(UDRE0);
  }
}

// transmisja jednego znaku
int uart_transmit(char data, FILE *stream)
{
  // czekaj dopoki bufor pelny
  while( output_buffer.elements == BUFSIZE ) {};
  
  output_buffer.tab[output_buffer.write_pos] = data;
  output_buffer.write_pos = (output_buffer.write_pos + 1) % BUFSIZE;
  output_buffer.elements++;

  if( output_buffer.elements > 0 )
    UCSR0B |= _BV(UDRE0);
  
  return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream)
{
  // czekaj aż znak dostępny
  while( input_buffer.elements == 0 ) {};
  char k = input_buffer.tab[input_buffer.read_pos];
  input_buffer.read_pos = (input_buffer.read_pos + 1) % BUFSIZE;
  input_buffer.elements--;
  return k;
}

FILE uart_file;

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // program testowy

  UCSR0B |= _BV(RXCIE0);
  sei();

  input_buffer.read_pos = 0;
  input_buffer.elements = 0;
  input_buffer.write_pos = 0;

  output_buffer.read_pos = 0;
  output_buffer.elements = 0;
  output_buffer.write_pos = 0;

  printf("Hello world!\r\n");

  while(1) {
    char a = 1;
    putchar(getchar());
    //scanf("%c", &a);
    //printf("Odczytano: %c\r\n", a);
  }
}
