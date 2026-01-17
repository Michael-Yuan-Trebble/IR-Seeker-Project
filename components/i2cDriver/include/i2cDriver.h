#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

#include <stdint.h>
#include <stddef.h>
#include "driver/i2c_master.h"
#include "esp_err.h"

#define I2C_PORT I2C_NUM_0
#define I2C_SDA_PIN 21
#define I2C_SCL_PIN 22
#define I2C_FREQ_HZ 400000
#define I2C_TIMEOUT_MS 100

void i2cDriverInit(void);
esp_err_t i2cDriverReadReg(uint8_t deviceAddr, uint8_t regAddr, uint8_t* data);
esp_err_t i2cDriverWriteReg(uint8_t deviceAddr, uint8_t regAddr, uint8_t data);
void i2cAttachDevice(uint8_t deviceAddr);

#endif