
#include "measurement_definitions.h"
#include "device_command.h"

union deviceCommands command;

extern uint8_t snap_start;
extern uint8_t record_start;
extern uint8_t output;

void commandHandling(){
	
	struct energyParameters  energyZero={0};
	
	
	if(command.bit.reset_energy_counter){

		energy=energyZero;
		command.bit.reset_energy_counter=0;
	
	}
	
	
	if(command.bit.take_snap){

			snap_start=1;
			record_start=1;
	
	}
	
	
	if(command.bit.force_output){
		command.bit.force_output=0;
		output=1;
		
		}











}