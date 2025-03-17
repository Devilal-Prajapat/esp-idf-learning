#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define TAG "APP"


void vTask1( void * pvParameters)
{
    while (true)
    {
        printf("Task 1 running\r\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    vTaskDelete(NULL);   
}

void vTask2( void * pvParameters)
{

    while (true)
    {
        printf("Task 2 running\r\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    vTaskDelete(NULL);   
}

void app_main(void)
{
    ESP_LOGI(TAG,"Freertos task example");
    /* xTaskCreate(
        TaskFunction_t pxTaskCode, 
        const char *const pcName, 
        const uint32_t usStackDepth, 
        void *const pvParameters, 
        UBaseType_t uxPriority, 
        TaskHandle_t *const pxCreatedTask
        )
    */
    xTaskCreate(vTask1,"Task-1", 2*1024, NULL, 2, NULL);
    xTaskCreate(vTask2,"Task-2", 2*1024, NULL, 2, NULL);
}