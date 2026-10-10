#ifndef _ZHO_LED_H_
#define _ZHO_LED_H_

#include "main.h"
#include "zho_util.h"

#define LED_PERIOD_ms		500

#define LED		PCout(13)

void init_led(void);

#endif
