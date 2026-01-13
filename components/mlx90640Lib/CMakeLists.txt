idf_component_register(SRCS "mlx90640Driver.c" "mlx90640API.c"
    INCLUDE_DIRS "include"
    REQUIRES esp_driver_i2c freertos
    PRIV_REQUIRES i2cDriver driver)