#ifndef TRACKER_H
#define TRACKER_H

#include <stdbool.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"

#define XFOV 55.0f
#define YFOV 35.0f
#define TEMP_THRESHOLD 50.0f
#define COLUMN_THRESHOLD 3
#define ROW_THRESHOLD 3
#define SEEKER_TIMEOUT_MS 30000

typedef struct{
    float angleX;
    float angleY;
    float maxTemp;
    float distance;
    bool targetLocked;
    int maxIdx;
    uint8_t pixelX;
    uint8_t pixelY;
} TrackerResult;

void TrackerInit(void);
void TrackerUpdate(const float* tempMap, TrackerResult* result);
void TrackerStartTracking(TrackerResult* info);

#endif