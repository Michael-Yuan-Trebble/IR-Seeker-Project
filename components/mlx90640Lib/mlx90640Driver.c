#include "mlx90640Driver.h"
#include "esp_err.h"
#include "esp_log.h"
#include "driver/i2c.h"
#include "i2cDriver.h"
#include "mlx90640API.h"

#define SDA_PIN 21
#define SCL_PIN 22

// MLX90640 I2C address
#define DEVICEADDRESS 0x33

void MLX90640_I2CInit(void)
{
    i2cDriverInit();
    i2cAttachDevice(DEVICEADDRESS);

    MLX90640_I2CGeneralReset();
    vTaskDelay(pdMS_TO_TICKS(20));

    uint16_t tempbuf[2];
    esp_err_t err = MLX90640_I2CRead(DEVICEADDRESS, 0x2400, 1, tempbuf);
    if (err != ESP_OK) {
        ESP_LOGE("MLX90640", "Failed to read from MLX90640 after init");
    }
}

int MLX90640_I2CGeneralReset(void)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, 0x00 << 1 | I2C_MASTER_WRITE, true);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(cmd);
    return ret;
}

/*
I2C Bus
START
    SLA+W
    REGISTER ADDRESS
    REPEATED START
    SLA+R
    DATA BYTES
STOP
*/

int MLX90640_I2CRead(uint8_t mlxHandle, uint16_t startAddress, uint16_t nMemAddressRead, uint16_t *data)
{
    uint8_t addr[2] = {
        (startAddress >> 8),
        startAddress & 0xFF
    };

    uint8_t readBuf[2 * nMemAddressRead];
    
    esp_err_t ret = i2c_master_write_read_device(
        I2C_NUM_0,
        DEVICEADDRESS, 
        addr, sizeof(addr),
        readBuf, sizeof(readBuf),
        pdMS_TO_TICKS(100)  
    );
    if (ret != ESP_OK) return ret;
    for (int i = 0; i < nMemAddressRead; i++) {
        data[i] = (readBuf[2 * i] << 8) | readBuf[2 * i + 1];
    }
    return ESP_OK;
}

// [ADDR_HIGH][ADDR_L][DATA_H][DATA_L]

/*
I2C Bus
START
    0x33 (write)
    ADDR_H
    ADDR_L
    DATA_H
    DATA_L
STOP
*/

int MLX90640_I2CWrite(uint8_t mlxHandle, uint16_t writeAddress, uint16_t data)
{
    uint8_t highByteAddr = writeAddress >> 8;
    uint8_t lowByteAddr = writeAddress & 0xFF;
    uint8_t buf[4] = {
        highByteAddr,
        lowByteAddr,
        (data >> 8) & 0xFF,
        data & 0xFF
    };
    return i2c_master_write_to_device(
        I2C_NUM_0,
        DEVICEADDRESS,
        buf, sizeof(buf),
        pdMS_TO_TICKS(100)
    );
}

// Not gonna use this function so just filler

void MLX90640_I2CFreqSet(int freq)
{
    (void)freq;
}