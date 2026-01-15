idf_component_register(SRCS "buttonTask.c"
                    INCLUDE_DIRS "include"
                    REQUIRES freertos driver
                    PRIV_REQUIRES trackingState servoController)
