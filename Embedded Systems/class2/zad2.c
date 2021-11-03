#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <string.h>

#define LED PB0
#define LED_DDR DDRB
#define LED_PORT PORTB

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

#define BTN PB1
#define BTN_PIN PINB
#define BTN_PORT PORTB

#define UNIT 5000
#define PRZYCISK 1
#define PRZERWA 0

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

void mignij_dioda_100ms(){
  LED_PORT |= _BV(LED);
  _delay_ms(100);
  LED_PORT &= ~_BV(LED);
};

int match_string(char* str1, char* str2){
  if(strlen(str1) != strlen(str2))
    return 0;
  for(int i = 0; i < strlen(str1); i++){
    if(str1[i] != str2[i]){
      return 0;
    }
  }
  return 1;
} 

int main() {
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;

  BTN_PORT |= _BV(BTN);
  LED_DDR |= _BV(LED);
  int liczbaZnakow;
  int wpisaneZnaki = 0;
  int znalezionoLiterke = 0;
  printf("%d\r\n", match_string(letter_to_morse_representation[0], ".-"));

  while (1) {    
    printf("Ile znakow w alfabecie Morse'a chcesz wpisac? \r\n");
    scanf("%d", &liczbaZnakow);
    printf("Wpisz %d znakow w alfabecie Morse'a.\r\n", liczbaZnakow);

    _delay_ms(1000); //czekamy sekunde zeby moc nacisnac przycisk
    printf("AAAAAAAAAAAAA");
    while ( (BTN_PIN & _BV(BTN)) ){ }//wciskamy pierwszy raz przycisk, zaczynami wpisywac kod morse'a

    char znakiMorsea[liczbaZnakow];
    int tryb_wprowadzania = PRZYCISK;

    while(wpisaneZnaki < liczbaZnakow){
      printf("WSZEDLEM PETLA\r\n");
      if( tryb_wprowadzania == PRZYCISK ){
        
        while( (BTN_PIN & _BV(BTN)) ){ } //czekamy az ktos wcisnie przycisk
        printf("Wszedlem tryb wprowadzania przycisk\r\n");
        _delay_ms(UNIT); //odmierzamy jednostke
        mignij_dioda_100ms(); //znak, ze odmierzylismy jednostke
        _delay_ms(300);

        if( (BTN_PIN & _BV(BTN)) ){
          printf("Odmierzono 1 przycisk\r\n");
          znakiMorsea[wpisaneZnaki] = '.';
        } else {
          printf("Odmierzono 3 przycisk\r\n");
          _delay_ms( 2 * UNIT - 100 ); //odmierzamy lacznie 3 jednostki
          znakiMorsea[wpisaneZnaki] = '-';
        }
      }
      if( tryb_wprowadzania == PRZERWA ){
        
        while( !(BTN_PIN & _BV(BTN) )){ } //czekamy az przecisk przestanie byc wcisniety
        printf("Wszedlem tryb wprowadzania przerwa\r\n"); 
        _delay_ms(UNIT);
        mignij_dioda_100ms(); //znak, ze odmierzylismy jednostke

        if( (BTN_PIN & _BV(BTN)) ){ //czyli 3 lub 7 jednostek, jesli nacisnelismy juz przycisk
          _delay_ms( 2 * UNIT - 100 ); //odmierzamy 3 jednostki
          mignij_dioda_100ms(); //znak, ze juz 3 jednostki minely

          if( !(BTN_PIN & _BV(BTN) )){ //przerwana przerwa, tzn 3 jednostki
            printf("Odmierzono 3 przerwa\r\n");
            znakiMorsea[wpisaneZnaki] = ' ';
          } else {
            _delay_ms( 4 * UNIT - 100 ); //znak, ze juz odmierzono 7 jednostek lacznie
            mignij_dioda_100ms();
            printf("Odmierzono 7 przerwa\r\n");
            znakiMorsea[wpisaneZnaki] = '|';
          } 
        } else {
          printf("Odmierzono 1 przerwa\r\n");
          wpisaneZnaki--;
        }
      }
      mignij_dioda_100ms(); //zmiana ktora znaczy zmiane trybu wprowadzania
      tryb_wprowadzania = (tryb_wprowadzania == PRZERWA) ? PRZYCISK : PRZERWA;
      wpisaneZnaki++;
    }
    //printf("%s????\r\n", znakiMorsea);
    //printf("WLAZLEM W ROZSZYFROWYWANIE\r\n");
    //printf("Liczba znakow: %d\r\n", liczbaZnakow);
    int rozmiarSlowa = 0;
    for(int idx = 0; idx < liczbaZnakow; idx++){
      //printf("ZNAK DO ROZPOZNANIA: %c\r\n", znakiMorsea[idx]);
      switch (znakiMorsea[idx])
      {
      case '.':
        rozmiarSlowa++;
        break;
      case '-':
        rozmiarSlowa++;
        break;
      case '|':
        printf(" ");
        break;
      case ' ': ;
        char literka[rozmiarSlowa+1];
        literka[rozmiarSlowa] = '\0';
        //printf("rozmiar slowa to: %d\r\n", rozmiarSlowa);
        for(int i = 0; i < rozmiarSlowa; i++){
          literka[i] = znakiMorsea[idx - rozmiarSlowa + i];
        }
        //printf("SZUKANE SLOWO TO:%s\r\n", literka);
        znalezionoLiterke = 0;
        for(int i = 0; (i < 27) && !znalezionoLiterke; i++){
          //printf("%d\r\n", i);
          if( match_string(literka, letter_to_morse_representation[i]) ){
            printf("%c", 97 + i);
            znalezionoLiterke = 1;
          }
        }
        if(!znalezionoLiterke){
          printf("!!!NIE ROZPOZNANO ZNAKU!!!\r\n");
        } else {
          znalezionoLiterke = 0;
        }
        rozmiarSlowa = 0;
        break;
      }
    }
    printf("\r\n");
  }
}