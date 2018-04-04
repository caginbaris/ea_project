#ifndef __menu_definitions_H
#define __menu_definitions_H

#include <stdint.h>
#include "lcd_definitions.h"

enum symbols {

up,
down,
left,
right

};





enum units {

V,
kV,

I,
kI

};

extern enum units unit;




struct menu_handles{
	
	int16_t title[16];
	int16_t first_line[3];
	int16_t second_line[3];
	int16_t third_line[3];
	int16_t symbols[5];
	
	//void (*dynamicDataTransfer)(float* val, enum units unit);
	
};







struct push_buttons{
	
	
	
	uint16_t s;


};


void voltagesPhase2Neutral(struct push_buttons pb);
void voltagesPhase2Phase(struct push_buttons pb);
void currents(struct push_buttons pb);

void apparentPower(struct push_buttons pb);
void activePower(struct push_buttons pb);
void reactivePower(struct push_buttons pb);
void totalPower(struct push_buttons pb);

void apparentEnergy(struct push_buttons pb);
void activeEnergy(struct push_buttons pb);
void reactiveEnergy(struct push_buttons pb);s


void (*menu_functions[])(struct push_buttons pb)={

	voltagesPhase2Neutral,
	voltagesPhase2Phase,
	currents,
	
	apparentPower,
	activePower,
	reactivePower,
	totalPower,
	
	apparentEnergy,
	activeEnergy,
	reactiveEnergy,
	
};






#endif
