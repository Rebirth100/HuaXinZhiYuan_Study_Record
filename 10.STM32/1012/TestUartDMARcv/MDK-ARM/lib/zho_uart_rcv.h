#ifndef _ZHO_UART_RCV_H_
#define _ZHO_UART_RCV_H_

#include "main.h"
#include "zho_util.h"
#include "zho_stm32_config.h"

typedef void (*uart_rcv_action_t)(uint8_t *buffer, uint16_t size);

typedef struct {
	UART_HandleTypeDef *puart;
	uint8_t *buffer;
	uint16_t capacity;
	uint16_t size;
	boolean flag;
	uart_rcv_action_t callback;
} uart_rcv_t;

#if USING_UART_RECEIVE
void init_zho_uart(UART_HandleTypeDef *puart, uart_rcv_t *uart);
#else
void init_zho_uart(UART_HandleTypeDef *puart);
#endif

#endif
