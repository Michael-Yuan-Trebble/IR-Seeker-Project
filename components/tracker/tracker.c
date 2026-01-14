#include "tracker.h"
#include <math.h>

#define XFOV 55.0f
#define YFOV 35.0f
#define TEMP_THRESHOLD 50.0f
#define COLUMN_THRESHOLD 3
#define ROW_THRESHOLD 3

static float prevAngleX = 0.f;
static float prevAngleY = 0.f;

void TrackerInit(void)
{
    // TODO: Put variable inits here if needed
}

void TrackerUpdate(const float* tempMap, TrackerResult* result)
{
    int maxIdx = 0;
    float maxTemp = -1000.f;
    for (int i = 0; i < 768; i++) 
    {
        if (tempMap[i] > maxTemp) 
        {
            maxTemp = tempMap[i];
            maxIdx = i;
        }
    }

    // Check if target is outside bounding box
    bool bShouldShift = false;
    if (maxIdx % 32 < COLUMN_THRESHOLD || maxIdx % 32 > (31 - COLUMN_THRESHOLD) ||
        maxIdx / 32 < ROW_THRESHOLD || maxIdx / 32 > (23 - ROW_THRESHOLD)) 
    {
        bShouldShift = true;
    }

    int pixelX = maxIdx % 32;
    int pixelY = maxIdx / 32;
    float angleX = (pixelX - 15.5f) * (XFOV / 32.f);
    float angleY = (pixelY - 11.5f) * (YFOV / 24.f);

    result->maxTemp = maxTemp;
    result->angleX = angleX;
    result->angleY = angleY;

    result->targetLocked = (maxTemp > TEMP_THRESHOLD);
    if (result->targetLocked && !bShouldShift) 
    {
        TrackerStartTracking(result);
    } else 
    {
        result->angleX = prevAngleX;
        result->angleY = prevAngleY;
    }
}

void TrackerStartTracking(TrackerResult* info)
{
    prevAngleX = info->angleX;
    prevAngleY = info->angleY;
}