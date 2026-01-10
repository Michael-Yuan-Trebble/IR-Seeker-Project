#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "esp_err.h"

esp_err_t mlx90640Init(mlx90640_device_t* dev);
void mlx90640Task(void *pvParameters);
esp_err_t mlx90640ReadReg(uint8_t regAddr, uint8_t* data);
esp_err_t mlx90640WriteReg(uint8_t regAddr, uint8_t data);
esp_err_t mlx90640ReadRegs(uint8_t regAddr, uint8_t* buf, size_t len);