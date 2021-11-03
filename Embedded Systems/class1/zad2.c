#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>

#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <string.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem
#define UNIT 2000

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

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

void turn_off(int ms){
  LED_PORT &= ~_BV(LED);
  if(ms != -1){
    _delay_ms(ms);
  }
}

void turn_on(int ms){
  LED_PORT |= _BV(LED);
  _delay_ms(ms);
}

//przeklad liczb na kod morse'a -> https://en.wikipedia.org/wiki/Morse_code#/media/File:International_Morse_Code.svg
char* letter_to_morse_representation[] = {
  ".-",
  "-...",
  "-.-.",
  "-..",
  ".",
  "..-.",
  "--.",
  "....",
  "..",
  ".---",
  "-.-",
  ".-..",
  "--",
  "-.",
  "---",
  ".--.",
  "--.-",
  ".-.",
  "...",
  "-",
  "..-",
  "...-",
  ".--",
  "-..-",
  "-.--",
  "--.."
};

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // program testowy
  // printf("A!\r\n");
  // while(1) {
  //   char a = 1;
  //   scanf("%c", &a);
  //   printf("Odczytano: %c\r\n", a);
  // }
  LED_DDR |= _BV(LED);
  int size;
  printf("Wpisz liczbe znakow w twoim tekscie: ");
  scanf("%d", &size);
  printf("%d", size);
  char text[size + 1];
  scanf("%c", &text[0]);
  printf("\r\n");

  for(int i = 1; i < size + 1; i++){
    scanf("%c", &text[i]);
    printf("\r\n%c %d\r\n", text[i], i);
  }

  for(int i = 1; i < size + 1; i++){
    char curr_char = text[i];
    printf("Wszedlem\r\n");
    if( curr_char == ' '){
      printf("Wszedlem spacja\r\n");
      turn_off( 7 * UNIT );
    }
    if( curr_char >= 65 && curr_char <= 90 ){
      printf("Wszedlem duza literka\r\n");
      curr_char += 32;
    }
    if( curr_char >= 97 && curr_char <= 122 ){
      printf("Wszedlem mala literka\r\n");
      char* morsed = letter_to_morse_representation[curr_char - 97];
      printf("\r\nPrzetlumaczony string %s\r\n", morsed);
      printf("Rozmiar %d\r\n", strlen(morsed));
      
      for(int i = 0; i < strlen(morsed); i++ ){
        if( morsed[i] == '.'){
          printf("Wszedlem kropka\r\n");
          turn_on( UNIT );
        }
        if( morsed[i] == '-' ){
          printf("Wszedlem kreska\r\n");
          turn_on( 3 * UNIT );
        }
        if( i < strlen(morsed) - 1 ){
          printf("Wszedlem przerwa miedzy znakami literek\r\n");
          turn_off( UNIT );
        }
      }

      if ( i < size && text[i+1] != ' ' ){ //przerwa miedzy slowami
        printf("Wszedlem przerwa miedzy literkami\r\n\r\n");
        turn_off( 3 * UNIT );
      }
    }
  }
  printf("Wyszedlem\r\n");
  turn_off(-1);
}