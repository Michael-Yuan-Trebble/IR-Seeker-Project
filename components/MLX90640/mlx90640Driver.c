#include "mlx90640Driver.h"
#include "driver/i2c.h"

mlx90640_device_t mlx90640Dev;

typedef enum{
    MLX90640_REFRESH_0_5HZ = 0,
    MLX90640_REFRESH_1HZ   = 1,
    MLX90640_REFRESH_2HZ   = 2,
    MLX90640_REFRESH_4HZ   = 3,
    MLX90640_REFRESH_8HZ   = 4,
    MLX90640_REFRESH_16HZ  = 5,
    MLX90640_REFRESH_32HZ  = 6,
    MLX90640_REFRESH_64HZ  = 7
} mlx90640_refresh_t;

esp_err_t mlx90640Init(mlx90640_device_t* dev) {
    esp_err_t ret;
    ret = mlx90640SetRefreshRate(dev, MLX90640_REFRESH_16HZ);
    if (ret != ESP_OK) {
        ESP_LOGE("MLX90640", "Failed to set refresh rate");
        return ret;
    }
    ret = mlx90640DumpEE(dev);
    if (ret != ESP_OK) {
        ESP_LOGE("MLX90640", "Failed to dump EE data");
        return ret;
    }
    ret = mlx90640ExtractParameters(dev, dev->eeData, &dev->mlx90640);
    if (ret != ESP_OK) {
        ESP_LOGE("MLX90640", "Failed to extract parameters");
        return ret;
    }

    return ESP_OK;
}