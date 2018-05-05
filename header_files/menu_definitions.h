#ifndef __menu_definitions_H
#define __menu_definitions_H

#include <stdint.h>
#include "lcd_definitions.h"

#define TotalMenuTransitionNo 50
#define menu_unit_vertical_position 100

enum menu_list {

Vpn_true,Vpn_fund,
Vpp_true,Vpp_fund,
Ip_true,Ip_fund,
Active_Power,
Reactive_Power,
Apparent_Power,
Total_Power,
Power_Factors_true,Power_Factors_fund,		
Total_Power_Factor_true, Total_Power_Factor_fund,
Power_Ratios,Total_Power_Ratios,//Q:P instantaneous	
Active_Energy_import,Active_Energy_export,
Reactive_Energy_import,Rective_Energy_export,
Apparent_Energy,	
	
main_menu
};

enum main_menu_list {

	neg_guard=-1,
	start_bar=0,//0
	Vpn_main=1,//1
	Vpp_main=2,//2
	Ip_main=3,//3
	Active_Power_main=4,//4
	Reactive_Power_main=5,//5
	Apparent_Power_main=6,//6
	Total_Power_main=7,//7
	Power_Factors_main=8,//8
	Total_Power_Factor_main=9,//9
	pos_guard=10,
};

struct main_menu_rows{
	
	enum letter_codes_8pt *row1;
	enum letter_codes_8pt *row2;
	enum letter_codes_8pt *row3;
	enum letter_codes_8pt *row4;
	enum letter_codes_8pt *row5;
	enum letter_codes_8pt *row6;
	enum letter_codes_8pt *row7;
};

extern struct main_menu_rows main_lines;
extern enum letter_codes_8pt main_menu_entries[][20];


extern enum menu_list current_menu;
extern enum menu_list previous_menu;
extern enum main_menu_list main_menu_entry;






struct display_menu_handles{
	
	/*dynamic data*/ 
	
	float *values;
	
	//static data
	
	enum letter_codes_8pt title[20];
	
	enum letter_codes_14pt first_line[3];
	enum letter_codes_14pt second_line[3];
	enum letter_codes_14pt third_line[3];
	
	enum menu_symbols symbol[5];
	enum menu_units menu_chars[4];
	
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
		
	struct display_menu_handles Active_Power;
	struct display_menu_handles Reactive_Power;
	struct display_menu_handles Apparent_Power;		
	struct display_menu_handles Total_Power;
			
	struct display_menu_handles Power_Factors;
	struct display_menu_handles Total_Power_Factor;

	struct display_menu_handles main_menu;		
		
	}handle;
	
	
	struct display_menu_handles all[13]; 


};


extern union display_menu_union MENU;




enum input{
	
	
		invalid=0,
		enter_pressed=1,
		left_pressed=2,
		right_pressed=4,
		down_pressed=8,
		up_pressed=16,


};


extern enum input pressed_button;


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





struct MENU_TRANSITION{
	
	enum menu_list current_menu;
	enum input pressed;
	enum menu_list next_menu;


};

extern const struct MENU_TRANSITION menu_transition[TotalMenuTransitionNo];







extern struct display_menu_handles Vpn_true_Menu;


uint8_t letter_transfer_14pt(enum letter_codes_14pt x, uint8_t page, uint8_t column);
uint8_t letter_transfer_8pt(enum letter_codes_8pt x, uint8_t page, uint8_t column);
void digit_transfer_14pt(enum digit_codes_14pt x, uint8_t page, uint8_t column);
void unit_transfer(enum units x, uint8_t page, uint8_t column);
void menu_unit_transfer(enum menu_units x, uint8_t page, uint8_t column);
void symbol_transfer(enum menu_symbols x, uint8_t page,uint8_t column);

void dynamicDataTripple(struct display_menu_handles menu_item);
void staticDataTripple(struct display_menu_handles menu_item);
void toMainDetect();
void atMainOperation();

void init_Menu();
void DISPLAY_MENU();



#endif
