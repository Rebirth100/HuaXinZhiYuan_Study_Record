#ifndef _ZHO_DHT_11_H_
#define _ZHO_DHT_11_H_

#include "main.h"
#include "zho_util.h"

#define USING_DHT11_DEBUG		0

void init_zho_dht11(GPIO_TypeDef *port, uint16_t pin);
boolean is_dht11_exist(void);
boolean get_dht11_humidity_temperature(uint16_t *humi, float *temp);

#endif
