idf_component_register(SRCS "tracker.c"
                    INCLUDE_DIRS "."
                    REQUIRES esp_driver_i2c
                    PRIV_REQUIRES mlx90640Lib)