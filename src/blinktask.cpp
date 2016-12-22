#include <em_cmu.h>
#include <em_gpio.h>

#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>

#include "blinktask.hpp"

using namespace xXx;

BlinkTask::BlinkTask(uint16_t stack, UBaseType_t priority)
    : ArduinoTask(stack, priority), _LastWakeTime(0) {}

BlinkTask::~BlinkTask() {}

void BlinkTask::setup() {
    _LastWakeTime = xTaskGetTickCount();

    CMU_ClockEnable(cmuClock_HFLE, true);
    CMU_ClockEnable(cmuClock_GPIO, true);

    GPIO_PinModeSet(gpioPortF, 2, gpioModePushPullDrive, 0);
    GPIO_PinModeSet(gpioPortF, 3, gpioModePushPullDrive, 0);

    GPIO_PinOutSet(gpioPortF, 2);
}

void BlinkTask::loop() {
    vTaskDelayUntil(&_LastWakeTime, 1000 / portTICK_PERIOD_MS);

    GPIO_PinOutToggle(gpioPortF, 2);
    GPIO_PinOutToggle(gpioPortF, 3);
}
