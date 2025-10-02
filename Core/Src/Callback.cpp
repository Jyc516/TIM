//
// Created by JiangYC on 25-10-2.
//
#include "main.h"
#include "gpio.h"
#include "tim.h"

#include "cmath"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    uint32_t arr_value = __HAL_TIM_GET_AUTORELOAD(&htim1) + 1;
    uint32_t brightness = arr_value * sinf(4 * HAL_GetTick() / 1000.f) - 1;
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, brightness);
}