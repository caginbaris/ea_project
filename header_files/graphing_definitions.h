#ifndef __graphing_definitions_H
#define __graphing_definitions_H


#include <stdint.h>
#include "menu_definitions.h"




union LCD_map{

struct{

	uint8_t b0:1;
	uint8_t b1:1;
	uint8_t b2:1;
	uint8_t b3:1;
	uint8_t b4:1;
	uint8_t b5:1;
	uint8_t b6:1;
	uint8_t b7:1;
	
	


}bit;

uint8_t all;


};



void graphBaseLining(struct display_menu_handles menu_item);
void graphDataTransfer(struct display_menu_handles menu_item);
void scope_routine(void);

void harmonicBaseLine(struct display_menu_handles menu_item);
void harmonicDataTransfer(struct display_menu_handles menu_item);


extern float bin_array[6][20];

#endif
