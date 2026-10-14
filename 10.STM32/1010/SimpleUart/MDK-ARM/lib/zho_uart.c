#include <stdio.h>

#include "main.h"
#include "zho_util.h"

#include "zho_uart.h"

static UART_HandleTypeDef *uart_uart = NULL;
static uint8_t ch;
static uint8_t buffer[1024];
static uint16_t index = 0;

boolean init_zho_uart(UART_HandleTypeDef *puart) {
	if (uart_uart != NULL) return FALSE;
	
	uart_uart = puart;
	HAL_UART_Receive_IT(puart, &ch, 1);
	
	return TRUE;
}

int fputc(int ch, FILE *fp) {
	HAL_UART_Transmit(uart_uart, (uint8_t *) &ch, 1, UART_TIMEOUT);
	
	return ch;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (ch != '\n') {
		buffer[index++] = ch;
	} else {
		buffer[index++] = ch;
		buffer[index] = 0;
		printf("%s", buffer);
		index = 0;
	}
	
	HAL_UART_Receive_IT(huart, &ch, 1);
}
