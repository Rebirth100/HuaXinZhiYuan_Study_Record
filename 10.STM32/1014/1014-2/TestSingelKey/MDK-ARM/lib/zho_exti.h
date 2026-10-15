#ifndef _ZHO_EXTI_H_
#define _ZHO_EXTI_H_

#include "main.h"
#include "zho_util.h"

#define NONE_EXTI_INDEX		-1

typedef void (*exti_action_t)(uint16_t pin);

boolean registry_exti_action(uint16_t pin, exti_action_t action);

#endif
