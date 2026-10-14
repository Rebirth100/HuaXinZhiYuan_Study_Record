#include <stdio.h>
#include "main.h"
#include "zho_util.h"

#include "user_app.h"

void do_something(uint8_t val) {
}

void after_receive_uart_message(uint8_t *buffer, uint16_t size) {
	buffer[size] = 0;
	printf("%s", buffer);
}
