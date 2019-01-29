#ifndef __ios_H
#define __ios_H

#include <stdint.h>

union boardInput{
	
	struct{
	
	uint8_t raw:1;
	uint8_t onDelayed:1;
	uint8_t offDelayed:1;
	uint8_t on_offDelayed:1;
	uint8_t risingEdgeDetected:1;
	uint8_t fallingEdgeDetected:1;
	uint8_t rem:2;}bit;
	
	uint8_t all;
	
};


extern union boardInput input;
extern uint8_t output;

void ios(void);


#endif

