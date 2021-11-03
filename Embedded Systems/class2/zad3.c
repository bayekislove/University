#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>

#define LED_PORT PORTD

#define BTN_RESET PB0
#define BTN_PREV  PB1
#define BTN_NEXT  PB2

#define BTN_PIN PINB
#define BTN_PORT PORTB

#define MAX_GRAY 16

uint8_t convert_to_gray(uint8_t  num){
    return num ^ (num >> 1);
}

int main() {
    UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
    BTN_PORT = 0xff;  

    DDRD = 0xff;
    uint8_t decimal = 1;
    while(1){
        if(!(BTN_PIN & _BV(BTN_RESET))){
            _delay_ms(100);
            if(!(BTN_PIN & _BV(BTN_RESET))){
                decimal = 0;
            };
        }
        if(!(BTN_PIN & _BV(BTN_PREV))){
            _delay_ms(100);
            if(!(BTN_PIN & _BV(BTN_PREV))){
                decimal = (decimal-1) % MAX_GRAY;
            };
        }
        if(!(BTN_PIN & _BV(BTN_NEXT))){
            _delay_ms(100);
            if(!(BTN_PIN & _BV(BTN_NEXT))){
                decimal = (decimal+1) % MAX_GRAY;
            };
        }
        //LED_PORT = MAX_GRAY;
        LED_PORT = convert_to_gray(decimal);
    }
}