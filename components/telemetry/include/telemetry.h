#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <stdint.h>
#include <stdbool.h>
#include "tracker.h"

enum Status{
    SEARCH = 0,
    LOCK = 1,
    TRACK = 2,
    LOST = 3
};

void TelemetryInit(void);
void TelemetrySend(const TrackerResult* data);

#endif