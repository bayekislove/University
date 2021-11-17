#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <util/delay.h>
#include <time.h>

#include <math.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

#define RLED PD6
#define ROCR OCR0A

#define GLED PB1
#define GOCR OCR1A

#define BLED PB3
#define BOCR OCR2A

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

void timer0_init()
{
  TCCR0A = _BV(WGM00) | _BV(COM0A1) | _BV(COM0A0);
  TCCR0B = _BV(CS00);
  DDRD |= _BV(RLED);
  PORTD |= _BV(RLED);
}

void timer1_init()
{
  TCCR1A = _BV(WGM10) | _BV(COM1A1) | _BV(COM1A0);
  TCCR1B =_BV(CS10);
  DDRB |= _BV(GLED);
  PORTB |= _BV(GLED);
}

void timer2_init()
{
  TCCR2A = _BV(WGM20) | _BV(COM2A1) | _BV(COM2A0);
  TCCR2B =_BV(CS20);
  DDRB |= _BV(BLED);
  PORTB |= _BV(BLED);
}

void hsv_to_rgb( uint8_t rgb[3], uint8_t h, uint8_t s, uint8_t v ){

    int reg = h / 43;
    int rem = (h - (reg * 43)) * 6;
    int a = (v * (255 - s)) >> 8;
    int b = (v * (255 - ((s * rem) >> 8))) >> 8;
    int c = (v * (255 - ((s * (255 - rem)) >> 8))) >> 8;

    switch( reg )
    {
        case 0:
            rgb[0] = v;
            rgb[1] = c;
            rgb[2] = a;
            break;
        case 1:
            rgb[0] = b;
            rgb[1] = v;
            rgb[2] = a;
            break;
        case 2:
            rgb[0] = a;
            rgb[1] = v;
            rgb[2] = c;
            break;
        case 3:
            rgb[0] = a;
            rgb[1] = b;
            rgb[2] = v;
            break;
        case 4:
            rgb[0] = c;
            rgb[1] = a;
            rgb[2] = v;
            break;
        case 5:
            rgb[0] = v;
            rgb[1] = a;
            rgb[2] = b;
            break;
    }
}

const float sinus[91] = { 0.0, 0.017, 0.035, 0.052, 0.07, 0.087, 0.105, 0.122, 0.139, 0.156, 0.174, 0.191, 0.208, 0.225, 0.242, 0.259, 0.276, 0.292, 0.309, 0.326, 0.342, 0.358, 0.375, 0.391, 0.407, 0.423, 0.438, 0.454, 0.469, 0.485, 0.5, 0.515, 0.53, 0.545, 0.559, 0.574, 0.588, 0.602, 0.616, 0.629, 0.643, 0.656, 0.669, 0.682, 0.695, 0.707, 0.719, 0.731, 0.743, 0.755, 0.766, 0.777, 0.788, 0.799, 0.809, 0.819, 0.829, 0.839, 0.848, 0.857, 0.866, 0.875, 0.883, 0.891, 0.899, 0.906, 0.914, 0.921, 0.927, 0.934, 0.94, 0.946, 0.951, 0.956, 0.961, 0.966, 0.97, 0.974, 0.978, 0.982, 0.985, 0.988, 0.99, 0.993, 0.995, 0.996, 0.998, 0.999, 0.999, 1.0, 1.0 };

FILE uart_file;

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;

  timer0_init();
  timer1_init();
  timer2_init();

  srand( time(0) );
  // mierz napięcie
  ROCR = 0;
  GOCR = 0;
  BOCR = 0;
  while(1) {
      uint8_t hrand = rand() % 256; //dostajemy losowa liczbe z przedialu 0-255
      printf("rand: %hhu\r\n", hrand);
      uint8_t rgb[3];
      hsv_to_rgb( rgb, hrand, 255, 255 );
      printf("r: %hhu, G: %hhu, B: %hhu\r\n", rgb[0], rgb[1], rgb[2]);

      for(uint8_t i = 0; i < 90; i++){
        ROCR = 1 << (((uint8_t)(rgb[0] * sinus[i])) >> 5);
        GOCR = 1 << (((uint8_t)(rgb[1] * sinus[i])) >> 5);
        BOCR = 1 << (((uint8_t)(rgb[2] * sinus[i])) >> 5);
        printf("r: %u, G: %u, B: %f\r\n", 2 << (((uint8_t)(rgb[0] * sinus[i])) >> 5), 2 << (((uint8_t)(rgb[1] * sinus[i])) >> 5), 2 << (((uint8_t)(rgb[2] * sinus[i])) >> 5));
      }
      printf("ASDA\r\n");
      for(uint8_t i = 0; i < 90; i++){
        ROCR = 1 << (((uint8_t)(rgb[0] * sinus[90-i])) >> 5);
        GOCR = 1 << (((uint8_t)(rgb[1] * sinus[90-i])) >> 5);
        BOCR = 1 << (((uint8_t)(rgb[2] * sinus[90-i])) >> 5);
        printf("r: %d, G: %d, B: %d\r\n", 2 << (((int)(rgb[0] * sinus[90-i])) >> 5), 2 << (((int)(rgb[1] * sinus[90-i])) >> 5),  2 << (((int)(rgb[2] * sinus[90-i])) >> 5));
        //_delay_ms(1000);
      }
  }
}
