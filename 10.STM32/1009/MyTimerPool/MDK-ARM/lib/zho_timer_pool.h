#ifndef _ZHO_TIMER_POOL_H_
#define _ZHO_TIMER_POOL_H_

#include "main.h"
#include "zho_util.h"

typedef void (*timer_action_t)(void *arg);

typedef struct {
	uint32_t count;
	uint32_t period;
	boolean state;
	boolean flag;
	timer_action_t callback;
	void *arg;
} zho_timer_t;

void init_zho_timer_pool(TIM_HandleTypeDef *ptim);
boolean add_timer(zho_timer_t *timer);
void set_zho_timer(zho_timer_t *timer, uint32_t period_ms, boolean state, timer_action_t action, void *arg); 
void set_timer_period(zho_timer_t *timer, uint32_t period_ms);

void timer_pool_action_in_it(TIM_HandleTypeDef *htim);

#endif
