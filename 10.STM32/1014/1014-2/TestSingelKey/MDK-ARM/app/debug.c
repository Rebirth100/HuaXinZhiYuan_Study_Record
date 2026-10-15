#include <stdio.h>

#include "main.h"
#include "zho_util.h"
#include "zho_stm32_config.h"

#include "debug.h"

#if USING_UART_RECEIVE
#include "zho_uart_rcv.h"
#endif

static UART_HandleTypeDef *debug_uart = NULL;
#if USING_UART_RECEIVE
static uart_rcv_t uart;
static uint8_t buffer[DEBUG_RECEIVE_BUFFER_CAPACITY];
#endif

#if USING_UART_RECEIVE
void init_debug(UART_HandleTypeDef *puart, uart_rcv_action_t callback) {
#else
void init_debug(UART_HandleTypeDef *puart) {
#endif
	if (debug_uart != NULL) return;
	
	debug_uart = puart;
#if USING_UART_RECEIVE
	set_uart_receiver(&uart, buffer, DEBUG_RECEIVE_BUFFER_CAPACITY, callback);
	init_zho_uart(puart, &uart);
#endif
}

void debug_send_bytes(uint8_t *buffer, uint16_t length) {
	HAL_UART_Transmit(debug_uart, buffer, length, UART_TIMEOUT);
}

int fputc(int ch, FILE *fp) {
	HAL_UART_Transmit(debug_uart, (uint8_t *) &ch, 1, UART_TIMEOUT);
	
	return ch;
}
