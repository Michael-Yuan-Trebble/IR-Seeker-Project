#include "thermalTask.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_system.h"
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "mlx90640API.h"
#include "mlx90640Driver.h"
#include "tracker.h"
#include "telemetry.h"

#define MLX90640_REFRESH_16HZ 5

paramsMLX90640 mlxParams;
uint16_t mlxFrame[834];
static float image[768];
static TrackerResult trackerResult;
float emissivity = 1.f;
float Ta = 25.f;

void ThermalTaskInit(void)
{
    uint16_t eeData[832];
    if (MLX90640_DumpEE(0x33, eeData) != 0) 
    {
        ESP_LOGI("THERMAL", "Failed to dump EEPROM data");
        return;
    }
    if (MLX90640_ExtractParameters(eeData, &mlxParams) != 0) 
    {
        ESP_LOGI("THERMAL", "Failed to extract parameters");
        return;
    }
    if (MLX90640_SetRefreshRate(0x33, MLX90640_REFRESH_16HZ) != 0) 
    {
        ESP_LOGI("THERMAL", "Failed to set refresh rate");
        return;
    }
}

// TEMP RANGES ROUGHLY -40C TO 300C
// BEST RANGES ARE 0 to 100

void ThermalTaskStart(void* pvParameters)
{
    while(1)
    {
        if (MLX90640_GetFrameData(0x33, mlxFrame) >= 0) 
        {
            MLX90640_CalculateTo(mlxFrame, &mlxParams, emissivity, Ta, image);
            for (int i = 0; i < 768; i++)
            {
                if (image[i] < MINIMUM_TEMP) image[i] = MINIMUM_TEMP;
                if (image[i] > MAXIMUM_TEMP) image[i] = MAXIMUM_TEMP;
            }

            // Tracker Calculates
            TrackerUpdate(image, &trackerResult);

            // Telemetry Sends
            TelemetrySend(&trackerResult);

        } 
        else ESP_LOGI("THERMAL", "Failed to get frame data");

        // 16Hz refresh rate delay
        vTaskDelay(pdMS_TO_TICKS(62.5)); 
    }
}

void ThermalTaskStop(void)
{
    // Code to stop the thermal task
}