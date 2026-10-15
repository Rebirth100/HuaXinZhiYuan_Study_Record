#include "main.h"
#include "zho_util.h"

#include "zho_os.h"
#include "zho_exti.h"
#include "zho_s_key.h"
#include "zho_delay.h"

#if USING_S_KEY_DEBUG
#include <stdio.h>
#endif

static get_port_t def_get_port = NULL;
static key_action_t def_key_action = NULL;
static boolean flag = FALSE;
static uint16_t cur_key;

static void s_key_action_in_exti(uint16_t key);
static void s_key_action_in_main_loop(void);

void init_zho_s_key(uint16_t key_pins, get_port_t get_key_port, key_action_t callback) {
	if (def_get_port != NULL || def_key_action != NULL) return;
	
	def_get_port = get_key_port;
	def_key_action = callback;
	registry_exti_action(key_pins, s_key_action_in_exti);
	add_action_in_main_loop(s_key_action_in_main_loop);
}

static void s_key_action_in_exti(uint16_t key) {
	zho_delay_ms(40);
	if (HAL_GPIO_ReadPin(def_get_port(key), key) == GPIO_PIN_SET) return;
	cur_key = key;
	flag = TRUE;
}

static void s_key_action_in_main_loop(void) {
	if (flag == FALSE) return;
	
	flag = FALSE;
	if (def_key_action != NULL) {
		def_key_action(cur_key);
	}
}
