#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <stdint.h>
#include <stdbool.h>
#include "tracker.h"
#include "trackingState.h"

void TelemetryInit(void);
void TelemetrySend(const TrackerResult* data);

#endif