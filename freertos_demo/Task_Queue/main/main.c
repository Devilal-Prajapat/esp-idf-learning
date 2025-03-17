#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#define TAG "APP"

static TaskHandle_t task1;
static TaskHandle_t task2;
QueueHandle_t myqueue;

typedef struct __mydata{
    uint32_t id;
    char buff[16];
}mydata;

void vTask1( void * pvParameters)
{
    uint32_t xmillis = pdMS_TO_TICKS(1000);
    uint32_t tick_cnt;
    uint32_t count = 1;
    mydata my_data = {0};
    while (true)
    {
        count++;
        sprintf(my_data.buff, "id %ld", (count%5));
        my_data.id = count;
        if(xQueueSend(myqueue, &my_data,pdMS_TO_TICKS(100)))
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
    mydata my_data;
    while (true)
    {
        if(xQueueReceive(myqueue,&my_data,pdMS_TO_TICKS(1000)))
        {
            printf("Received: id %ld and buff: %s in %s\r\n",my_data.id, my_data.buff, (char *)pvParameters);
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
    myqueue = xQueueCreate(3,sizeof(mydata));
    xTaskCreate(vTask2,"Task-2", 2*1024, "Task 2", 1, &task2);
    xTaskCreate(vTask1,"Task-1", 2*1024, "Task 1", 1, &task1);
   
}