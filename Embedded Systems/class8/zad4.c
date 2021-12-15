/******************************************************************************
 * Header file inclusions.
 ******************************************************************************/

#include "FreeRTOS.h"
#include "task.h"

#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdio.h>
#include "uart.h"
#include "semphr.h"

/******************************************************************************
 * Private macro definitions.
 ******************************************************************************/

/******************************************************************************
 * Private function prototypes.
 ******************************************************************************/

static void vBlinkLed(void* pvParameters);

static void vSerial(void* pvParameters);

static void vADCPotentiometr(void* pvParameters);
static void vADCPhotoresistor(void* pvParameters);
static void vADCThermoresistor(void* pvParameters);


/******************************************************************************
 * Public function definitions.
 ******************************************************************************/

// inicjalizacja ADC
void adc_init()
{
  ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
  /*When an analog signal is applied to the
    ADC5...0 pin and the digital input from this pin is not needed, this bit should be written logic one to reduce power
    consumption in the digital input buffer */
  DIDR0   = _BV(ADC0D) | _BV(ADC1D) | _BV(ADC2D); // wyłącz wejście cyfrowe na ADC0,ADC1,ADC2
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN) | _BV(ADIE); // włącz ADC
}

SemaphoreHandle_t adc_sem;
SemaphoreHandle_t io_sem;
SemaphoreHandle_t read_sem;

ISR( ADC_vect ){
    xSemaphoreGiveFromISR( adc_sem, 0 ); //TODO
    //printf("AAA\r\n");
}

uint16_t readADC( uint8_t mux ){
    ADMUX = _BV(REFS0) | mux;
    ADCSRA |= _BV(ADSC); //Bit 6 – ADSC: ADC Start Conversion
    //printf("CCCCC\r\n");
    xSemaphoreTake( adc_sem, portMAX_DELAY );
    //printf("WZIALEM ADC\r\n");
    uint16_t res =  ADC;
    //printf("A%"PRIu16"\r\n", res);
    return res;
}

/**************************************************************************//**
 * \fn int main(void)
 *
 * \brief Main function.
 *
 * \return
 ******************************************************************************/
int main(void)
{
    // Create task.
    xTaskHandle adc_photoresistor_handle;
    xTaskHandle adc_thermistor_handle;
    xTaskHandle adc_potentiometr_handle;

    adc_sem = xSemaphoreCreateBinary();
    //xSemaphore(adc_sem);

    io_sem = xSemaphoreCreateBinary();
    xSemaphoreGive(io_sem);

    read_sem = xSemaphoreCreateBinary();
    xSemaphoreGive(read_sem);

    xTaskCreate
        (
         vADCPhotoresistor,
         "photoresistor",
         300,
         NULL,
         1,
         &adc_photoresistor_handle
        );

    xTaskCreate
        (
         vADCThermoresistor,
         "thermoresistor",
         300,
         NULL,
         1,
         &adc_thermistor_handle
        );

    xTaskCreate
        (
         vADCPotentiometr,
         "potentiometr",
         300,
         NULL,
         1,
         &adc_potentiometr_handle
        );
        
    adc_init();
    uart_init();
    sei();
    stdin = stdout = stderr = &uart_file;

    if(adc_sem == NULL || io_sem == NULL || read_sem == NULL){
        printf("KTORYS Z SEMAFOROW UTWORZONY NIEPOPRAWNIE\r\n");
    }
    // Start scheduler.
    vTaskStartScheduler();

    return 0;
}

/**************************************************************************//**
 * \fn static vApplicationIdleHook(void)
 *
 * \brief
 ******************************************************************************/
void vApplicationIdleHook(void)
{

}

/******************************************************************************
 * Private function definitions.
 ******************************************************************************/

static void vADCThermoresistor(void* pvParameters)
{
    uint16_t res;
    while(1){
        //printf("JESTEM\r\n");
        xSemaphoreTake( read_sem, portMAX_DELAY );
        //printf("WZIALEM READA\r\n");
        res = readADC(0);
        //printf("MAM WYNIK ADC\r\n");
        xSemaphoreGive( read_sem );
        //printf("ODDALEM READA\r\n");
        xSemaphoreTake(io_sem, portMAX_DELAY);//If INCLUDE_vTaskSuspend is set to '1' then specifying the block time as portMAX_DELAY will cause the task to block indefinitely (without a timeout).
        printf( "Wartosc ADC z termorezystora: %"PRIu16"\r\n", res );
        //xSemaphoreGive( read_sem );
        xSemaphoreGive(io_sem);
        vTaskDelay(7000 / portTICK_PERIOD_MS);
    }
}

static void vADCPhotoresistor(void* pvParameters)
{
    uint16_t res;
    while(1){
        //printf("JESTEM\r\n");
        xSemaphoreTake( read_sem, portMAX_DELAY );
        //printf("WZIALEM READA\r\n");
        res = readADC(1);
        xSemaphoreGive( read_sem );
        xSemaphoreTake( io_sem, portMAX_DELAY );//If INCLUDE_vTaskSuspend is set to '1' then specifying the block time as portMAX_DELAY will cause the task to block indefinitely (without a timeout).
        printf( "Wartosc ADC z fotorezystora: %"PRIu16"\r\n", res );
        xSemaphoreGive( io_sem );
        //xSemaphoreGive( read_sem );
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

static void vADCPotentiometr(void* pvParameters)
{
    uint16_t res;
    while(1){
        //printf("JESTEM\r\n");
        xSemaphoreTake( read_sem, portMAX_DELAY );
        //printf("WZIALEM READA\r\n");
        res = readADC(2);
        xSemaphoreGive( read_sem );
        xSemaphoreTake( io_sem, portMAX_DELAY );//If INCLUDE_vTaskSuspend is set to '1' then specifying the block time as portMAX_DELAY will cause the task to block indefinitely (without a timeout).
        printf( "Wartosc ADC z potencjometru: %"PRIu16"\r\n", res );
        xSemaphoreGive( io_sem );
        //xSemaphoreGive( read_sem );;
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}