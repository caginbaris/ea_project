#include "menu_definitions.h"
#include "lcd_definitions.h"

float values[3]={0};
enum units unit=V;

void voltagesPhase2Neutral(struct push_buttons pb){




};
void voltagesPhase2Phase(struct push_buttons pb){};
void currents(struct push_buttons pb){};

void apparentPower(struct push_buttons pb){};
void activePower(struct push_buttons pb){}
void reactivePower(struct push_buttons pb){};
void totalPower(struct push_buttons pb){};

void apparentEnergy(struct push_buttons pb){};
void activeEnergy(struct push_buttons pb){};
void reactiveEnergy(struct push_buttons pb){};
	
void dynamicData(float* val,enum units unit){


};
	



void DISPLAY_MENU( struct display_menu_handles menu_item){

	uint8_t page=0;

	// define function for title data
	
	// 1st line of display menu
	letter_transfer((enum letter_codes)menu_item.first_line[0],page,0);
	letter_transfer((enum letter_codes)menu_item.first_line[1],page,upperCaseLargeLetterWidth);
	letter_transfer((enum letter_codes)menu_item.first_line[2],page,2*upperCaseLargeLetterWidth);
	
	page=page+2;
	
	// 2nd line of display menu
	letter_transfer((enum letter_codes)menu_item.second_line[0],page,0);
	letter_transfer((enum letter_codes)menu_item.second_line[1],page,upperCaseLargeLetterWidth);
	letter_transfer((enum letter_codes)menu_item.second_line[2],page,2*upperCaseLargeLetterWidth);
	
	page=page+2;
	
	// 3rd line of display menu
	letter_transfer((enum letter_codes)menu_item.third_line[0],page,0);
	letter_transfer((enum letter_codes)menu_item.third_line[1],page,upperCaseLargeLetterWidth);
	letter_transfer((enum letter_codes)menu_item.third_line[2],page,2*upperCaseLargeLetterWidth);
	
	
	//define function for button definition symbols
	
	// befor transferring real dynamic data it should be formatted accordingly)
	menu_item.dynamicDataTransfer( menu_item.values,unit);
	
	// define function for button evaluation for transition between menus
	
	
	
	


};