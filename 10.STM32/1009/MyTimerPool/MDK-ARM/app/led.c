#include "main.h"
#include "zho_util.h"

#include "zho_timer_pool.h"
#include "zho_stm32_config.h"
#include "led.h"

static zho_timer_t led_timer;

static void led_action(void *arg);

void init_led(void) {
	set_zho_timer(&led_timer, LED_PERIOD_ms, TIMER_STATUS_WORKING, led_action, NULL);
	add_timer(&led_timer);
}

static void led_action(void *arg) {
	static uint8_t val = 1;
	
	LED = val;
	val ^= 0x01;
}
