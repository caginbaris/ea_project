#ifndef __counters_H
#define __counters_H

#include <stdint.h>

extern uint8_t systick_flag;

extern uint16_t display_refresh_counter;
extern uint16_t display_refresh_rate;

enum input  pushButtonHandling(void);
enum menu_list SELECT_MENU(enum menu_list current,enum input button);

#endif