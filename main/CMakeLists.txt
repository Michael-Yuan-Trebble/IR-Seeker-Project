idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS "."
                    REQUIRES freertos esp_driver_i2c esp_driver_uart esp_adc
                    PRIV_REQUIRES mlx90640Lib tracker thermalTask servoController)
