#include <stdio.h>
#include "esp_log.h"

#define TAG "LOG"


void app_main(void)
{
    ESP_LOGE(TAG,"ERROR ");
    ESP_LOGW(TAG,"WARNING");
    ESP_LOGI(TAG,"INFO");
    ESP_LOGD(TAG,"DEBUG");
    ESP_LOGV(TAG,"VERBOSE");
}