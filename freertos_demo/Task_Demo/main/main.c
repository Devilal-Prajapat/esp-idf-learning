#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define TAG "APP"

void vTask1( void * pvParameters)
{
    while (true)
    {
        printf("%s running\r\n",(char *)pvParameters);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    vTaskDelete(NULL);   
}

void vTask2( void * pvParameters)
{

    while (true)
    {
        printf("%s running\r\n",(char *)pvParameters);
        vTaskDelay(pdMS_TO_TICKS(2000));
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
    xTaskCreate(vTask1,"Task-1", 2*1024, "Task 1", 1, NULL);
    xTaskCreate(vTask2,"Task-2", 2*1024, "Task 2", 2, NULL);
}