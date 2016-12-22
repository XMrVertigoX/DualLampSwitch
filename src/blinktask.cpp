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

    GPIO_PinModeSet(gpioPortA, 0, gpioModePushPullDrive, 0);
    GPIO_PinModeSet(gpioPortA, 1, gpioModePushPullDrive, 0);

    GPIO_PinOutSet(gpioPortA, 0);
}

void BlinkTask::loop() {
    vTaskDelayUntil(&_LastWakeTime, 1000 / portTICK_PERIOD_MS);

    GPIO_PinOutToggle(gpioPortA, 0);
    GPIO_PinOutToggle(gpioPortA, 1);
}
