#ifndef _ZHO_S_KEY_H_
#define _ZHO_S_KEY_H_

#include "main.h"
#include "zho_util.h"

#define USING_S_KEY_DEBUG			1

typedef GPIO_TypeDef *(*get_port_t)(uint16_t key);
typedef void (*key_action_t)(uint16_t key);

void init_zho_s_key(uint16_t key_pins, get_port_t get_key_port, key_action_t callback);

#endif
