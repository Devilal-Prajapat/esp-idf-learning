#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define TAG "APP"

static TaskHandle_t task1;
static TaskHandle_t task2;

void vTask1( void * pvParameters)
{
    while (true)
    {
        printf("%s running\r\n",(char *)pvParameters);
        xTaskNotifyGive(task2);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    vTaskDelete(NULL);   
}

void vTask2( void * pvParameters)
{

    while (true)
    {
        uint32_t  notify_val = ulTaskNotifyTake(true, pdMS_TO_TICKS(1000));
        if(notify_val != 0)
        {
            printf("%s notify val: %ld\r\n",(char *)pvParameters, notify_val);
        }
        else{
            printf("Notify Timeout\r\n");
        }
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
    xTaskCreate(vTask2,"Task-2", 2*1024, "Task 2", 2, &task2);
    xTaskCreate(vTask1,"Task-1", 2*1024, "Task 1", 1, &task1);
   
}