#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "esp_err.h"

void i2cDriverInit(void);
esp_err_t i2cDriverReadReg(uint8_t deviceAddr, uint8_t regAddr, uint8_t* data);
esp_err_t i2cDriverWriteReg(uint8_t deviceAddr, uint8_t regAddr, uint8_t data);