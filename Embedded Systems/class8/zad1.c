/******************************************************************************
 * Header file inclusions.
 ******************************************************************************/

#include "FreeRTOS.h"
#include "task.h"

#include <avr/io.h>


#include <stdio.h>
#include "uart.h"

/******************************************************************************
 * Private macro definitions.
 ******************************************************************************/

#define mainLED_TASK_PRIORITY   1

#define mainSERIAL_TASK_PRIORITY 1

/******************************************************************************
 * Private function prototypes.
 ******************************************************************************/

#define LED_PORT2 PORTD
#define DELAY 400
#define LEDs_NUM 8

#define LED PB0
#define LED_DDR DDRB
#define LED_PORT PORTB

#define BTN PB1
#define BTN_PIN PINB
#define BTN_PORT PORTB

static void vBlinkLed(void* pvParameters);

static void vSerial(void* pvParameters);

/******************************************************************************
 * Public function definitions.
 ******************************************************************************/

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
    xTaskHandle blink_handle;
    xTaskHandle serial_handle;

    xTaskCreate
        (
         vBlinkLed,
         "blink",
         configMINIMAL_STACK_SIZE,
         NULL,
         mainLED_TASK_PRIORITY,
         &blink_handle
        );

    xTaskCreate
        (
         vSerial,
         "serial",
         200,
         NULL,
         mainSERIAL_TASK_PRIORITY,
         &serial_handle
        );

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

/**************************************************************************//**
 * \fn static void vBlinkLed(void* pvParameters)
 *
 * \brief
 *
 * \param[in]   pvParameters
 ******************************************************************************/
static void vBlinkLed(void* pvParameters){
    UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);  
    DDRD = 0xff;
    while (1) {
        for(int i = 0; i < LEDs_NUM; i++){
            LED_PORT2 = _BV(i);
            vTaskDelay(DELAY / portTICK_PERIOD_MS);
        }
        for(int i = LEDs_NUM - 2; i > 0; i--){
            LED_PORT2 = _BV(i);
            vTaskDelay(DELAY / portTICK_PERIOD_MS);
        }
    }
}

/**************************************************************************//**
 * \fn static void vSerial(void* pvParameters)
 *
 * \brief
 *
 * \param[in]   pvParameters
 ******************************************************************************/
static void vSerial(void* pvParameters)
{
    BTN_PORT |= _BV(BTN);
    LED_DDR |= _BV(LED);
    uint8_t circular_buffer[100] = {0};
    int i = 0;
    while (1) {
        LED_PORT |= _BV(LED);

        if( circular_buffer[i] == 1 ){
        LED_PORT &= ~_BV(LED);
        circular_buffer[i] = 0;
        }
        if (BTN_PIN & _BV(BTN)){
        circular_buffer[i] = 1;
        }
        i = (i+1) % 100;
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}
