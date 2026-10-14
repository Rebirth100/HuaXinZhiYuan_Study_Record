#ifndef _ZHO_UART_H_
#define _ZHO_UART_H_

#include "main.h"
#include "zho_util.h"

#define UART_TIMEOUT		200

boolean init_zho_uart(UART_HandleTypeDef *puart);

#endif
