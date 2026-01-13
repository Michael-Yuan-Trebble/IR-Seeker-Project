#include "i2cDriver.h"

#include <math.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/i2c_master.h"
#include "esp_log.h"

#define I2C_PORT I2C_NUM_0
#define I2C_SDA_PIN 21
#define I2C_SCL_PIN 22
#define I2C_FREQ_HZ 400000
#define I2C_TIMEOUT_MS 100

static i2c_master_bus_handle_t bus_handle;

void i2cDriverInit(void){
    i2c_master_bus_config_t bus_config = {
        .i2c_port = I2C_NUM_0,
        .sda_io_num = I2C_SDA_PIN,
        .scl_io_num = I2C_SCL_PIN,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, &bus_handle));
}

static i2c_master_dev_handle_t mlxDev;

void i2cAttachDevice(uint8_t deviceAddr)
{
    i2c_device_config_t device_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = deviceAddr,
        .scl_speed_hz = I2C_FREQ_HZ,
    };

    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &device_config, &mlxDev));
}

esp_err_t i2cDriverReadReg(uint8_t deviceAddr, uint8_t regAddr, uint8_t* data)
{
    return i2c_master_transmit_receive(
        mlxDev,
        &regAddr, 1,
        data, 1,
        pdMS_TO_TICKS(I2C_TIMEOUT_MS)
    );
}

esp_err_t i2cDriverWriteReg(uint8_t deviceAddr, uint8_t regAddr, uint8_t data)
{
    uint8_t buf[2] = {regAddr, data};
    return i2c_master_transmit(
        mlxDev,
        buf, sizeof(buf),
        pdMS_TO_TICKS(I2C_TIMEOUT_MS)
    );
}