#include <stdio.h>
#include "main.h"
#include "zho_util.h"

#include "user_app.h"

void init_user_app(void) {
}

void do_something(uint8_t val) {

#if 0
	printf("´®¿ÚÊä³ö²âÊÔ");
#endif
	
}

void after_receive_uart_message(uint8_t *buffer, uint16_t size) {
	buffer[size] = 0;
	printf("%s", buffer);
}

void after_s_key_pressed(uint16_t key) {
	printf("key:%04X", key);
}

GPIO_TypeDef *get_key_port(uint16_t key) {
	return GPIOB;
}
