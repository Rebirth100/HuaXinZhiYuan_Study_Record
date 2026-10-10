#include "main.h"
#include "zho_util.h"

#include "zho_os.h"

static action_in_main_loop_t action_pool[ACTION_POOL_CAPACITY];
static uint16_t count = 0;

void zho_os_loop(void) {
	uint16_t index;
	
	while (1) {
		for (index = 0; index < count; index++) {
			if (action_pool[index] != NULL) {
				action_pool[index]();
			}
		}
	}
}

boolean add_action_in_main_loop(action_in_main_loop_t action) {
	if (count >= ACTION_POOL_CAPACITY) return FALSE;
	
	action_pool[count++] = action;
	
	return TRUE;
}
