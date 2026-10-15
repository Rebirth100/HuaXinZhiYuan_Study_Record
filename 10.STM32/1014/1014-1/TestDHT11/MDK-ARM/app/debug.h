#ifndef _ZHO_DEBUG_H_
#define _ZHO_DEBUG_H_

#include "main.h"
#include "zho_util.h"
#include "zho_stm32_config.h"

#if USING_UART_RECEIVE
#include "zho_uart_rcv.h"

#define DEBUG_RECEIVE_BUFFER_CAPACITY			32
#endif

#if USING_UART_RECEIVE
void init_debug(UART_HandleTypeDef *puart, uart_rcv_action_t callback);
#else
void init_debug(UART_HandleTypeDef *puart);
#endif
void debug_send_bytes(uint8_t *buffer, uint16_t length);

#endif
