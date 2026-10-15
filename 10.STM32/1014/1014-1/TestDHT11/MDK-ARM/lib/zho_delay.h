#ifndef _ZHO_DELAY_H_
#define _ZHO_DELAY_H_

#include "main.h"
#include "zho_util.h"
#include "zho_stm32_config.h"

#if USING_TIM_DELAY
void init_tim_delay(TIM_HandleTypeDef *ptim);
void tim_delay_us(uint32_t us);
void tim_delay_ms(uint32_t ms);
#endif

#if USING_SYSTICK_DELAY
void init_systick(uint8_t psc);
void systick_delay_us(uint32_t us);
void systick_delay_ms(uint32_t ms);
#endif

#if USING_ZHO_DELAY
	#if USING_SYSTICK_DELAY
	#define zho_delay_us(n)		systick_delay_us(n)
	#define zho_delay_ms(n)		systick_delay_ms(n)
	#endif
	#if USING_TIM_DELAY
	#define zho_delay_us(n)		tim_delay_us(n)
	#define zho_delay_ms(n)		tim_delay_ms(n)
	#endif
#endif

#endif
