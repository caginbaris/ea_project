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



enum units {

u_K,
u_M,
u_G	

};

extern enum units unit;




struct display_menu_handles{
	
	//dynamic data
	float* values;
	
	//static data
	
	enum letter_codes_8pt title[20];
	
	enum letter_codes_14pt first_line[3];
	enum letter_codes_14pt second_line[3];
	enum letter_codes_14pt third_line[3];
	
	enum menu_symbols symbol[5];
	
	enum menu_list id;
	
	void (*dynamicDataTransfer)();
	void (*staticDataTransfer)();
	
};

extern struct display_menu_handles Vpn_Menu_trueRMS,Vpn_Menu_fundRMS;





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




void dynamicData(float* val,enum units unit);


extern struct display_menu_handles Vpn_true_Menu;



#endif
