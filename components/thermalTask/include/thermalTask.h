#ifndef THERMAL_TASK_H
#define THERMAL_TASK_H

#define MINIMUM_TEMP -40.f
#define MAXIMUM_TEMP 300.f
#define MLX90640_REFRESH_16HZ 5

void ThermalTaskInit(void);
void ThermalTaskStart(void* pvParameters);
void ThermalTaskStop(void);

#endif