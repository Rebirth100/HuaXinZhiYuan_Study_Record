#include "main.h"
#include "zho_util.h"

#include "zho_exti.h"

static exti_action_t exti_action_pool[16] = { NULL };
static int16_t get_index(uint16_t pin);

boolean registry_exti_action(uint16_t pin, exti_action_t action) {
	uint16_t index;
	
	for (index = 0; index < 16; index++) {
		if (pin & 0x0001) {
			if (exti_action_pool[index] == NULL) {
				exti_action_pool[index] = action;
			} else {
				return FALSE;
			}
		}
		pin >>= 1;
	}
	
	return TRUE;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	int16_t index;
	
	index = get_index(GPIO_Pin);
	if (index == NONE_EXTI_INDEX) return;
	if (exti_action_pool[index] == NULL) return;

	exti_action_pool[index](GPIO_Pin);
}

static int16_t get_index(uint16_t pin) {
	uint16_t index;
	
	for (index = 0; index < 16; index++) {
		if (pin & 0x0001) return index;
		pin >>= 1;
	}
	
	return NONE_EXTI_INDEX;
}
