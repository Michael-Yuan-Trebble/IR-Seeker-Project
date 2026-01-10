#include <stdio.h>
#include <math.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"
#include "esp_system.h"
#include "esp_err.h"
#include "esp_timer.h"

#include "driver/i2c.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "driver/adc.h"

#include "../components/I2C/i2cDriver.h"
#include "../components/MLX90640/mlx90640Driver.h"

mlx90640_device_t mlx90640Dev;

void app_main(void)
{
    ESP_LOGI("MAIN", "IR Seeker main booting");

    i2cDriverInit();
    mlx90640Init(&mlx90640Dev);
}