#include <avr/io.h>
#include <stdio.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

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

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  
  int x;
  int8_t a; 
  int8_t b;
  int16_t c; 
  int16_t d;
  int32_t e; 
  int32_t f;
  int64_t g; 
  int64_t h;
  float i; 
  float j;

  printf("1 - int8_t, 2 - int16_t, 3 - int32_t, 4 - int64_t, 5 - float\r\n");
  scanf("%d", &x);
  printf("Odczytano: %d\r\nWpisz dwie liczby tego typu\r\n", x);


  switch (x){
    case 1:
      scanf("%hhd %hhd", &a, &b);
      printf("%hhd + %hhd = %hhd\r\n", a, b, a+b);
      printf("%hhd - %hhd = %hhd\r\n", a, b, a-b);
      printf("%hhd * %hhd = %hhd\r\n", a, b, a*b);
      printf("%hhd / %hhd = %hhd\r\n", a, b, a/b);
      break;
    case 2:
      scanf("%"SCNd16" %"SCNd16, &c, &d);
      printf("%"SCNd16" + %"SCNd16" = %"SCNd16"\r\n", c, d, c+d);
      printf("%"SCNd16" - %"SCNd16" = %"SCNd16"\r\n", c, d, c-d);
      printf("%"SCNd16" * %"SCNd16" = %"SCNd16"\r\n", c, d, c*d);
      printf("%"SCNd16" / %"SCNd16" = %"SCNd16"\r\n", c, d, c/d);
      break;
    case 3:
      scanf("%"SCNd32" %"SCNd32, &e, &f);
      printf("%"SCNd32" + %"SCNd32" = %"SCNd32"\r\n", e, f, e+f);
      printf("%"SCNd32" - %"SCNd32" = %"SCNd32"\r\n", e, f, e-f);
      printf("%"SCNd32" * %"SCNd32" = %"SCNd32"\r\n", e, f, e*f);
      printf("%"SCNd32" / %"SCNd32" = %"SCNd32"\r\n", e, f, e/f);
      break;
    case 4:
      scanf("%ld %ld", &g, &h);
      printf("%ld + %ld = %ld\r\n", g, h, g+h);
      printf("%ld - %ld = %ld\r\n", g, h, g-h);
      printf("%ld * %ld = %ld\r\n", g, h, g*h);
      printf("%ld / %ld = %ld\r\n", g, h, g/h);
      break;
    case 5:
      scanf("%f %f", &i, &j);
      printf("%f + %f = %f\r\n", i, j, i+j);
      printf("%f --%f = %f\r\n", i, j, i-j);
      printf("%f * %f = %f\r\n", i, j, i*j);
      printf("%f / %f = %f\r\n", i, j, i/j);
      break;
  }
}
