#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include "i2c.h"

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

#define WRITE 1
#define READ 2

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

const uint8_t eeprom_addr = 0xa0;

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
  uint16_t addr = 0;

  #define i2cCheck(code, msg) \
    if ((TWSR & 0xf8) != (code)) { \
      printf(msg " failed, status: %.2x\r\n", TWSR & 0xf8); \
      i2cReset(); \
      continue; \
    }
  uint8_t instruction;
  uint8_t written_value;
  uint8_t read_value;
  const char* edu_message = "Type 1 for write, type 2 for read\r\n";
  printf( edu_message );
  while(1) {
    scanf( "%"PRIu8"", &instruction );
    printf("Input command address: ", instruction);
    scanf( "%"PRIu16"", &addr );
    endl
    if( instruction == WRITE ){
        
      printf("What value do you want to write to EEPROM? ");
      scanf( "%"PRIu8"", &written_value );
      endl
	    i2cStart();
	    i2cCheck(0x08, "I2C start")
	    i2cSend(eeprom_addr | ((addr & 0x100) >> 7));
	    i2cCheck(0x18, "I2C EEPROM write request")
	    i2cSend(addr & 0xff);
	    i2cCheck(0x28, "I2C EEPROM set address")
	    i2cSend(written_value);
	    i2cCheck(0x28, "I2C EEPROM write")
	    i2cStop();
	    i2cCheck(0xf8, "I2C stop")
      printf("You can find value %"PRIu8" on %"PRIu16" address\r\n", written_value, addr);

    } else if ( instruction == READ ){

      i2cStart();
	    i2cCheck(0x08, "I2C start");
	    i2cSend(eeprom_addr | ((addr & 0x100) >> 7));
	    i2cCheck(0x18, "I2C EEPROM write request")
	    i2cSend(addr & 0xff);
	    i2cCheck(0x28, "I2C EEPROM set address")
    	i2cStart();
	    i2cCheck(0x10, "I2C second start")
	    i2cSend(eeprom_addr | 0x1 | ((addr & 0x100) >> 7));
	    i2cCheck(0x40, "I2C EEPROM read request")
	    read_value = i2cReadNoAck();
	    i2cStop();
	    i2cCheck(0xf8, "I2C stop")
	    printf("I found %"PRIu8" on address %"PRIu16"\r\n", read_value, addr);

    } else
      printf( "%s", edu_message );
    }
}
