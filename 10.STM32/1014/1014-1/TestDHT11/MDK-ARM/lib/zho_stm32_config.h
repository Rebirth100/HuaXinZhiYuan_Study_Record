#ifndef _ZHO_STM32_CONFIG_H_
#define _ZHO_STM32_CONFIG_H_

#include "main.h"
#include "zho_util.h"

// 定时器池
#define USING_TIMER_POOL				1
#if USING_TIMER_POOL
#define TIMER_POOL_CAPACITY			32

#define TIMER_STATUS_WORKING		0
#define TIMER_STATUS_SLEEPING		1
#endif

// 串口接收
#define USING_UART_RECEIVE			0
#define UART_TIMEOUT						200
#if USING_UART_RECEIVE
#define UART_RCV_POOL_CAPACITY	8
#endif

// 延时器
#define USING_ZHO_DELAY					1
#if USING_ZHO_DELAY
#define USING_SYSTICK_DELAY			1
#define USING_TIM_DELAY					0
#if USING_SYSTICK_DELAY
	#define SYSTICK_PSC_1					1
	#define SYSTICK_PSC_8					0
#endif
#endif

#endif
