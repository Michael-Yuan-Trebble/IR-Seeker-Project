#include "telemetry.h"
#include <inttypes.h>
#include "driver/uart.h"

void TelemetryInit(void){
    const uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_param_config(UART_NUM_1, &uart_config);
    uart_set_pin(UART_NUM_1, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(UART_NUM_1, 1024 * 2, 0, 0, NULL, 0);
}

void TelemetrySend(const TrackerResult* data){
    if(data == NULL){
        return;
    }
    char buffer[96];
    
    int len = snprintf(buffer, 
                       sizeof(buffer),
                       "ANGLE_X:%.2f,ANGLE_Y:%.2f,MAX_TEMP:%.2f,TARGET_LOCKED:%d,PIXEL_X:%d,PIXEL_Y:%d,MAX_IDX:%d\r\n",
                       data->angleX, data->angleY, data->maxTemp, data->targetLocked, data->pixelX, data->pixelY, data->maxIdx);
    if(len < 0)return;
    if (len >= (int)sizeof(buffer)) len = sizeof(buffer) - 1;
    uart_write_bytes(UART_NUM_1, buffer, len);
}