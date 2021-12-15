#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include "i2c.h"

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

#define TIME 1
#define DATE 2
#define STIME 3
#define SDATE 4

#define endl printf("\r\n");

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

const uint8_t eeprom_addr = 0b11010000;

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // zainicjalizuj I2C
  i2cInit();
  // program testowy
  #define i2cCheck(code, msg) \
    if ((TWSR & 0xf8) != (code)) { \
      printf(msg " failed, status: %.2x\r\n", TWSR & 0xf8); \
      i2cReset(); \
      continue; \
    }
  while(1) {

    uint8_t instruction;
    uint8_t minutes = 0;
    uint8_t seconds = 0;
    uint8_t hours = 0;
    uint8_t days = 0;
    uint8_t months = 0;
    uint8_t years = 0;
    uint8_t century = 0;

    const char* edu_message = "Type 1 to get time, type 2 to get date, type 3 to set time or type 4 to set date\r\n";
    printf( edu_message );
    while(1) {
        scanf( "%"PRIu8"", &instruction );
        printf( "You chose instruction no. %hhu", instruction);
        endl
        if( instruction == TIME ){
            while(1){
                i2cStart();
                i2cCheck(0x08, "I2C start");
                i2cSend(eeprom_addr);
                i2cCheck(0x18, "I2C EEPROM write")
                i2cSend(0x0);
                i2cCheck(0x28, "I2C EEPROM set")
                i2cStart();
                i2cCheck(0x10, "I2C second start")
                i2cSend( eeprom_addr | 0x1 );
                seconds = i2cReadAck();
                seconds = (10 * (( seconds & 0b1110000 ) >> 4) ) + ( seconds & 0b1111);
                i2cCheck(0x50, "I2C EEPROM read")
                minutes = i2cReadAck();
                minutes = (10 * (( minutes & 0b1110000 ) >> 4) )  + ( minutes & 0b1111);
                i2cCheck(0x50, "I2C EEPROM read request")
                hours = i2cReadNoAck();
                hours = (20 & (hours & 0b00100000)) + (10 & (hours & 0b10000)) + (hours & 0b1111);
                i2cCheck(0x58, "I2C EEPROM read request")
                i2cStop();
                i2cCheck(0xf8, "I2C stop")
                printf( "Now is %02hhuh:%02hhum:%02hhus\r\n", hours, minutes, seconds );
                break;
            }
        } else if ( instruction == DATE ){
            while(1){
                i2cStart();
                i2cCheck(0x08, "I2C start in read");
                i2cSend(eeprom_addr);
                i2cCheck(0x18, "I2C EEPROM write request")
                i2cSend(0x04);
                i2cCheck(0x28, "I2C EEPROM set address")
                i2cStart();
                i2cCheck(0x10, "I2C second start")
                i2cSend(eeprom_addr | 0x1);
                days = i2cReadAck();
                days = (10 * ((days & 0b110000) >> 4)) + (days & 0b1111);
                i2cCheck(0x50, "I2C EEPROM read request")
                months = i2cReadAck();
                century = months & 0b10000000;
                months = (10 * ((months & 0b00010000) >> 4)) + (months & 0b1111);
                i2cCheck(0x50, "I2C EEPROM read request")
                years = i2cReadNoAck();
                years = 10 * ((years & 0b11110000) >> 4) + (years & 0b1111);
                i2cCheck(0x58, "I2C EEPROM read request")
                i2cStop();
                i2cCheck(0xf8, "I2C stop")
                printf( "Now is %02hhud of %02hhum is year 2%1hhu%04hhu\r\n", days, century, months, years );
                break;
            }

        } else if ( instruction == STIME ){ 
          //scanf("%hhu", &hours);
          printf("%hhu", hours);
          scanf("%hhx %hhx %hhx", &hours, &minutes, &seconds);
          printf("%hhu", hours); endl
          printf("%hhx:%hhx:%hhx", hours, minutes, seconds); 
          endl
          // hours = (hours / 10) << 4 | (hours % 10);
          // minutes = (minutes / 10) << 4 | (minutes % 10);
          // seconds = (seconds / 10) << 4 | (seconds % 10);
          while(1){
            i2cStart();
            i2cCheck(0x08, "I2C start")
            i2cSend(eeprom_addr);
            i2cCheck(0x18, "I2C EEPROM write")
            i2cSend(0x0);
            i2cCheck(0x28, "I2C EEPROM write")
            i2cSend(seconds);
            i2cCheck(0x28, "I2C EEPROM set")
            i2cSend(minutes);
            i2cCheck(0x28, "I2C EEPROM set")
            i2cSend(hours);
            i2cCheck(0x28, "I2C EEPROM set")
            i2cStop();
            i2cCheck(0xf8, "I2C stop")
            break;
          }

        } else if ( instruction == SDATE ){

          while(1){
            scanf("%hhu %hhu %hhu", &years, &months, &days);
            printf("%hhu:%hhu:%hhu", years, months, days); 
            endl
            years = (years % 10) | ((years / 10) << 4);
            months = (months % 10) | ((months) / 10) << 4;
            days = (days % 10) | ((days / 10) << 4); 
            i2cStart();
            i2cCheck(0x08, "I2C start")
            i2cSend(eeprom_addr);
            i2cCheck(0x28, "I2C EEPROM set")
            i2cSend(0x04);
            i2cCheck(0x28, "I2C EEPROM write")
            i2cSend(days);
            i2cCheck(0x28, "I2C EEPROM set")
            i2cSend(months);
            i2cCheck(0x28, "I2C EEPROM set")
            i2cSend(years);
            i2cCheck(0x28, "I2C EEPROM set")
            i2cStop();
            i2cCheck(0xf8, "I2C stop")
          }

        } else 
            printf( edu_message );
    }
  }
}
