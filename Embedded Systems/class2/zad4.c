#include <avr/io.h>
#include <util/delay.h>

#define LED_PORT PORTD
#define DELAY 1000
#define __BV(bit) (1 << (bit))

const int numbers[] = {
    0x3F, //0
    0x06, //1
    0x5B, //2
    0x4F, //3
    0x66, //4
    0x6D, //5
    0x7D, //6
	0x07, //7
    0x7F, //8
	0x6F  //9
};

int main(){
    UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
    DDRC = 0xff;
    DDRD = 0xff;
    while(1){
        for( int i = 0; i < 6; i++ ){
            for( int j = 0; j < 10; j++ ){
                for( int _ = 0; _ < 50; _++ ){
                    PORTC = 0b10;
                    LED_PORT = ~numbers[i];
                    _delay_ms(10);
                    PORTC = 0b1;
                    LED_PORT = ~numbers[j];
                    _delay_ms(10);
                }
            }
        }
    }
}