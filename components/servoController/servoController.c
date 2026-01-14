#include "servoController.h"
#include "mathUtils.h"

static uint32_t usToDuty(uint32_t us) {
    const uint32_t maxDuty = (1 << SERVO_RESOLUTION) - 1;
    return (us * maxDuty) / 20000; // 20ms period for 50Hz
}

void ServoInit(void)
{
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = SERVO_MODE,
        .timer_num        = SERVO_TIMER,
        .duty_resolution  = SERVO_RESOLUTION,
        .freq_hz          = SERVO_FREQ_HZ,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);

    ledc_channel_config_t ledc_channel_x = {
        .speed_mode       = SERVO_MODE,
        .channel          = SERVO_X_CHANNEL,
        .timer_sel        = SERVO_TIMER,
        .gpio_num         = SERVO_X_PIN,
        .duty             = 0,
        .hpoint           = 0
    };
    ledc_channel_config(&ledc_channel_x);

    ledc_channel_config_t ledc_channel_y = ledc_channel_x;
    ledc_channel_y.channel = SERVO_Y_CHANNEL;
    ledc_channel_y.gpio_num = SERVO_Y_PIN;
    ledc_channel_config(&ledc_channel_y);
}

void UpdateAngles(ServoAngles targetAngles, float deltaTime)
{
    targetAngles.angleX = ClampFloat(targetAngles.angleX, -45.0f, 45.0f);
    targetAngles.angleY = ClampFloat(targetAngles.angleY, -30.0f, 30.0f);

    uint32_t pulseWidthX = SERVO_MIN_US + (targetAngles.angleX + 45) * (SERVO_MAX_US - SERVO_MIN_US) / 90.0f;
    uint32_t pulseWidthY = SERVO_MIN_US + (targetAngles.angleY + 30) * (SERVO_MAX_US - SERVO_MIN_US) / 60.0f;

    ledc_set_duty(SERVO_MODE, SERVO_X_CHANNEL, usToDuty(pulseWidthX));
    ledc_update_duty(SERVO_MODE, SERVO_X_CHANNEL);

    ledc_set_duty(SERVO_MODE, SERVO_Y_CHANNEL, usToDuty(pulseWidthY));
    ledc_update_duty(SERVO_MODE, SERVO_Y_CHANNEL);
}

void StopServos(){
}