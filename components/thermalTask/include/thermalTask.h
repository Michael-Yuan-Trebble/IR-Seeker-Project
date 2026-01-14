#ifndef THERMAL_TASK_H
#define THERMAL_TASK_H

extern float emissivity;
extern float Ta;

#define MINIMUM_TEMP -40.f
#define MAXIMUM_TEMP 300.f

void ThermalTaskInit(void);
void ThermalTaskStart(void* pvParameters);
void ThermalTaskStop(void);

#endif