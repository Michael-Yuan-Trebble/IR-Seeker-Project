#include <stdio.h>
#include <math.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"
#include "esp_system.h"
#include "esp_err.h"
#include "mlx90640API.h"
#include "mlx90640Driver.h"
#include "../components/thermalTask/thermalTask.h"

#define MLX90640_REFRESH_16HZ 5

void app_main(void)
{
    ESP_LOGI("MAIN", "IR Seeker main booting");

    MLX90640_I2CInit();

    uint16_t eeData[832];
    MLX90640_DumpEE(0x33, eeData);
    paramsMLX90640 tempParams;
    MLX90640_ExtractParameters(eeData, &tempParams);
    MLX90640_SetRefreshRate(0x33, MLX90640_REFRESH_16HZ);

    ThermalTaskInit();

    xTaskCreate(ThermalTaskStart, "ThermalTask", 8192, NULL, 5, NULL);
}