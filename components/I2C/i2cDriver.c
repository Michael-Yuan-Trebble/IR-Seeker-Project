#include "i2cDriver.h"

#include <math.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/i2c.h"
#include "esp_log.h"

#define I2C_PORT I2C_NUM_0
#define I2C_SDA_PIN 21
#define I2C_SCL_PIN 22
#define I2C_FREQ_HZ 400000
#define I2C_TIMEOUT_MS 100

void i2cDriverInit(void){
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_SDA_PIN,
        .scl_io_num = I2C_SCL_PIN,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_FREQ_HZ,
    };
    ESP_ERROR_CHECK(i2c_param_config(I2C_PORT, &conf));
    ESP_ERROR_CHECK(i2c_driver_install(I2C_PORT, conf.mode, 0, 0, 0));
}

esp_err_t i2cDriverReadReg(uint8_t deviceAddr, uint8_t regAddr, uint8_t* data)
{
    return i2c_master_write_read_device(
        I2C_PORT,
        deviceAddr,
        &regAddr, 1,
        data, 1,
        pdMS_TO_TICKS(I2C_TIMEOUT_MS)
    );
}

esp_err_t i2cDriverWriteReg(uint8_t deviceAddr, uint8_t regAddr, uint8_t data)
{
    uint8_t buf[2] = {regAddr, data};
    return i2c_master_write_to_device(
        I2C_PORT,
        deviceAddr,
        buf, 2,
        pdMS_TO_TICKS(I2C_TIMEOUT_MS)
    );
}