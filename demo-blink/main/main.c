#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define TAG "LOG"

#define LED    2

void gpio_init(){
    gpio_config_t led_config = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = 1 << LED
    };
    gpio_config(&led_config);
}

void app_main(void)
{
    // gpio_set_direction(LED,GPIO_MODE_OUTPUT);
    gpio_init();
    uint32_t led_state = 0;
    while ( true)
    {   
        ESP_LOGI(TAG,"LED Blink at 0.5 Second Interval");
        led_state = !led_state;
        gpio_set_level(LED,led_state);
        vTaskDelay(500/portTICK_PERIOD_MS);
    }
}