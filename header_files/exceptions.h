#ifndef exceptions_H
#define exceptions_H

#include <stdint.h>


#define voltageHighLimit 440.0f
#define voltageLowLimit  4.0f

#define currentHighLimit 5.5f
#define currentLowLimit  0.05f

union exception_defs{

struct {

	
	uint32_t Va_highLevel:1;
	uint32_t Vb_highLevel:1;
	uint32_t Vc_highLevel:1;
	
	uint32_t Ia_highLevel:1;
	uint32_t Ib_highLevel:1;
	uint32_t Ic_highLevel:1;
	
	
	uint32_t spare:20;



}bit;

uint32_t all;

};

extern union exception_defs exception;

void exceptions(void);
void exception_messaging(void);

#endif

