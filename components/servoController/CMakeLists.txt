idf_component_register(SRCS "servoController.c"
                    INCLUDE_DIRS "include"
                    REQUIRES freertos esp_driver_i2c esp_driver_ledc
                    PRIV_REQUIRES mathUtils)
