//
// Created by JiangYC on 25-10-2.
//
#include "main.h"
#include "gpio.h"
#include "tim.h"
#include "usart.h"

#include "cmath"

uint32_t pre_ticks = HAL_GetTick();
uint32_t cur_ticks;
volatile uint32_t brightness;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    cur_ticks = HAL_GetTick();
    if (cur_ticks - pre_ticks > 500) {
        pre_ticks = cur_ticks;

        uint32_t arr_value = __HAL_TIM_GET_AUTORELOAD(&htim1) + 1;
        brightness = arr_value * sinf(4 * HAL_GetTick() / 1000.f) - 1;
        // __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, brightness);
    }
}

uint32_t count = 0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
    if (htim == &htim1) {
        ++count;
    }
}

extern uint8_t rx_msg[20];
extern uint8_t tx_msg[20];
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart == &huart7) {
        for (int i=0; i<20; i++) {
            tx_msg[i] = rx_msg[i];
        }
        HAL_UART_Transmit_IT(&huart7, tx_msg, 20);
    }
    HAL_UART_Receive_IT(&huart7, rx_msg, 20);
}

// void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
//     if (huart == &huart7) {
//         HAL_UART_Transmit(&huart7, tx_msg, 19, 1000);
//     }
// }