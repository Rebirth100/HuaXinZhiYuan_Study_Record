#include "main.h"
#include "zho_os.h"
#include "zho_util.h"
#include "zho_stm32_config.h"

#include "zho_uart_rcv.h"

#if USING_UART_RECEIVE
static uart_rcv_t *uart_rcv_pool[UART_RCV_POOL_CAPACITY] = {NULL};
static uint16_t count = 0;

static void uart_rcv_action_in_main_loop(void);

void set_uart_receiver(uart_rcv_t *uart, uint8_t *buffer, uint16_t capacity, uart_rcv_action_t callback) {
	if (uart == NULL || buffer == NULL || capacity <= 0) return;
	
	uart->buffer = buffer;
	uart->capacity = capacity;
	uart->callback = callback;
	
	uart->size = 0;
	uart->flag = FALSE;
}

boolean init_zho_uart(UART_HandleTypeDef *puart, uart_rcv_t *uart) {
	if (count >= UART_RCV_POOL_CAPACITY) return FALSE;
	
	uart->puart = puart;
	uart_rcv_pool[count++] = uart;
	add_action_in_main_loop(uart_rcv_action_in_main_loop);
	
	HAL_UARTEx_ReceiveToIdle_DMA(puart, uart->buffer, uart->capacity);
	__HAL_DMA_DISABLE_IT(puart->hdmarx, DMA_IT_HT);
	
	return TRUE;
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
	uint16_t index;
	uart_rcv_t *uart = NULL;
	
	for (index = 0; index < count; index++) {
		uart = uart_rcv_pool[index];
		if (uart->puart == huart) {
			uart->size = Size;
			uart->flag = TRUE;
			return;
		}
	}
}

static void uart_rcv_action_in_main_loop(void) {
	uint16_t index;
	uart_rcv_t *uart = NULL;
	
	for (index = 0; index < count; index++) {
		uart = uart_rcv_pool[index];
		if (uart->flag == TRUE) {
			uart->flag = FALSE;
			if (uart->callback != NULL) {
				uart->callback(uart->buffer, uart->size);
			}
			
			HAL_UARTEx_ReceiveToIdle_DMA(uart->puart, uart->buffer, uart->capacity);
			__HAL_DMA_DISABLE_IT(uart->puart->hdmarx, DMA_IT_HT);
			
			return;
		}
	}
}
#endif
