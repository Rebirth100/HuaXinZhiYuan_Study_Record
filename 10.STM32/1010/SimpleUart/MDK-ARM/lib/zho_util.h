#ifndef _ZHO_UTIL_H_
#define _ZHO_UTIL_H_

#include "main.h"

#if defined (STM32F4)
#define GPIO_ODR_OFFSET		0x14
#define GPIO_IDR_OFFSET		0x10
#elif defined (STM32F1)
#define GPIO_ODR_OFFSET		0x0C
#define GPIO_IDR_OFFSET		0x08
#endif

typedef uint8_t boolean;
#define TRUE		1
#define FALSE		0

#define BIT_SET(val, n)			((val) | (1 << (n)))
#define BIT_RESET(val, n)		((val) & ~(1 << (n)))
#define IS_BIT_SET(val, n)	(((val) & (1 << (n))) != 0)

#define HIGH		1
#define LOW			0

#define BITBAND(addr, bitnum) ((addr & 0xF0000000) + 0x02000000 + ((addr & 0x000FFFFF) << 5 ) + (bitnum << 2))
#define MEM_ADDR(addr) *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum) MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE | GPIO_ODR_OFFSET) 
#define GPIOB_ODR_Addr    (GPIOB_BASE | GPIO_ODR_OFFSET) 
#define GPIOC_ODR_Addr    (GPIOC_BASE | GPIO_ODR_OFFSET) 
#define GPIOD_ODR_Addr    (GPIOD_BASE | GPIO_ODR_OFFSET) 
#define GPIOE_ODR_Addr    (GPIOE_BASE | GPIO_ODR_OFFSET) 
#define GPIOF_ODR_Addr    (GPIOF_BASE | GPIO_ODR_OFFSET) 
#define GPIOG_ODR_Addr    (GPIOG_BASE | GPIO_ODR_OFFSET) 

#define GPIOA_IDR_Addr    (GPIOA_BASE | GPIO_IDR_OFFSET) 
#define GPIOB_IDR_Addr    (GPIOB_BASE | GPIO_IDR_OFFSET) 
#define GPIOC_IDR_Addr    (GPIOC_BASE | GPIO_IDR_OFFSET) 
#define GPIOD_IDR_Addr    (GPIOD_BASE | GPIO_IDR_OFFSET) 
#define GPIOE_IDR_Addr    (GPIOE_BASE | GPIO_IDR_OFFSET) 
#define GPIOF_IDR_Addr    (GPIOF_BASE | GPIO_IDR_OFFSET) 
#define GPIOG_IDR_Addr    (GPIOG_BASE | GPIO_IDR_OFFSET) 
 
//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr, n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr, n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr, n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr, n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr, n)  //输出
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr, n)  //输入  

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr, n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr, n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr, n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr, n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr, n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr, n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr, n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr, n)  //输入

#endif
