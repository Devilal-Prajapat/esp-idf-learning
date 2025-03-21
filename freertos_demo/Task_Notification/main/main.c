#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define TAG "APP"

static TaskHandle_t task1;
static TaskHandle_t task2;

void vTask1( void * pvParameters)
{
    uint32_t count = 0;
    while (true)
    {
        printf("%s running\r\n",(char *)pvParameters);
        /*
            TaskNotify(xTaskToNotify,ulValue,eAction)
            typedef enum
            {
                eNoAction = 0,           
                eSetBits,                
                eIncrement,              
                eSetValueWithOverwrite,  
                eSetValueWithoutOverwrite
            } eNotifyAction;
        */

        xTaskNotify(task2, 1<<0, eSetBits);
        vTaskDelay(pdMS_TO_TICKS(100));
        xTaskNotify(task2, 1<<1, eSetBits);
        vTaskDelay(pdMS_TO_TICKS(100));
        xTaskNotify(task2, 1<<2, eSetBits);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
    vTaskDelete(NULL);   
}

void vTask2( void * pvParameters)
{
    while (true)
    {
        uint32_t  notify_val;
        if(xTaskNotifyWait(true, false, &notify_val, pdMS_TO_TICKS(100)))
        {
            printf("%s notify val: %ld\r\n",(char *)pvParameters, notify_val);
        }
        else
        {
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
    xTaskCreate(vTask2,"Task-2", 2*1024, "Task 2", 1, &task2);
    xTaskCreate(vTask1,"Task-1", 2*1024, "Task 1", 1, &task1);
   
}