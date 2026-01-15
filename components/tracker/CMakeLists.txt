idf_component_register(SRCS "tracker.c"
                    INCLUDE_DIRS "include"
                    PRIV_REQUIRES trackingState servoController)