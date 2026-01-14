idf_component_register(SRCS "thermalTask.c"
                    INCLUDE_DIRS "include"
                    REQUIRES esp_driver_i2c
                    PRIV_REQUIRES mlx90640Lib tracker telemetry)