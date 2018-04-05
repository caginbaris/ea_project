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




struct display_menu_handles{
	
	//dynamic data
	float values[3];
	
	//static data
	
	int16_t title[16];
	
	int16_t first_line[3];
	int16_t second_line[3];
	int16_t third_line[3];
	
	int16_t symbols[5];
	
	int16_t button_pressed;
	
	void (*dynamicDataTransfer)(float* val, enum units unit);
	
	
};

extern struct display_menu_handles Vpn_Menu_trueRMS,Vpn_Menu_fundRMS;





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
void reactiveEnergy(struct push_buttons pb);

void dynamicData(float* val,enum units unit);






#endif
