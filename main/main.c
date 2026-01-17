#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"
#include "esp_system.h"
#include "esp_err.h"

#include "mlx90640API.h"
#include "mlx90640Driver.h"
#include "tracker.h"
#include "thermalTask.h"
#include "servoController.h"
#include "buttonTask.h"

void app_main(void)
{
    ESP_LOGI("MAIN", "IR Seeker main booting");

    MLX90640_I2CInit();
    ThermalTaskInit();
    TrackerInit();
    ButtonTaskInit();
    ServoInit();

    ButtonTaskConfigure();
    xTaskCreate(ThermalTaskStart, "ThermalTask", 8192, NULL, 5, NULL);
}