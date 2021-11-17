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

void timer1_init()
{
  // ustaw tryb licznika
  // WGM1  = 0000 -- normal
  // CS1   = 001  -- prescaler 1
  TCCR1B = _BV(CS10);
}
FILE uart_file;



int main()
{
  // zainicjalizuj UART
  uart_init();
  timer1_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  
  int x;
  volatile int8_t a; 
  volatile int8_t b;
  volatile int8_t res8;
  volatile int16_t c; 
  volatile int16_t d;
  volatile int16_t res16;
  volatile int32_t e; 
  volatile int32_t f;
  volatile int32_t res32;
  volatile int64_t g; 
  volatile int64_t h;
  volatile int64_t res64;
  volatile float i; 
  volatile float j;
  volatile float resf;
  volatile uint16_t cycles;

  printf("1 - int8_t, 2 - int16_t, 3 - int32_t, 4 - int64_t, 5 - float\r\n");
  scanf("%d", &x);
  printf("Odczytano: %d\r\nWpisz dwie liczby tego typu\r\n", x);

  switch (x)
  {
    case 1:
      scanf("%hhd %hhd", &a, &b);
      // printf("%hhd + %hhd = %hhd\r\n", a, b, a+b);
      TCNT1 = 0;
      res8 = a+b;
      cycles = TCNT1;
      printf("Liczba wykonanych cykli: %"SCNu16"\r\n", cycles);
      // printf("%hhd - %hhd = %hhd\r\n", a, b, a-b);
      TCNT1 = 0;
      res8 = a-b;
      cycles = TCNT1;
      printf("Liczba wykonanych cykli: %"SCNu16"\r\n", cycles);
      // printf("%hhd * %hhd = %hhd\r\n", a, b, a*b);
      TCNT1 = 0;
      res8 = a*b;
      cycles = TCNT1;
      printf("Liczba wykonanych cykli: %"SCNu16"\r\n", cycles);
      // printf("%hhd / %hhd = %hhd\r\n", a, b, a/b);
      TCNT1 = 0;
      res8 = a/b;
      cycles = TCNT1;
      printf("Liczba wykonanych cykli: %"SCNu16"\r\n", cycles);
      break;
    case 2:
      scanf("%"SCNd16" %"SCNd16, &c, &d);
      // printf("%"SCNd16" + %"SCNd16" = %"SCNd16"\r\n", c, d, c+d);
      TCNT1 = 0;
      res16 = c+d;
      cycles = TCNT1;
      printf("Liczba wykonanych cykli: %"SCNu16"\r\n", cycles);
      // printf("%"SCNd16" - %"SCNd16" = %"SCNd16"\r\n", c, d, c-d);
      TCNT1 = 0;
      res16 = c-d;
      cycles = TCNT1;
      printf("Liczba wykonanych cykli: %"SCNu16"\r\n", cycles);
      // printf("%"SCNd16" * %"SCNd16" = %"SCNd16"\r\n", c, d, c*d);
      TCNT1 = 0;
      res16 = c*d;
      cycles = TCNT1;
      printf("Liczba wykonanych cykli: %"SCNu16"\r\n", cycles);
      // printf("%"SCNd16" / %"SCNd16" = %"SCNd16"\r\n", c, d, c/d);
      TCNT1 = 0;
      res16 = c/d;
      cycles = TCNT1;
      printf("Liczba wykonanych cykli: %"SCNu16"\r\n", cycles);
      break;
    case 3:
      scanf("%"SCNd32" %"SCNd32, &e, &f);
      // printf("%"SCNd32" + %"SCNd32" = %"SCNd32"\r\n", e, f, e+f);
      TCNT1 = 0;
      res32 = e+f;
      cycles = TCNT1;
      printf("Liczba wykonanych cykli: %"SCNu16"\r\n", cycles);
      // printf("%"SCNd32" - %"SCNd32" = %"SCNd32"\r\n", e, f, e-f);
      TCNT1 = 0;
      res32 = e-f;
      cycles = TCNT1;
      printf("Liczba wykonanych cykli: %"SCNu16"\r\n", cycles);
      // printf("%"SCNd32" * %"SCNd32" = %"SCNd32"\r\n", e, f, e*f);
      TCNT1 = 0;
      res32 = e*f;
      cycles = TCNT1;
      printf("Liczba wykonanych cykli: %"SCNu16"\r\n", cycles);
      // printf("%"SCNd32" / %"SCNd32" = %"SCNd32"\r\n", e, f, e/f);
      TCNT1 = 0;
      res32 = e/f;
      cycles = TCNT1;
      printf("Liczba wykonanych cykli: %"SCNu16"\r\n", cycles);
      break;
    case 4:
      scanf("%ld %ld", &g, &h);
      // printf("%ld + %ld = %ld\r\n", g, h, g+h);
      TCNT1 = 0;
      res64 = g+h;
      cycles = TCNT1;
      printf("Liczba wykonanych cykli: %"SCNu16"\r\n", cycles);
      // printf("%ld - %ld = %ld\r\n", g, h, g-h);
      TCNT1 = 0;
      res64 = g-h;
      cycles = TCNT1;
      printf("Liczba wykonanych cykli: %"SCNu16"\r\n", cycles);
      // printf("%ld * %ld = %ld\r\n", g, h, g*h);
      TCNT1 = 0;
      res64 = g*h;
      cycles = TCNT1;
      printf("Liczba wykonanych cykli: %"SCNu16"\r\n", cycles);
      // printf("%ld / %ld = %ld\r\n", g, h, g/h);
      TCNT1 = 0;
      res64 = g/h;
      cycles = TCNT1;
      printf("Liczba wykonanych cykli: %"SCNu16"\r\n", cycles);
      break;
    case 5:
      scanf("%f %f", &i, &j);
      // printf("%f + %f = %f\r\n", i, j, i+j);
      TCNT1 = 0;
      resf = i+j;
      cycles = TCNT1;
      printf("Liczba wykonanych cykli: %"SCNu16"\r\n", cycles);
      // printf("%f --%f = %f\r\n", i, j, i-j);
      TCNT1 = 0;
      resf = i-j;
      cycles = TCNT1;
      printf("Liczba wykonanych cykli: %"SCNu16"\r\n", cycles);
      // printf("%f * %f = %f\r\n", i, j, i*j);
      TCNT1 = 0;
      resf = i*j;
      cycles = TCNT1;
      printf("Liczba wykonanych cykli: %"SCNu16"\r\n", cycles);
      // printf("%f / %f = %f\r\n", i, j, i/j);
      TCNT1 = 0;
      resf = i/j;
      cycles = TCNT1;
      printf("Liczba wykonanych cykli: %"SCNu16"\r\n", cycles);
      break;
  }
}
