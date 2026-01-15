#include "buttonTask.h"
#include "trackingState.h"
#include "servoController.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

static EventGroupHandle_t buttonEventGroup;

void ButtonTaskInit(void)
{

}

static void IRAM_ATTR buttonISRHandler(void* arg)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xEventGroupSetBitsFromISR(buttonEventGroup, INPUT_BTN_PRESS, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken) 
    {
        portYIELD_FROM_ISR();
    }
}

void ButtonTaskStart(void* pvParameters)
{
    while(1)
    {
        xEventGroupWaitBits(buttonEventGroup, INPUT_BTN_PRESS, pdTRUE, pdFALSE, portMAX_DELAY);
        tracking_state_t state = TrackerGetState();
        if(state == TRACKER_DISABLED)
        {
            TrackerSetState(TRACKER_SEARCH);
        } 
        else 
        {
            TrackerSetState(TRACKER_DISABLED);
            StopServos();
        }
        vTaskDelay(10);
    }
}

void ButtonTaskStop(void)
{
    buttonEventGroup = xEventGroupCreate();

    gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_NEGEDGE,
        .mode = GPIO_MODE_INPUT,
        .pin_bit_mask = (1ULL << BUTTON_PIN),
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_ENABLE
    };

    gpio_config(&io_conf);
    gpio_install_isr_service(0);
    gpio_isr_handler_add(BUTTON_PIN, buttonISRHandler, NULL);

    xTaskCreate(ButtonTaskStart, "ButtonTask", 2048, NULL, 10, NULL);
}