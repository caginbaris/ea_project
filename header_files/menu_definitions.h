#ifndef __menu_definitions_H
#define __menu_definitions_H

#include <stdint.h>
#include "lcd_definitions.h"

#define TotalMenuTransitionNo 170
#define menu_unit_vertical_position 100

#define flashWordSize 10
#define flashByteSize  (flashWordSize*4)

extern enum menu_list current_menu;
extern enum menu_list previous_menu;

enum menu_list {

Vpn_true,Vpn_fund, //0-1
Vpp_true,Vpp_fund, //2-3
Ip_true,Ip_fund,   //4-5
Active_Power,      //6
Reactive_Power,    //7
Apparent_Power,		 //8
Total_Power,			 //9
Power_Factors_true,Power_Factors_fund, //10-11		
Total_Power_Factor_true, Total_Power_Factor_fund,//12-13	
Power_Ratios,Total_Power_Ratios,//14-15
Active_Energy_import	,Active_Energy_Total_import,	Active_Energy_export,		Active_Energy_Total_export,//16-17
Reactive_Energy_import,Reactive_Energy_Total_import,Reactive_Energy_export,	Reactive_Energy_Total_export, //18-19
Apparent_Energy,Apparent_Energy_Total,	//20
Scope_Van,Scope_Vbn,Scope_Vcn,//23-24-25
Scope_Ia,Scope_Ib,Scope_Ic,//26-27-28	
Harmonics_Van,Harmonics_Vbn,Harmonics_Vcn,//29-30-31	
Harmonics_Ia,Harmonics_Ib,Harmonics_Ic,//32-33-34			
thd_Vpn,thd_I,//35-36-37	
sym_Vpn,sym_I,//38-39-40	
unb_Vpn,unb_I,	
main_menu, //41

settings_menu,
set_VT,
set_CT,
set_input,
set_output,
set_comm,
set_display,
set_energy_reset,
set_password,
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
	Power_Ratios_main=9,//9
	Active_Energy_main=10,//10
	Reactive_Energy_main=11,//11
	Apparent_Energy_main=12,//12
	Scope_main=13,//13
	Harmonics_Main=14,//14
	THD_main=15,//15
	Sym_main=16,//16
	Unb_main=17,//17
	settings_main=18,//18
	pos_guard=19,
};


enum setting_menu_list {

	setting_neg_guard=-1,
	setting_start_bar=0,//0
	setting_VT,//1
	setting_CT,//2
	setting_input,//3
	setting_output,//4
	setting_comm,//5
	setting_display,//6
	setting_energy_reset,//7
	setting_password,//8
	setting_pos_guard=9,
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

struct setting_menu_rows{
	
	enum letter_codes_8pt *row1;
	enum letter_codes_8pt *row2;
	enum letter_codes_8pt *row3;
	enum letter_codes_8pt *row4;
	enum letter_codes_8pt *row5;
	enum letter_codes_8pt *row6;
	enum letter_codes_8pt *row7;
};


extern struct main_menu_rows main_lines;
extern enum   letter_codes_8pt main_menu_entries[][20];

extern struct setting_menu_rows setting_lines;
extern enum  letter_codes_8pt setting_menu_entries[][20];

extern enum menu_list current_menu;
extern enum menu_list previous_menu;

extern enum main_menu_list    main_menu_entry;
extern enum setting_menu_list setting_menu_entry;





struct display_menu_handles{
	
	/*dynamic data*/ 
	
	float *values;
	
	//static data
	
	enum letter_codes_8pt title[21];
	
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
		
	struct display_menu_handles Vpn_true;//0
	struct display_menu_handles Vpn_fund;//1

	struct display_menu_handles Vpp_true;//2
	struct display_menu_handles Vpp_fund;//3
	
	struct display_menu_handles Ip_true;//4
	struct display_menu_handles Ip_fund;//5
		
	struct display_menu_handles Active_Power;//6
	struct display_menu_handles Reactive_Power;//7
	struct display_menu_handles Apparent_Power;//8		
	struct display_menu_handles Total_Power;//9
			
	struct display_menu_handles Power_Factors_true;//10
	struct display_menu_handles Power_Factors_fund;//11
		
	struct display_menu_handles Total_Power_Factor_true;//12
	struct display_menu_handles Total_Power_Factor_fund;//13

	struct display_menu_handles Power_Ratios;//14
	struct display_menu_handles Total_Power_Ratios;	//15
	
	struct display_menu_handles Active_Energy_Import;//16
	struct display_menu_handles Active_Total_Energy_Import;//17
	
