#ifndef __device_command_h
#define __device_command_h

#include <stdint.h>

union deviceCommands{

struct{
	
	uint32_t reset_energy_counter:1;
	uint32_t take_snap:1;
	uint32_t force_output:1;
	uint32_t rem:28;

}bit;

uint32_t all;

};


extern union deviceCommands command;

void commandHandling(void);

#endif
