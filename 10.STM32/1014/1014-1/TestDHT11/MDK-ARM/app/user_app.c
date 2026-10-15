#include <stdio.h>
#include "main.h"
#include "zho_util.h"

#include "user_app.h"

#if 1
#include "zho_dht11.h"
#endif

void init_user_app(void) {
#if defined (_ZHO_DHT_11_H_)
	if (is_dht11_exist()) {
		printf("DHT11 存在");
	} else {
		printf("DHT11 不 存在");
	}
#endif
}

void do_something(uint8_t val) {
#if defined (_ZHO_DHT_11_H_)
	static uint16_t count = 0;
	uint16_t hm;
	float tm;
	
	if (++count >= 4) {
		count = 0;
		if (get_dht11_humidity_temperature(&hm, &tm)) {
			printf("湿度:%d%%, 温度:%.1f", hm, tm);
		} else {
			printf("获取温湿度数据失败！");
		}
	}
#endif
#if 0
	printf("串口输出测试");
#endif
}

void after_receive_uart_message(uint8_t *buffer, uint16_t size) {
	buffer[size] = 0;
	printf("%s", buffer);
}
