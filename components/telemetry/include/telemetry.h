#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <stdint.h>
#include "tracker.h"

void TelemetryInit(void);
void TelemetrySend(const TrackerResult* data);

#endif