#ifndef _ZHO_STM32_CONFIG_H_
#define _ZHO_STM32_CONFIG_H_

#include "main.h"
#include "zho_util.h"

#define USING_TIMER_POOL				1
#if USING_TIMER_POOL
#define TIMER_POOL_CAPACITY			32

#define TIMER_STATUS_WORKING		0
#define TIMER_STATUS_SLEEPING		1
#endif

#endif
