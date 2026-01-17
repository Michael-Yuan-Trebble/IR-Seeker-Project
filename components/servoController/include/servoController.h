#ifndef SERVOCONTROLLER_H
#define SERVOCONTROLLER_H

#include "driver/ledc.h"

#define SERVO_FREQ_HZ 50
#define SERVO_RES_BITS 16
#define SERVO_MAX_DUTY ((1 << SERVO_RES_BITS) - 1)
#define SERVO_TIMER LEDC_TIMER_0
#define SERVO_MODE LEDC_LOW_SPEED_MODE
#define SERVO_RESOLUTION LEDC_TIMER_16_BIT
#define SERVO_X_CHANNEL LEDC_CHANNEL_0
#define SERVO_Y_CHANNEL LEDC_CHANNEL_1
#define SERVO_X_PIN 18
#define SERVO_Y_PIN 19
#define SERVO_MIN_US 500
#define SERVO_MAX_US 2500
#define SERVO_ALPHA 0.15f
#define SERVO_DEADZONE_DEG 0.5f

typedef struct{
    float angleX;
    float angleY;
} ServoAngles;

void ServoInit(void);
void UpdateAngles(ServoAngles targetAngles, float deltaTime);
void StopServos();

#endif