#include "main.h"
#include "rocketlib.h"
#include "ublox_max_m10s.h"

int fwmain(void) {
	while (1) {
		HAL_GPIO_TogglePin(GPIOC, LED_Pin);
		HAL_Delay(200);
		uint8_t data[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
		can_msg_t msg = {0};
		build_debug_raw_msg(PRIO_LOW, HAL_GetTick(), data, &msg);
	}
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t size) { //written in fwmain.c because USE_HAL_UART_REGISTER_CALLBACKS is set to 0
    if (huart->Instance == USART1) {
        ublox_rx_event_isr(size);
    }
}