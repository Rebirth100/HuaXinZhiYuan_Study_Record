#ifndef _ZHO_USER_APP_H_
#define _ZHO_USER_APP_H_

#include "main.h"
#include "zho_util.h"

void init_user_app(void);
void do_something(uint8_t val);
void after_receive_uart_message(uint8_t *buffer, uint16_t size);

#endif
