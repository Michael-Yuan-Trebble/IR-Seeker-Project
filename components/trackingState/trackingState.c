#include "trackingState.h"

tracking_state_t currentTrackingState;

void TrackerSetState(tracking_state_t state){
    currentTrackingState = state;
}

tracking_state_t TrackerGetState(void){
    return currentTrackingState;
}