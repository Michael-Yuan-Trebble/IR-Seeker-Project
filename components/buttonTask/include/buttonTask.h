#ifndef BUTTON_TASK_H
#define BUTTON_TASK_H

#include "driver/gpio.h"

#define BUTTON_PIN GPIO_NUM_0
#define INPUT_BTN_PRESS (1<<0)

void ButtonTaskInit(void);
void ButtonTaskStart(void* pvParameters);
void ButtonTaskConfigure(void);

#endif