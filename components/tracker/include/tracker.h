#ifndef TRACKER_H
#define TRACKER_H

#include <stdbool.h>
#include <stdint.h>

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