#ifndef __graphing_definitions_H
#define __graphing_definitions_H


#include <stdint.h>





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



void graphBaseLining();
void graphDataTransfer();
void scope_routine();

void harmonicBaseLine();
void harmonicDataTransfer();

#endif
