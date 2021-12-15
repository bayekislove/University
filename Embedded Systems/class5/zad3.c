#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

#define LED PB0
#define LED_DDR DDRB
#define LED_PORT PORTB

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

// inicjalizacja ADC
void adc_init()
{
  ADMUX  =  _BV(REFS0); //| _BV(REFS1);
  ADMUX  |= 0b1110; //czyscimy bity MUX
  DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
}

FILE uart_file;

float calculate_average(float measurment[]){
    uint8_t len = 200;
    float sum = 0;
    for(uint8_t i = 0; i < len; i++){
        sum += measurment[i];
    }
    //printf("%f\r\n", sum);
    return sum / len;
}

float calculate_variance(float measurment[], float average){
    uint8_t len = 200;
    float sum = 0;
    for(uint8_t i = 0; i < len; i++){
        sum += (measurment[i] - average)*(measurment[i] - average);
    }
    return sum / (float)len;
}

void ADC_noise_reduction_setup(){
    SMCR = _BV(SM0); //set mode DC Noise Reduction
    ADCSRA |= _BV(ADIE); // ADC Interrupt Enable
    sei();
}

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // zainicjalizuj ADC
  adc_init();
  // mierz napięcie

  LED_DDR |= _BV(LED);
  while(1) {
    float measurment[200] = {0.0};
    uint8_t len = 200;
    for(uint8_t i = 0; i < len; i++){
        //printf("%d\r\n", i);
        ADCSRA |= _BV(ADSC); // wykonaj konwersję
        while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
        ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
        measurment[i] = 1126.4 / ADC; // wyliczamy napiecie wejsciowe ze wzoru z podrecznika
    }
    float average = calculate_average(measurment);
    printf("Wariancja dla pomiarow ADC z aktywnym czekaniem: %f \r\n", calculate_variance(measurment, average));
    
    //If an enabled interrupt occurs while the MCU is in a sleep mode, the MCU wakes up. The MCU is then halted for
    //four cycles in addition to the start-up time, executes the interrupt routine, 
    //and resumes execution from the instruction following SLEEP.
    ADC_noise_reduction_setup();
    for(uint8_t i = 0; i < len; i++){
        sleep_cpu(); //stad bedziemy wybudzeni przerwaniem ADC Conversion Complete
        measurment[i] = 1126.4 / ADC; // wyliczamy napiecie wejsciowe ze wzoru z podrecznika
    }
    average = calculate_average(measurment);
    printf("Wariancja dla pomiarow ADC Noise Reduction: %f \r\n", calculate_variance(measurment, average));
  }
}