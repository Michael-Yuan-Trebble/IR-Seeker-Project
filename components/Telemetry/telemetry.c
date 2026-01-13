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

void TelemetrySend(const TelemetryData* data){
    if(data == NULL){
        return;
    }
    char buffer[96];
    int len = snprintf(buffer, 
                       sizeof(buffer),
                       "t=%" PRIu32 " ax=%.2f, ay=%.2f, temp=%.2f, locked=%d, load=%.2f\r\n",
                       data->timestamp,
                       data->targetAngleX,
                       data->targetAngleY,
                       data->targetTemp,
                       data->targetLocked ? 1 : 0,
                       data->systemLoad);
    if(len < 0)return;
    if (len >= (int)sizeof(buffer)) len = sizeof(buffer) - 1;
    uart_write_bytes(UART_NUM_1, buffer, len);
}