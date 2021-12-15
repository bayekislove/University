/******************************************************************************
 * Header file inclusions.
 ******************************************************************************/

#include "FreeRTOS.h"
#include "task.h"

#include <avr/io.h>


#include <stdio.h>
#include "uart.h"
#include "queue.h"

/******************************************************************************
 * Private macro definitions.
 ******************************************************************************/

#define mainLED_TASK_PRIORITY   30

#define mainSERIAL_TASK_PRIORITY 1

/******************************************************************************
 * Private function prototypes.
 ******************************************************************************/

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

QueueHandle_t ipcQueue;

int main(void)
{
    // Create task.
    xTaskHandle blink_handle;
    xTaskHandle serial_handle;

    ipcQueue = xQueueCreate( 20, 2 ); //20 uint16_t elements -> each int is 2 bytes long

    xTaskCreate
        (
         vBlinkLed,
         "blink",
         200,
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
    uart_init();
    stdin = stdout = stderr = &uart_file;
    //printf("ASDA\r\n");
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
static void vBlinkLed(void* pvParameters)
{

    DDRB |= _BV(PB0);
    uint16_t received = 0;
    while(1)
    {
        if( xQueueReceive( ipcQueue, &received, 0 ) == pdPASS ){
            
            printf("Dostalem %hu\r\n", received);
            PORTB |= _BV(PB0);
            vTaskDelay(received / portTICK_PERIOD_MS);
            PORTB &= ~_BV(PB0);
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
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
    uint16_t input;

    while(1)
    {
        scanf("%hu", &input);
        printf("Wczytalem: %d\r\n", input);
        xQueueSend(ipcQueue, &input, 0);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}