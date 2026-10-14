#include "main.h"
#include "zho_util.h"
#include "zho_stm32_config.h"

#include "zho_uart_rcv.h"

#if USING_UART_RECEIVE
static uart_rcv_t *uart_rcv_pool[UART_RCV_POOL_CAPACITY] = {NULL};
static uint16_t count = 0;
#endif

#if USING_UART_RECEIVE
void init_zho_uart(UART_HandleTypeDef *puart, uart_rcv_t *uart) {
#else
void init_zho_uart(UART_HandleTypeDef *puart) {
#endif
	
#if USING_UART_RECEIVE
	if (count >= UART_RCV_POOL_CAPACITY) return;
	
	uart_rcv_pool[count++] = uart;
	
	HAL_UARTEx_ReceiveToIdle_DMA(puart, uart->buffer, uart->capacity);
#endif
}