	struct display_menu_handles Active_Energy_Export;//18
	struct display_menu_handles Active_Total_Energy_Export;//19
	
	struct display_menu_handles Reactive_Energy_Import;//20
	struct display_menu_handles Reactive_Total_Energy_Import;//21
	
	struct display_menu_handles Reactive_Energy_Export;//22
	struct display_menu_handles Reactive_Total_Energy_Export;//23
	
	struct display_menu_handles Apparent_Energy;//24
	struct display_menu_handles Apparent_Total_Energy;//25
	
	struct display_menu_handles Scope_Van;//26
	struct display_menu_handles Scope_Vbn;//27
	struct display_menu_handles Scope_Vcn;//28
	
	struct display_menu_handles Scope_Ia;//29
	struct display_menu_handles Scope_Ib;//30
	struct display_menu_handles Scope_Ic;//31
	
	struct display_menu_handles Harmonics_Van;//32
	struct display_menu_handles Harmonics_Vbn;//33
	struct display_menu_handles Harmonics_Vcn;//34
	
	struct display_menu_handles Harmonics_Ia;//35
	struct display_menu_handles Harmonics_Ib;//36
	struct display_menu_handles Harmonics_Ic;//37
	
	struct display_menu_handles thd_Vpn;//38
	struct display_menu_handles thd_I;	//39
	
	struct display_menu_handles sym_Vpn;//40
	struct display_menu_handles sym_I;	//41
	
	struct display_menu_handles UNB_V;	//42
	struct display_menu_handles UNB_I;	//43
	
	struct display_menu_handles main_menu;//44	
	
	struct display_menu_handles settings;	//45

	struct display_menu_handles settings_VT;	//46
	struct display_menu_handles settings_CT;	//47
	struct display_menu_handles settings_input;	//48
	struct display_menu_handles settings_output;	//49
	struct display_menu_handles settings_comm;	//50
	struct display_menu_handles settings_energy_reset;	//51
	struct display_menu_handles settings_password;	//51

		
		
	}handle;
	
	
	struct display_menu_handles all[53]; 


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

union flashDataUnion{
	
	struct{
		
	uint32_t vt_primer;
	uint32_t vt_seconder;

	uint32_t ct_primer;
	uint32_t ct_seconder;	
		
	
	
	}data;
	
	uint32_t uBuffer[flashWordSize];
	uint8_t bBuffer[flashByteSize];
	


};

extern union flashDataUnion flash;
extern union flashDataUnion flashNew;



enum saveMenus{
	
		no_save_at_all=0,
		save_option_menu=1,
		saving__menu=2,
		not_saved_menu=3,


};

extern enum saveMenus saveMenu;

extern void (*savingFunctions[])(void);
extern void(* save_fun)(void);



extern struct display_menu_handles Vpn_true_Menu;


uint8_t letter_transfer_14pt(enum letter_codes_14pt x, uint8_t page, uint8_t column);
uint8_t letter_transfer_8pt(enum letter_codes_8pt x, uint8_t page, uint8_t column);
uint8_t digit_transfer_8pt(enum digit_codes_14pt x, uint8_t page, uint8_t column);
void digit_transfer_14pt(enum digit_codes_14pt x, uint8_t page, uint8_t column);
void unit_transfer(enum units x, uint8_t page, uint8_t column);
void menu_unit_transfer(enum menu_units x, uint8_t page, uint8_t column);
void symbol_transfer(enum menu_symbols x, uint8_t page,uint8_t column);

void dynamicDataTripple(struct display_menu_handles menu_item);
void dynamicDataTrippleTotalPower(struct display_menu_handles menu_item);
void staticDataTripple(struct display_menu_handles menu_item);
void staticDataTrippleTotalPower(struct display_menu_handles menu_item);
void dynamicDataSingle(struct display_menu_handles menu_item);
void staticDataSingle(struct display_menu_handles menu_item);

void toMainDetect(struct display_menu_handles menu_item);
void atMainOperation(struct display_menu_handles menu_item);

void toSettingsDetect(struct display_menu_handles menu_item);
void atSettingsOperation(struct display_menu_handles menu_item);


void init_Menu(void);
enum menu_list SELECT_MENU(enum menu_list current,enum input button);
void DISPLAY_MENU(void);


void saveEmAll(void);


void staticData_VT(struct display_menu_handles menu_item);
void dynamicData_VT(struct display_menu_handles menu_item);

void staticData_CT(struct display_menu_handles menu_item);
void dynamicData_CT(struct display_menu_handles menu_item);

#endif
