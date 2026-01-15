#ifndef TRACKER_STATE_H
#define TRACKER_STATE_H

typedef enum{
    TRACKER_DISABLED = 0,
    TRACKER_SEARCH = 1,
    TRACKER_LOCK = 2,
    TRACKER_TRACK = 3
} tracking_state_t;

void TrackerSetState(tracking_state_t state);
tracking_state_t TrackerGetState(void);

#endif