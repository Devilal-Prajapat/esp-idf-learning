#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "calc.h"
#define TAG "APP"

void app_main(void)
{
    ESP_LOGI(TAG,"Component Demo");
    printf("sum : %d\n",add(5,10));

} 