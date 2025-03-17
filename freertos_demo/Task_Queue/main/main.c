#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#define TAG "APP"

static TaskHandle_t task1;
static TaskHandle_t task2;
QueueHandle_t myqueue;

void vTask1( void * pvParameters)
{
    uint32_t xmillis = pdMS_TO_TICKS(1000);
    uint32_t tick_cnt;
    uint32_t count = 0;
    while (true)
    {
        count++;
        if(xQueueSend(myqueue, (uint32_t*)&count,pdMS_TO_TICKS(100)))
        {
            printf("Send Success from %s\r\n",(char *)pvParameters);
        }
        else
        {
            printf("Send Failed from %s\r\n",(char *)pvParameters);
        }
        tick_cnt = xTaskGetTickCount();
        vTaskDelayUntil(&tick_cnt,xmillis);
    }
    vTaskDelete(NULL);   
}

void vTask2( void * pvParameters)
{
    uint32_t data;
    while (true)
    {
        if(xQueueReceive(myqueue,&data,pdMS_TO_TICKS(1000)))
        {
            printf("Received: %ld in %s\r\n",data, (char *)pvParameters);
        }
        else
        {
            printf("Receive timeout: %s\r\n",(char *)pvParameters);
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
    myqueue = xQueueCreate(3,sizeof(uint32_t));
    xTaskCreate(vTask2,"Task-2", 2*1024, "Task 2", 1, &task2);
    xTaskCreate(vTask1,"Task-1", 2*1024, "Task 1", 1, &task1);
   
}