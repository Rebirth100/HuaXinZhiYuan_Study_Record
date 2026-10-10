#ifndef _ZHO_OS_H_
#define _ZHO_OS_H_

#include "main.h"
#include "zho_util.h"

#define ACTION_POOL_CAPACITY		16

typedef void (*action_in_main_loop_t)(void);

void zho_os_loop(void);
boolean add_action_in_main_loop(action_in_main_loop_t action);

#endif
