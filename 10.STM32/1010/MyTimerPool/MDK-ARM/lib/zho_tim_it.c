#include "main.h"
#include "zho_util.h"

#include "zho_tim_it.h"
#include "zho_stm32_config.h"

#if USING_TIMER_POOL
#include "zho_timer_pool.h"
#endif

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	
#if USING_TIMER_POOL
	timer_pool_action_in_it(htim);
#endif
	
}
