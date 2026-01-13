#include "thermalTask.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_system.h"
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "mlx90640API.h"
#include "mlx90640Driver.h"

paramsMLX90640 mlxParams;
uint16_t mlxFrame[834];
uint16_t eeData[832];
float image[768];

float emissivity = 1.f;
float Ta = 25.f;

void ThermalTaskInit(void)
{
    if (MLX90640_DumpEE(0x33, eeData) != 0) {
        ESP_LOGI("THERMAL", "Failed to dump EEPROM data");
        return;
    }
    MLX90640_ExtractParameters(eeData, &mlxParams);
}

// TEMP RANGES ROUGHLY -40C TO 300C
// BEST RANGES ARE 0 to 100

void ThermalTaskStart(void* pvParameters)
{
    while(1){
        if (MLX90640_GetFrameData(0x33, mlxFrame) >= 0) {
            MLX90640_CalculateTo(mlxFrame, &mlxParams, emissivity, Ta, image);
            float maxTemp = -1000.f;
            int maxIdx = 0;
            for (int i = 0; i < 768; i++) {
                if (image[i] > maxTemp) {
                    maxTemp = image[i];
                    maxIdx = i;
                }
            }

            if (maxTemp < MINIMUM_TEMP || maxTemp > MAXIMUM_TEMP) {
                ESP_LOGI("THERMAL", "Max Temp out of range: %.2f C", maxTemp);
                continue;
            }

            if (maxTemp >= 60.f)
            {
                ESP_LOGI("THERMAL", "Max Temp: %.2f C at Index: %d", maxTemp, maxIdx);
                int row = maxIdx / 32;
                int col = maxIdx % 32;
            } 
        } 
        else 
        {
            ESP_LOGI("THERMAL", "Failed to get frame data");
        }
        // 16Hz refresh rate delay
        vTaskDelay(pdMS_TO_TICKS(62.5)); 
    }
}

void ThermalTaskStop(void)
{
    // Code to stop the thermal task
}