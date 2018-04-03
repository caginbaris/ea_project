#ifndef __menu_definitions_H
#define __menu_definitions_H

#include <stdint.h>

struct menu_handles{
	
	
	uint8_t up:1;
	uint8_t down:1;
	uint8_t left:1;
	uint8_t right:1;
	uint8_t enter:1;
	
	void (*static_data_transfer)();
	void (*dynamic_data_transfer)();

};





#endif
