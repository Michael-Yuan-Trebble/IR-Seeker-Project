#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint32_t timestamp;
    float targetAngleX;
    float targetAngleY;
    float targetTemp;
    bool targetLocked;
    float systemLoad;
} TelemetryData;

enum Status{
    SEARCH = 0,
    LOCK = 1,
    TRACK = 2,
    LOST = 3
};

void TelemetryInit(void);
void TelemetrySend(const TelemetryData* data);

#endif