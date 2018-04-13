#ifndef __menu_definitions_H
#define __menu_definitions_H

#include <stdint.h>
#include "lcd_definitions.h"



enum menu_list {

Vpn_true,Vpn_fund,
Vpp_true,Vpp_fund,
Ip_true,Ip_fund


};


extern enum menu_list current_menu;
extern enum menu_list next_menu;

enum menu_symbols {

menu_enter,
menu_escape,		
menu_left,
menu_right,
menu_down,
menu_up

};


struct display_menu_handles{
	
	/*dynamic data*/ 
	
	float *values;
	
	//static data
	
	enum letter_codes_8pt title[20];
	
	enum letter_codes_14pt first_line[3];
	enum letter_codes_14pt second_line[3];
	enum letter_codes_14pt third_line[3];
	
	enum menu_symbols symbol[5];
	
	void (*staticDataTransfer)(struct display_menu_handles menu_item);
	void (*dynamicDataTransfer)(struct display_menu_handles menu_item);
	
	
};




union display_menu_union{
	
	
	struct{
		
	struct display_menu_handles Vpn_true;
	struct display_menu_handles Vpn_fund;

	struct display_menu_handles Vpp_true;
	struct display_menu_handles Vpp_fund;
	
	struct display_menu_handles Ip_true;
	struct display_menu_handles Ip_fund;
	
	}handle;
	
	
	struct display_menu_handles all[6]; 


};


extern union display_menu_union MENU;




enum input{
	
		enter_pressed=1,
		left_pressed=2,
		right_pressed=4,
		down_pressed=8,
		up_pressed=16,


};


union push_buttons{
	
	struct{
		
		uint8_t enter:1;
		uint8_t left:1;
		uint8_t right:1;
		uint8_t down:1;
		uint8_t up:1;
	
	}button;
	
	uint8_t all;


};


extern union push_buttons pb;


struct MENU_TRANSITION{
	
	enum menu_list current_menu;
	enum input pressed;
	enum menu_list next_menu;


};







extern struct display_menu_handles Vpn_true_Menu;


void letter_transfer_14pt(enum letter_codes_14pt x, uint8_t page, uint8_t column);
void letter_transfer_8pt(enum letter_codes_8pt x, uint8_t page, uint8_t column);
void digit_transfer_14pt(enum digit_codes_14pt x, uint8_t page, uint8_t column);

void dynamicDataTripple(struct display_menu_handles menu_item);
void staticDataTripple(struct display_menu_handles menu_item);

#endif
