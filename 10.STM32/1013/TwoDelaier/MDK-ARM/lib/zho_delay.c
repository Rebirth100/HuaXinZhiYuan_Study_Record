#include "main.h"
#include "zho_util.h"
#include "zho_stm32_config.h"

#include "zho_delay.h"

#if USING_TIM_DELAY

static TIM_HandleTypeDef *delay_tim = NULL;
static uint32_t arr;

void init_tim_delay(TIM_HandleTypeDef *ptim) {
	if (delay_tim != NULL) return;
	
	arr = ptim->Init.Period + 1;
	
	delay_tim = ptim;
	HAL_TIM_Base_Start(ptim);
}

void tim_delay_us(uint32_t us) {
	uint32_t last_count;
	uint32_t cur_count;
	uint32_t count = 0;
	
	last_count = __HAL_TIM_GetCounter(delay_tim);
	
	while (count < us) {
		cur_count = __HAL_TIM_GetCounter(delay_tim);
		
		if (cur_count >= last_count) {
			count = cur_count - last_count;
		} else {
			count = arr - last_count + cur_count;
		}
	}
}

void tim_delay_ms(uint32_t ms) {
	while (ms--) {
		tim_delay_us(1000);
	}
}

#endif

#if USING_SYSTICK_DELAY

static uint32_t count_base;

void init_systick(uint8_t psc) {
	uint32_t main_freq = HAL_RCC_GetHCLKFreq();
	
	BIT_RESET(SysTick->CTRL, 1);
	
	if (psc == SYSTICK_PSC_1) {
		BIT_SET(SysTick->CTRL, 2);
		count_base = main_freq / 1000000UL;
	} else {
		BIT_RESET(SysTick->CTRL, 2);
		count_base = main_freq / 1000000UL / 8;
	}
	
	BIT_RESET(SysTick->CTRL, 0);
}

void systick_delay_us(uint32_t us) {
	uint32_t temp;

	SysTick->LOAD = us * count_base;
	SysTick->VAL = 0;
	
	BIT_SET(SysTick->CTRL, 0);
	
	do {
		temp = SysTick->CTRL;
	} while (!IS_BIT_SET(temp, 16));
	
	BIT_RESET(SysTick->CTRL, 0);
}

void systick_delay_ms(uint32_t ms) {
	while (ms--) {
		systick_delay_us(1000);
	}
}

#endif
