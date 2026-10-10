#include "main.h"
#include "zho_util.h"

#include "zho_timer_pool.h"
#include "zho_stm32_config.h"

static zho_timer_t *timer_pool[TIMER_POOL_CAPACITY];
static uint16_t count = 0;

static TIM_HandleTypeDef *timer_pool_tim = NULL;

static void timer_pool_action_in_main_loop(void);

void init_zho_timer_pool(TIM_HandleTypeDef *ptim) {
	if (timer_pool_tim != NULL) return;
	
	timer_pool_tim = ptim;
}

boolean add_timer(zho_timer_t *timer) {
	if (count >= TIMER_POOL_CAPACITY) return FALSE;
	
	timer_pool[count++] = timer;
	return TRUE;
}

void set_zho_timer(zho_timer_t *timer, uint32_t period_ms, boolean state, timer_action_t action, void *arg) {
	if (timer == NULL) return;
	
	set_timer_period(timer, period_ms);
	timer->state = state;
	timer->callback = action;
	timer->arg = arg;
	
	timer->count = 0;
	timer->flag = FALSE;
}

void set_timer_period(zho_timer_t *timer, uint32_t period_ms) {
	if (timer == NULL) return;
	
	uint32_t mhz = HAL_RCC_GetHCLKFreq();
	uint32_t psc = timer_pool_tim->Init.Prescaler + 1;
	uint32_t arr = timer_pool_tim->Init.Period + 1;
	
	// X = Ö÷Æµ / 1000 / (PSC + 1) * T / (ARR + 1)
	uint32_t x;
	x = mhz / 1000 * period_ms;
	x /= psc;
	x /= arr;
	timer->period = x;
}

void timer_pool_action_in_it(TIM_HandleTypeDef *htim) {
	if (htim != timer_pool_tim) return;
	
	uint16_t index;
	zho_timer_t *timer;
	
	for (index = 0; index < count; index++) {
		timer = timer_pool[index];
		if (timer->state == TIMER_STATUS_SLEEPING) continue;
		
		if (++timer->count >= timer->period) {
			timer->count = 0;
			timer->flag = TRUE;
		}
	}
}

static void timer_pool_action_in_main_loop(void) {
	uint16_t index;
	zho_timer_t *timer;
	
	for (index = 0; index < count; index++) {
		timer = timer_pool[index];
		if (timer->state == TIMER_STATUS_SLEEPING) continue;
		
		if (timer->flag == TRUE) {
			timer->flag = FALSE;
			if (timer->callback != NULL) {
				timer->callback(timer->arg);
			}
		}
	}
}
