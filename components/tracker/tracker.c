#include "tracker.h"
#include <math.h>
#include "trackingState.h"
#include "servoController.h"

#define XFOV 55.0f
#define YFOV 35.0f
#define TEMP_THRESHOLD 50.0f
#define COLUMN_THRESHOLD 3
#define ROW_THRESHOLD 3

#define SEEKER_TIMEOUT_MS 30000

static float prevAngleX = 0.f;
static float prevAngleY = 0.f;

bool prevTargetLocked = false;

static TimerHandle_t seekerTimeoutTimer;

static void seekerTimeoutCallback(TimerHandle_t xTimer)
{
    TrackerSetState(TRACKER_DISABLED);
    StopServos();
}

void TrackerInit(void)
{
    // Init Tracker State
    TrackerSetState(TRACKER_DISABLED);

    seekerTimeoutTimer = xTimerCreate("SeekerTimeout", pdMS_TO_TICKS(SEEKER_TIMEOUT_MS), pdFALSE, NULL, seekerTimeoutCallback);
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

    tracking_state_t currentState = TrackerGetState();

    if (currentState == TRACKER_DISABLED) 
    {
        StopServos();
    }

    prevTargetLocked = result->targetLocked;
    result->targetLocked = (maxTemp > TEMP_THRESHOLD) && !bShouldShift && (currentState != TRACKER_DISABLED);
    
    if (result->targetLocked) 
    {
        TrackerStartTracking(result);
    } 
    else 
    {
        if (prevTargetLocked == true) 
        {
            xTimerStop(seekerTimeoutTimer, 0);
        }
        result->angleX = prevAngleX;
        result->angleY = prevAngleY;
    }
}

// Tracking, calculate angle

void TrackerStartTracking(TrackerResult* info)
{
    if (prevTargetLocked == false){
         xTimerReset(seekerTimeoutTimer, 0);
    }

    prevAngleX = info->angleX;
    prevAngleY = info->angleY;

    float errorX = info->angleX - 15.5f;
    float errorY = info->angleY - 11.5f;

    float degPerPixelX = XFOV / 32.f;
    float degPerPixelY = YFOV / 24.f;

    float angleX = errorX * degPerPixelX;
    float angleY = errorY * degPerPixelY;

    UpdateAngles((ServoAngles){angleX, angleY}, 0.f);    
}