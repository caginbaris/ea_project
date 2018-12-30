#include "menu_definitions.h"
#include "lcd_definitions.h"
#include "ch_format.h"
#include "measurement_definitions.h"
#include  <string.h>
#include  "aux_functions.h"
#include "flash_api.h"


uint8_t save_lock=0;
uint8_t currentSaveMenu=0;






//saving function pointers

void (*savingFunctions[])(void)={
	
noSave,
saveScreen,
savingScreen,
notSavedScreen

};
void(* save_fun)(void);



struct digit_format  formatDynamicData(float x){
	
	struct digit_format formatted_digit;
	
	if(x<0){formatted_digit.sign=1;x=-x;}else{formatted_digit.sign=0;}

	if(x<_e3){formatted_digit.range=u_N;}
	if(x>=_e3 && x<_e6){formatted_digit.range=u_K;x=x*_em3;}
	if(x>=_e6 && x<_e9){formatted_digit.range=u_M;x=x*_em6;}
	if(x>=_e9 && x<_e12){formatted_digit.range=u_G;x=x*_em9;}

	formatted_digit.fraction=10.0f*(x-(int16_t)x);
	formatted_digit.int100	=(x*_em2); 
	formatted_digit.int10		=(int16_t)(x*_em1) % 10;
	formatted_digit.int1		=((int16_t)x % 10);

	return formatted_digit;
	
}


void loading_bar(uint8_t page,uint8_t columnStart,uint8_t columnEnd, uint8_t EN){


	static uint16_t loadBarCounter=7;
	
	
	uint8_t i;
	

	for(i=columnStart;i<loadBarCounter;i++){
		
		display_buffer[page][i]=0xff;
		display_buffer[page][i+1]=0xff;
		display_buffer[page][i+2]=0xff;
		display_buffer[page][i+3]=0xff;
		display_buffer[page][i+4]=0xff;
		

	}
	
	loadBarCounter+=5;
		
	if(loadBarCounter>columnEnd){loadBarCounter=columnEnd+1;}
	if(!EN){loadBarCounter=0;}



}


void noSave(){


}


void saveScreen(){

	enum letter_codes_8pt saveORnot[]={k,a,y,d,e,t};
	static uint32_t timeOut=0;
	
	static uint8_t pbcheck=1;
	static uint32_t pbtimeOut=0;
	
	uint8_t i;
	uint8_t column=50;
	
	
	
	clearColumns(1,0,127);
	clearColumns(2,0,127);
	clearColumns(3,0,127);
	clearColumns(4,0,127);
	clearColumns(5,0,127);
	clearColumns(6,0,127);
	clearColumns(7,0,127);
	
	
	//question
	
	for(i=0;i<6;i++){
		
	column=letter_transfer_8pt(saveORnot[i],2,column);
	
	}
	
	symbol_transfer(menu_qmark,2,column);

	
	symbol_transfer(menu_cross,7,88);
	symbol_transfer(menu_tick,7,119);
	
	pbcheck=off_delay(0,pbcheck,5,&pbtimeOut);
	
	
	save_lock=off_delay(0,save_lock,200,&timeOut);
	if(save_lock==0){current_menu=settings_menu;currentSaveMenu=not_saved_menu;pbcheck=1;}
	
	if(pressed_button==up_pressed && pbcheck==0){currentSaveMenu=saving__menu;pbcheck=1;}
	if(pressed_button==down_pressed && pbcheck==0){currentSaveMenu=not_saved_menu;pbcheck=1;}

}
	



void savingScreen(){

	enum letter_codes_8pt saving[]={k,a,y,d,e,d,i,l,i,y,o,r};
	static uint32_t timeOut=0;

	
	uint8_t i;
	uint8_t column=10;
	

	
	clearColumns(1,0,127);
	clearColumns(2,0,127);
	clearColumns(3,0,127);
	clearColumns(4,0,127);
	clearColumns(5,0,127);
	clearColumns(6,0,127);
	clearColumns(7,0,127);
	
	
	//saving
	
	for(i=0;i<12;i++){
		
	column=letter_transfer_8pt(saving[i],2,column);
	
	}
	
	
	
	
	save_lock=off_delay(0,save_lock,20,&timeOut);
	loading_bar(6,7,120,save_lock);
	
	if(save_lock==0){
	
	current_menu=settings_menu;
	
	currentSaveMenu=no_save_at_all;
		
	flash=flashNew;
		
	flashWrite();
	

	
	}
	
	
	
	
	
}



void notSavedScreen(){

	enum letter_codes_8pt notSaved[]={k,a,y,d,e,d,i,l,m,e,d,i};
	static uint32_t timeOut=0;

	
	uint8_t i;
	uint8_t column=10;
	

	
	clearColumns(1,0,127);
	clearColumns(2,0,127);
	clearColumns(3,0,127);
	clearColumns(4,0,127);
	clearColumns(5,0,127);
	clearColumns(6,0,127);
	clearColumns(7,0,127);
	
	
	for(i=0;i<12;i++){
		
	column=letter_transfer_8pt(notSaved[i],2,column);
	
	}
	
	
	save_lock=off_delay(0,save_lock,20,&timeOut);
	if(save_lock==0){
	
	current_menu=settings_menu;currentSaveMenu=no_save_at_all;
	flashNew=flash;
		
	
	}
	
	
}


void saveEmAll(void){


		
		save_fun=savingFunctions[currentSaveMenu];
		save_fun();
		
	

}





	
void dynamicDataTripple(struct display_menu_handles menu_item){
	
	#if 1
	struct digit_format lcd_row1={0},lcd_row2={0},lcd_row3={0};
	float *fp;

	uint8_t page,column; 
	

	
	
	fp=menu_item.values;
	
	//format-unit
	lcd_row1=formatDynamicData(*fp);
	lcd_row2=formatDynamicData(*(fp+1));
	lcd_row3=formatDynamicData(*(fp+2));
	
	//digit and unit transfer
	
	column=38;
	
	page=1;
	
	//first row
	if(lcd_row1.sign)															{	put_minus(page,column-6);};
	if(lcd_row1.int100!=0											)		{	digit_transfer_14pt(lcd_row1.int100,page,column);}
	if(lcd_row1.int100!=0 || lcd_row1.int10!=0	)	{ digit_transfer_14pt(lcd_row1.int10,page,column+digit_width_14pt);}
																									digit_transfer_14pt(lcd_row1.int1,page,column+2*digit_width_14pt);
																									put_dot2x2(page+1,column+3*digit_width_14pt);
																									digit_transfer_14pt(lcd_row1.fraction,page,column+(3*digit_width_14pt+5)); 
	
	
	if(lcd_row1.range==u_K){unit_transfer(u_K,page,column+(3*digit_width_14pt+digit_width_14pt));}
	if(lcd_row1.range==u_M){unit_transfer(u_M,page,column+(3*digit_width_14pt+digit_width_14pt));}	
	if(lcd_row1.range==u_G){unit_transfer(u_G,page,column+(3*digit_width_14pt+digit_width_14pt));}

	page=3;
	//second row
	if(lcd_row2.sign)													 {	put_minus(page,column-5);}
	if(lcd_row2.int100!=0											){	digit_transfer_14pt(lcd_row2.int100,page,column);}
	if(lcd_row2.int100!=0 || lcd_row2.int10!=0){ 	digit_transfer_14pt(lcd_row2.int10,page,column+digit_width_14pt);}
																								digit_transfer_14pt(lcd_row2.int1,page,column+2*digit_width_14pt);
																								put_dot2x2(page+1,column+3*digit_width_14pt);
																								digit_transfer_14pt(lcd_row2.fraction,page,column+(3*digit_width_14pt+5)); 
	
	
	if(lcd_row2.range==u_K){unit_transfer(u_K,page,column+(3*digit_width_14pt+digit_width_14pt));}
	if(lcd_row2.range==u_M){unit_transfer(u_M,page,column+(3*digit_width_14pt+digit_width_14pt));}	
	if(lcd_row2.range==u_G){unit_transfer(u_G,page,column+(3*digit_width_14pt+digit_width_14pt));}		
	

	page=5;
	//third row
	if(lcd_row3.sign)															{	put_minus(page,column-5);}
	if(lcd_row3.int100!=0											)		{	digit_transfer_14pt(lcd_row3.int100,page,column);}
	if(lcd_row3.int100!=0 || lcd_row3.int10!=0	)	{ digit_transfer_14pt(lcd_row3.int10,page,column+digit_width_14pt);}
																								digit_transfer_14pt(lcd_row3.int1,page,column+2*digit_width_14pt);
																								put_dot2x2(page+1,column+3*digit_width_14pt);
																								digit_transfer_14pt(lcd_row3.fraction,page,column+(3*digit_width_14pt+5)); 
	
	
	if(lcd_row3.range==u_K){unit_transfer(u_K,page,column+(3*digit_width_14pt+digit_width_14pt));}
	if(lcd_row3.range==u_M){unit_transfer(u_M,page,column+(3*digit_width_14pt+digit_width_14pt));}	
	if(lcd_row3.range==u_G){unit_transfer(u_G,page,column+(3*digit_width_14pt+digit_width_14pt));}		
	
	
	#endif
									

};

void dynamicDataTrippleTotalPower(struct display_menu_handles menu_item){
	
	#if 1
	struct digit_format lcd_row1={0},lcd_row2={0},lcd_row3={0};


	uint8_t page,column; 
	

	
	

	
	//format-unit
	lcd_row1=formatDynamicData(power_iq.Power.Ptotal);
	lcd_row2=formatDynamicData(power_iq.Power.Qtotal);
	lcd_row3=formatDynamicData(power_iq.Power.Stotal);
	
	//digit and unit transfer
	
	column=38;
	
	page=1;
	
	//first row
	if(lcd_row1.sign)															{	put_minus(page,column-6);};
	if(lcd_row1.int100!=0											)		{	digit_transfer_14pt(lcd_row1.int100,page,column);}
	if(lcd_row1.int100!=0 || lcd_row1.int10!=0	)	{ digit_transfer_14pt(lcd_row1.int10,page,column+digit_width_14pt);}
																									digit_transfer_14pt(lcd_row1.int1,page,column+2*digit_width_14pt);
																									put_dot2x2(page+1,column+3*digit_width_14pt);
																									digit_transfer_14pt(lcd_row1.fraction,page,column+(3*digit_width_14pt+5)); // 5 for dot space
	
	
	if(lcd_row1.range==u_K){unit_transfer(u_K,page,column+(3*digit_width_14pt+digit_width_14pt));}
	if(lcd_row1.range==u_M){unit_transfer(u_M,page,column+(3*digit_width_14pt+digit_width_14pt));}	
	if(lcd_row1.range==u_G){unit_transfer(u_G,page,column+(3*digit_width_14pt+digit_width_14pt));}

	page=3;
	//second row
	if(lcd_row2.sign)													 {	put_minus(page,column-5);}
	if(lcd_row2.int100!=0											){	digit_transfer_14pt(lcd_row2.int100,page,column);}
	if(lcd_row2.int100!=0 || lcd_row2.int10!=0){ 	digit_transfer_14pt(lcd_row2.int10,page,column+digit_width_14pt);}
																								digit_transfer_14pt(lcd_row2.int1,page,column+2*digit_width_14pt);
																								put_dot2x2(page+1,column+3*digit_width_14pt);
																								digit_transfer_14pt(lcd_row2.fraction,page,column+(3*digit_width_14pt+5)); //5 for dot space
	
	
	if(lcd_row2.range==u_K){unit_transfer(u_K,page,column+(3*digit_width_14pt+digit_width_14pt));}
	if(lcd_row2.range==u_M){unit_transfer(u_M,page,column+(3*digit_width_14pt+digit_width_14pt));}	
	if(lcd_row2.range==u_G){unit_transfer(u_G,page,column+(3*digit_width_14pt+digit_width_14pt));}		
	

	page=5;
	//third row
	if(lcd_row3.sign)															{	put_minus(page,column-5);}
	if(lcd_row3.int100!=0											)		{	digit_transfer_14pt(lcd_row3.int100,page,column);}
	if(lcd_row3.int100!=0 || lcd_row3.int10!=0	)	{ digit_transfer_14pt(lcd_row3.int10,page,column+digit_width_14pt);}
																								digit_transfer_14pt(lcd_row3.int1,page,column+2*digit_width_14pt);
																								put_dot2x2(page+1,column+3*digit_width_14pt);
																								digit_transfer_14pt(lcd_row3.fraction,page,column+(3*digit_width_14pt+5)); // 5 for dot space
	
	
	if(lcd_row3.range==u_K){unit_transfer(u_K,page,column+(3*digit_width_14pt+digit_width_14pt));}
	if(lcd_row3.range==u_M){unit_transfer(u_M,page,column+(3*digit_width_14pt+digit_width_14pt));}	
	if(lcd_row3.range==u_G){unit_transfer(u_G,page,column+(3*digit_width_14pt+digit_width_14pt));}		
	
	
	#endif
									

};



void staticDataTripple(struct display_menu_handles menu_item){
	
	uint8_t i;
	uint8_t column=1;
	uint8_t page=0;
	
	#if 1

	for(i=0;i<21;i++){
		
	column=letter_transfer_8pt(menu_item.title[i],page,column);
	
		
	}
	
	line_highlighter(0,128);
	
	column=0;
	
	page=1;
	
	column=letter_transfer_14pt(menu_item.first_line[0],page,column);
	column=letter_transfer_14pt(menu_item.first_line[1],page,column);
	column=letter_transfer_14pt(menu_item.first_line[2],page,column);
	
	menu_unit_transfer(menu_item.menu_chars[0],page, menu_unit_vertical_position);
	
	
	for(i=1;i<4;i++){
		
		
		if(menu_item.menu_chars[i]==m_){break;}
		if(menu_item.menu_chars[0]==m_W){menu_unit_transfer(menu_item.menu_chars[i],page, menu_unit_vertical_position+11);}else{
		
		menu_unit_transfer(menu_item.menu_chars[i],page, menu_unit_vertical_position+7*i);
			
		}
		
	}
	
	
	column=0;
	
	page=3;
	
	column=letter_transfer_14pt(menu_item.second_line[0],page,column);
	column=letter_transfer_14pt(menu_item.second_line[1],page,column);
	column=letter_transfer_14pt(menu_item.second_line[2],page,column);
	
	
		menu_unit_transfer(menu_item.menu_chars[0],page, menu_unit_vertical_position);
	
	
	for(i=1;i<4;i++){
		
		
		if(menu_item.menu_chars[i]==m_){break;}
		if(menu_item.menu_chars[0]==m_W){menu_unit_transfer(menu_item.menu_chars[i],page, menu_unit_vertical_position+11);}else{
		
		menu_unit_transfer(menu_item.menu_chars[i],page, menu_unit_vertical_position+7*i);
			
		}
		
	}
	
	
	column=0;
	
	page=5;
	
	column=letter_transfer_14pt(menu_item.third_line[0],page,column);
	column=letter_transfer_14pt(menu_item.third_line[1],page,column);
	column=letter_transfer_14pt(menu_item.third_line[2],page,column);
	
	menu_unit_transfer(menu_item.menu_chars[0],page, menu_unit_vertical_position);
	
	
	for(i=1;i<4;i++){
		
		
		if(menu_item.menu_chars[i]==m_){break;}
		if(menu_item.menu_chars[0]==m_W){menu_unit_transfer(menu_item.menu_chars[i],page, menu_unit_vertical_position+11);}else{
		
		menu_unit_transfer(menu_item.menu_chars[i],page, menu_unit_vertical_position+7*i);
			
		}
		
	}
	

	
	

	symbol_transfer(menu_item.symbol[0],7,1);
	symbol_transfer(menu_item.symbol[1],7,28);
	symbol_transfer(menu_item.symbol[2],7,59);
	symbol_transfer(menu_item.symbol[3],7,88);
	symbol_transfer(menu_item.symbol[4],7,119);
	
	
	//menu units
	
	
	#endif
	
	
}

void staticDataTrippleTotalPower(struct display_menu_handles menu_item){
	
	uint8_t i;
	uint8_t column=1;
	uint8_t page=0;
	
	#if 1

	for(i=0;i<21;i++){
		
	column=letter_transfer_8pt(menu_item.title[i],page,column);
	
		
	}
	
	line_highlighter(0,128);
	
	column=0;
	
	page=1;
	
	column=letter_transfer_14pt(menu_item.first_line[0],page,column);
	column=letter_transfer_14pt(menu_item.first_line[1],page,column);
	column=letter_transfer_14pt(menu_item.first_line[2],page,column);
	
	menu_unit_transfer(m_W,page, menu_unit_vertical_position);

			
	
	column=0;
	
	page=3;
	
	column=letter_transfer_14pt(menu_item.second_line[0],page,column);
	column=letter_transfer_14pt(menu_item.second_line[1],page,column);
	column=letter_transfer_14pt(menu_item.second_line[2],page,column);
	
	
		menu_unit_transfer(m_V,page, menu_unit_vertical_position);//****
		menu_unit_transfer(m_A,page, menu_unit_vertical_position+7);
		menu_unit_transfer(m_R,page, menu_unit_vertical_position+14);
	
	
	column=0;
	
	page=5;
	
	column=letter_transfer_14pt(menu_item.third_line[0],page,column);
	column=letter_transfer_14pt(menu_item.third_line[1],page,column);
	column=letter_transfer_14pt(menu_item.third_line[2],page,column);
	
	
	menu_unit_transfer(m_V,page, menu_unit_vertical_position);
	menu_unit_transfer(m_A,page, menu_unit_vertical_position+7);
	
	
	

	
	

	symbol_transfer(menu_item.symbol[0],7,1);
	symbol_transfer(menu_item.symbol[1],7,28);
	symbol_transfer(menu_item.symbol[2],7,59);
	symbol_transfer(menu_item.symbol[3],7,88);
	symbol_transfer(menu_item.symbol[4],7,119);
	
	
	//menu units
	
	
	#endif
	
	
}




void dynamicDataSingle(struct display_menu_handles menu_item){
	
	#if 1
	struct digit_format lcd_row2={0};
	float *fp;

	uint8_t page,column; 
	


	fp=menu_item.values;
	
	//format-unit
	lcd_row2=formatDynamicData(*fp);
	//digit and unit transfer
	
	column=38;
	

	page=3;
	//second row
	if(lcd_row2.int100!=0											){	digit_transfer_14pt(lcd_row2.int100,page,column);}
	if(lcd_row2.int100!=0 || lcd_row2.int10!=0){ 	digit_transfer_14pt(lcd_row2.int10,page,column+digit_width_14pt);}
																								digit_transfer_14pt(lcd_row2.int1,page,column+2*digit_width_14pt);
																								put_dot2x2(page+1,column+3*digit_width_14pt);
																								digit_transfer_14pt(lcd_row2.fraction,page,column+(3*digit_width_14pt+5)); // 5 for dot space
	
	
	if(lcd_row2.range==u_K){unit_transfer(u_K,page,column+(3*digit_width_14pt+digit_width_14pt));}
	if(lcd_row2.range==u_M){unit_transfer(u_M,page,column+(3*digit_width_14pt+digit_width_14pt));}	
	if(lcd_row2.range==u_G){unit_transfer(u_G,page,column+(3*digit_width_14pt+digit_width_14pt));}		
	
	
	
	
	#endif
									

};
	
void staticDataSingle(struct display_menu_handles menu_item){
	
	uint8_t i;
	uint8_t column=1;
	uint8_t page=0;
	
	#if 1

	for(i=0;i<21;i++){
		
	column=letter_transfer_8pt(menu_item.title[i],page,column);
	
		
	}
	
	line_highlighter(0,128);
	

	
	
	column=0;
	
	page=3;
	
	column=letter_transfer_14pt(menu_item.second_line[0],page,column);
	column=letter_transfer_14pt(menu_item.second_line[1],page,column);
	column=letter_transfer_14pt(menu_item.second_line[2],page,column);
	
	
		menu_unit_transfer(menu_item.menu_chars[0],page, menu_unit_vertical_position);
	
	
	for(i=1;i<4;i++){
		
		
		if(menu_item.menu_chars[i]==m_){break;}
		if(menu_item.menu_chars[0]==m_W){menu_unit_transfer(menu_item.menu_chars[i],page, menu_unit_vertical_position+11);}else{
		
		menu_unit_transfer(menu_item.menu_chars[i],page, menu_unit_vertical_position+7*i);
			
		}
		
	}
	
	
	
	

	

	
	

	symbol_transfer(menu_item.symbol[0],7,1);
	symbol_transfer(menu_item.symbol[1],7,28);
	symbol_transfer(menu_item.symbol[2],7,59);
	symbol_transfer(menu_item.symbol[3],7,88);
	symbol_transfer(menu_item.symbol[4],7,119);
	
	
	//menu units
	
	
	#endif
	
	
}



void toMainDetect(struct display_menu_handles menu_item){
	

	
	switch(previous_menu){
		
	
		
		case Vpn_true:									main_menu_entry=	Vpn_main; break;
		case Vpn_fund:									main_menu_entry=	Vpn_main; break;
		
		case Vpp_true:									main_menu_entry=	Vpp_main; break;
		case Vpp_fund:									main_menu_entry=	Vpp_main; break;
		
		case Ip_true:										main_menu_entry=	Ip_main; break;
		case Ip_fund:										main_menu_entry=	Ip_main; break;
		
		case Active_Power		:						main_menu_entry=	Active_Power_main; break;
		case Reactive_Power	:						main_menu_entry=	Reactive_Power_main; break;
		case Apparent_Power	:						main_menu_entry=	Apparent_Power_main; break;
		case Total_Power		:						main_menu_entry=	Total_Power_main; break;
		
		case Power_Factors_fund:				main_menu_entry=	Power_Factors_main; break;
		case Total_Power_Factor_fund:		main_menu_entry=	Power_Factors_main; break;
		
		case Power_Ratios:							main_menu_entry=	Power_Ratios_main; break;
		case Total_Power_Ratios:				main_menu_entry=	Power_Ratios_main; break;
		
		case Active_Energy_import:			main_menu_entry=	Active_Energy_main; break;
		case Active_Energy_Total_import:main_menu_entry=	Active_Energy_main; break;
		case Active_Energy_export:			main_menu_entry=	Active_Energy_main; break;
		case Active_Energy_Total_export:main_menu_entry=	Active_Energy_main; break;
		
		case Reactive_Energy_import:			main_menu_entry=	Reactive_Energy_main; break;
		case Reactive_Energy_Total_import:main_menu_entry=	Reactive_Energy_main; break;
		case Reactive_Energy_export:			main_menu_entry=	Reactive_Energy_main; break;
		case Reactive_Energy_Total_export:main_menu_entry=	Reactive_Energy_main; break;

		
		case Apparent_Energy:						main_menu_entry=	Apparent_Energy_main; break;
		case Apparent_Energy_Total:			main_menu_entry=	Apparent_Energy_main; break;
		
		case Scope_Van:									main_menu_entry=	Scope_main; break;
		case Scope_Vbn:									main_menu_entry=	Scope_main; break;
		case Scope_Vcn:									main_menu_entry=	Scope_main; break;
		case Scope_Ia:									main_menu_entry=	Scope_main; break;
		case Scope_Ib:									main_menu_entry=	Scope_main; break;
		case Scope_Ic:									main_menu_entry=	Scope_main; break;
		
		case Harmonics_Van:							main_menu_entry=	Harmonics_Main; break;
		case Harmonics_Vbn:							main_menu_entry=	Harmonics_Main; break;
		case Harmonics_Vcn:							main_menu_entry=	Harmonics_Main; break;
		
		case Harmonics_Ia:							main_menu_entry=	Harmonics_Main; break;
		case Harmonics_Ib:							main_menu_entry=	Harmonics_Main; break;
		case Harmonics_Ic:							main_menu_entry=	Harmonics_Main; break;
		
		case thd_Vpn:										main_menu_entry=	THD_main; break;
		case thd_I:										  main_menu_entry=	THD_main; break;
		
		case sym_Vpn:										main_menu_entry=	Sym_main; break;
		case sym_I:										  main_menu_entry=	Sym_main; break;
		
		case unb_Vpn:										main_menu_entry=	Unb_main; break;
		case unb_I:										  main_menu_entry=	Unb_main; break;
		
		
		default:main_menu_entry=settings_main;break;
		
	}
	

	
	current_menu=main_menu ;
	pressed_button=invalid;

}

void toSettingsDetect(struct display_menu_handles menu_item){
	

	
	switch(previous_menu){
		
	
		
		case set_VT:								    setting_menu_entry=	setting_VT; break;
		case set_CT:									  setting_menu_entry=	setting_CT; break;
		case set_input:								  setting_menu_entry=	setting_input; break;
		case set_output:								setting_menu_entry=	setting_output; break;
		case set_comm:								  setting_menu_entry=	setting_comm; break;
		case set_display:								setting_menu_entry=	setting_comm; break;
		case set_energy_reset:					setting_menu_entry=	setting_energy_reset; break;
		case set_password:					    setting_menu_entry=	setting_password; break;
		
		default:setting_menu_entry=setting_VT;break;
		
	}
	

	
	current_menu=settings_menu ;
	pressed_button=invalid;

}

void atMainOperation(struct display_menu_handles menu_item){
	
	uint8_t i;
	uint8_t column;
	
	
	
	
	
	enum main_menu_list current_entry;
	enum main_menu_list last_menu_entry=pos_guard;
	
	
	

	if(pressed_button==enter_pressed){
		
		switch(main_menu_entry){
		
		case Vpn_main:											current_menu=Vpn_true; 									break;
		case Vpp_main:											current_menu=Vpp_true; 									break;
		case Ip_main:												current_menu=Ip_true; 									break;
		case Active_Power_main:							current_menu=Active_Power; 							break;
		case Reactive_Power_main:						current_menu=Reactive_Power;						break;
		case Apparent_Power_main:						current_menu=Apparent_Power; 						break;
		case Total_Power_main:							current_menu=Total_Power; 							break;
		case Power_Factors_main:						current_menu=Power_Factors_fund; 				break;
		case Power_Ratios_main:							current_menu=Power_Ratios;							break;				
		case Active_Energy_main:						current_menu=Active_Energy_import;			break;
		case Reactive_Energy_main:					current_menu=Reactive_Energy_import;		break;
		case Apparent_Energy_main:					current_menu=Apparent_Energy;						break;
		case Scope_main:										current_menu=Scope_Van; 								break;
		case Harmonics_Main:								current_menu=Harmonics_Ia;							break;
		case THD_main:											current_menu=thd_Vpn;										break;	
		case Sym_main:											current_menu=sym_Vpn;										break;
		case Unb_main:											current_menu=unb_Vpn;										break;
		case settings_main:									current_menu=settings_menu;							break;	
			
		default:	;break;
		
		}
	
	}
	
	if(pressed_button==down_pressed){
	
		main_menu_entry++;
		
	
	}
	
	if(pressed_button==up_pressed){
	
		main_menu_entry--;
		
	
	}
	
	
	if(main_menu_entry>last_menu_entry){main_menu_entry=start_bar;}
	if(main_menu_entry<start_bar){main_menu_entry=last_menu_entry;}
	
	current_entry=main_menu_entry-1+last_menu_entry; 
	current_entry%=last_menu_entry;
	
	
	
	main_lines.row1=&main_menu_entries[current_entry][0];current_entry++;current_entry%=last_menu_entry;//if(current_entry>last_menu_entry){current_entry=start_bar;};
	main_lines.row2=&main_menu_entries[current_entry][0];current_entry++;current_entry%=last_menu_entry;//if(current_entry>last_menu_entry){current_entry=start_bar;};
	main_lines.row3=&main_menu_entries[current_entry][0];current_entry++;current_entry%=last_menu_entry;//if(current_entry>last_menu_entry){current_entry=start_bar;};
	main_lines.row4=&main_menu_entries[current_entry][0];current_entry++;current_entry%=last_menu_entry;//if(current_entry>last_menu_entry){current_entry=start_bar;};
	main_lines.row5=&main_menu_entries[current_entry][0];current_entry++;current_entry%=last_menu_entry;//if(current_entry>last_menu_entry){current_entry=start_bar;};
	main_lines.row6=&main_menu_entries[current_entry][0];current_entry++;current_entry%=last_menu_entry;//if(current_entry>last_menu_entry){current_entry=start_bar;};
	main_lines.row7=&main_menu_entries[current_entry][0];
	
	
	
	for(i=1;i<21;i++){column=letter_transfer_8pt(*main_lines.row1++,0,column);}column=1;
	for(i=1;i<21;i++){column=letter_transfer_8pt(*main_lines.row2++,1,column);}column=1;
	for(i=1;i<21;i++){column=letter_transfer_8pt(*main_lines.row3++,2,column);}column=1;
	for(i=1;i<21;i++){column=letter_transfer_8pt(*main_lines.row4++,3,column);}column=1;
	for(i=1;i<21;i++){column=letter_transfer_8pt(*main_lines.row5++,4,column);}column=1;
	for(i=1;i<21;i++){column=letter_transfer_8pt(*main_lines.row6++,5,column);}column=1;
	for(i=1;i<21;i++){column=letter_transfer_8pt(*main_lines.row7++,6,column);}column=1;
	
	
	symbol_transfer(MENU.handle.main_menu.symbol[0],7,1);
	symbol_transfer(MENU.handle.main_menu.symbol[1],7,28);
	symbol_transfer(MENU.handle.main_menu.symbol[2],7,59);
	symbol_transfer(MENU.handle.main_menu.symbol[3],7,88);
	symbol_transfer(MENU.handle.main_menu.symbol[4],7,119);
	
	
	line_highlighter(1,128);
	
	
	
}

void atSettingsOperation(struct display_menu_handles menu_item){
	
	uint8_t i;
	uint8_t column;
	
	
	
	
	
	enum setting_menu_list current_entry;
	enum setting_menu_list last_menu_entry=setting_pos_guard;
	
	
	

	if(pressed_button==enter_pressed){
		
		switch(setting_menu_entry){
		
		case setting_VT:					current_menu=set_VT; 						break;
		case setting_CT:					current_menu=set_CT; 						break;
		case setting_input:				current_menu=set_input; 				break;
		case setting_output:			current_menu=set_output; 				break;
		case setting_comm:				current_menu=set_comm; 					break;
		case setting_display:			current_menu=set_display; 			break;
		case setting_energy_reset:current_menu=set_energy_reset; 	break;
		case setting_password:		current_menu=set_password; 			break;

			
		default:	;break;
		
		}
	
	}
	
	if(pressed_button==left_pressed){
	
		current_menu=main_menu;
	
	}
	
	if(pressed_button==down_pressed){
	
		setting_menu_entry++;
		
	
	}
	
	if(pressed_button==up_pressed){
	
		setting_menu_entry--;
		
	
	}
	
	
	
	if(setting_menu_entry>last_menu_entry){setting_menu_entry=setting_start_bar;}
	if(setting_menu_entry<start_bar){setting_menu_entry=last_menu_entry;}
	
	current_entry=setting_menu_entry-1+last_menu_entry; 
	current_entry%=last_menu_entry;
	
	
	
	setting_lines.row1=&setting_menu_entries[current_entry][0];current_entry++;current_entry%=last_menu_entry;//if(current_entry>last_menu_entry){current_entry=start_bar;};
	setting_lines.row2=&setting_menu_entries[current_entry][0];current_entry++;current_entry%=last_menu_entry;//if(current_entry>last_menu_entry){current_entry=start_bar;};
	setting_lines.row3=&setting_menu_entries[current_entry][0];current_entry++;current_entry%=last_menu_entry;//if(current_entry>last_menu_entry){current_entry=start_bar;};
	setting_lines.row4=&setting_menu_entries[current_entry][0];current_entry++;current_entry%=last_menu_entry;//if(current_entry>last_menu_entry){current_entry=start_bar;};
	setting_lines.row5=&setting_menu_entries[current_entry][0];current_entry++;current_entry%=last_menu_entry;//if(current_entry>last_menu_entry){current_entry=start_bar;};
	setting_lines.row6=&setting_menu_entries[current_entry][0];current_entry++;current_entry%=last_menu_entry;//if(current_entry>last_menu_entry){current_entry=start_bar;};
	setting_lines.row7=&setting_menu_entries[current_entry][0];
	
	
	
	for(i=1;i<21;i++){column=letter_transfer_8pt(*setting_lines.row1++,0,column);}column=1;
	for(i=1;i<21;i++){column=letter_transfer_8pt(*setting_lines.row2++,1,column);}column=1;
	for(i=1;i<21;i++){column=letter_transfer_8pt(*setting_lines.row3++,2,column);}column=1;
	for(i=1;i<21;i++){column=letter_transfer_8pt(*setting_lines.row4++,3,column);}column=1;
	for(i=1;i<21;i++){column=letter_transfer_8pt(*setting_lines.row5++,4,column);}column=1;
	for(i=1;i<21;i++){column=letter_transfer_8pt(*setting_lines.row6++,5,column);}column=1;
	for(i=1;i<21;i++){column=letter_transfer_8pt(*setting_lines.row7++,6,column);}column=1;
	
	
	symbol_transfer(MENU.handle.settings.symbol[0],7,1);
	symbol_transfer(MENU.handle.settings.symbol[1],7,28);
	symbol_transfer(MENU.handle.settings.symbol[2],7,59);
	symbol_transfer(MENU.handle.settings.symbol[3],7,88);
	symbol_transfer(MENU.handle.settings.symbol[4],7,119);
	
	
	line_highlighter(1,128);
	
	
	
}



enum menu_list SELECT_MENU(enum menu_list current,enum input button){
	
	uint8_t i;
	enum menu_list new_menu;
	
	previous_menu=current_menu;
	new_menu=current;
	
	for(i=0;i<TotalMenuTransitionNo;i++){
				
			if( menu_transition[i].current_menu==current &&
					menu_transition[i].pressed==button){
						
					new_menu=	menu_transition[i].next_menu;
					break;
			}
			
	}
	
	
	
	
	
	return new_menu;

}


void DISPLAY_MENU(){
	
	uint8_t scope_menus=0,harmonic_menus=0;
	
	static uint8_t scope_menu_transition=0;

	struct display_menu_handles local_menu=Vpn_true_Menu;
	
	
	local_menu=MENU.all[current_menu];
	
	
	switch(current_menu){
	
		case Scope_Van:scope_menus=1;break;
		case Scope_Vbn:scope_menus=1;break;
		case Scope_Vcn:scope_menus=1;break;
		
		case Scope_Ia:scope_menus=1;break;
		case Scope_Ib:scope_menus=1;break;
		case Scope_Ic:scope_menus=1;break;
		
		case Harmonics_Van:harmonic_menus=1;break;
		case Harmonics_Vbn:harmonic_menus=1;break;
		case Harmonics_Vcn:harmonic_menus=1;break;
		
		case Harmonics_Ia:harmonic_menus=1;break;
		case Harmonics_Ib:harmonic_menus=1;break;
		case Harmonics_Ic:harmonic_menus=1;break;
		

		
		default:scope_menus=0;harmonic_menus=0;scope_menu_transition=1;
	
	}
	
	
	if(!scope_menus){
		
	if((previous_menu!=current_menu) || (current_menu==main_menu)|| (current_menu==settings_menu)|| (harmonic_menus==1)){
	
	memset(display_buffer,0,1024); }
	
	
	}else{
	
	
	if(scope_menu_transition){memset(display_buffer,0,1024);scope_menu_transition=0;}	
		
	}
	
	
	
	
	
	
	if((previous_menu!=current_menu) || harmonic_menus==1 ){
	
	MENU.all[current_menu].staticDataTransfer(local_menu);
	
	}
	
	
	
	
	MENU.all[current_menu].dynamicDataTransfer(local_menu);
	
	saveEmAll();
	
};

void staticData_VT(struct display_menu_handles menu_item){

	enum letter_codes_8pt primary[8]=  {p,r,i,m,e,r,_,_};
	enum letter_codes_8pt secondary[8]={s,e,k,o,n,d,e,r};
	
	uint8_t i;
	uint8_t column=1;
	uint8_t page=0;
	


	for(i=0;i<21;i++){
		
	column=letter_transfer_8pt(menu_item.title[i],page,column);
	
		
	}
	
	line_highlighter(0,128);
	
	column=0;
	page=2;
	
	for(i=0;i<8;i++){
		
	column=letter_transfer_8pt(primary[i],page,column);
	
	}
	
	
	column=0;
	page=4;
	for(i=0;i<8;i++){
		
	column=letter_transfer_8pt(secondary[i],page,column);
		
	}
	
	
	symbol_transfer(menu_item.symbol[0],7,1);
	symbol_transfer(menu_item.symbol[1],7,28);
	symbol_transfer(menu_item.symbol[2],7,59);
	symbol_transfer(menu_item.symbol[3],7,88);
	symbol_transfer(menu_item.symbol[4],7,119);
	
	
	
};


void dynamicData_VT(struct display_menu_handles menu_item){
	
	static enum digit_codes_14pt vt_digit_p[6]={0};
  static enum digit_codes_14pt vt_digit_s[6]={0};

	static uint8_t ord=0;//order of  digits 0...5
	static uint8_t sel=1;//primary/secondary selection
	static uint8_t entered=0;
	
	uint8_t i;
	uint8_t column=80;
	
	
	
	
	
	clearColumns(2,79,127);
	clearColumns(4,79,127);
	
	column=80;
		
	for(i=0;i<6;i++){ //digit tranfer
	
	digit_transfer_8pt(vt_digit_p[i],2,column);
	column+=8;	

	}
		
		
	column=80;
		
		
	for(i=0;i<6;i++){ //digit tranfer
	
	digit_transfer_8pt(vt_digit_s[i],4,column);
	column+=8;	

	}
	
	
	
	
	if(!entered && save_lock==0){
	
		vt_digit_p[5]=flashData2LCD(flash.data.vt_primer,1);
		vt_digit_p[4]=flashData2LCD(flash.data.vt_primer,2);
		vt_digit_p[3]=flashData2LCD(flash.data.vt_primer,3);
		vt_digit_p[2]=flashData2LCD(flash.data.vt_primer,4);
		vt_digit_p[1]=flashData2LCD(flash.data.vt_primer,5);
		vt_digit_p[0]=flashData2LCD(flash.data.vt_primer,6);
		

		
		vt_digit_s[5]=flashData2LCD(flash.data.vt_seconder,1);
		vt_digit_s[4]=flashData2LCD(flash.data.vt_seconder,2);
		vt_digit_s[3]=flashData2LCD(flash.data.vt_seconder,3);
		vt_digit_s[2]=flashData2LCD(flash.data.vt_seconder,4);
		vt_digit_s[1]=flashData2LCD(flash.data.vt_seconder,5);
		vt_digit_s[0]=flashData2LCD(flash.data.vt_seconder,6);
		

	}
	
	
	if(pressed_button==enter_pressed){sel^=1;ord=0;entered=1;}
	

	
	
	if(sel==0 && entered==1){//primer side start
		
	if(pressed_button==left_pressed){  // left is plus @VT
	
	
	if(++vt_digit_p[ord]>_9){vt_digit_p[ord]=_0;}	
		
	}
	
	if(pressed_button==right_pressed){ // left is plus @VT
	
	
	if(--vt_digit_p[ord]==_m1){vt_digit_p[ord]=_9;}	
		
	}
	
	
	if(pressed_button==down_pressed){  // down is right pos change
	
	ord++;
	if(ord>_5){ord=0;}	
		
	}
	
	
	put_cursor(2,79+ord*8,7);
	
	
	}//primer side end
	
	
	
	if(sel==1 && entered==1){//seconder side start
		
		
	//cau	
		
		
	if(pressed_button==left_pressed){  // left is plus @VT
	
	
	if(++vt_digit_s[ord]>_9){vt_digit_s[ord]=_0;}	
		
	}
	
	if(pressed_button==right_pressed){ // left is plus @VT
	
	
	if(--vt_digit_s[ord]==_m1){vt_digit_s[ord]=_9;}	
		
	}
	
	
	if(pressed_button==down_pressed){  // down is right pos change
	
	ord++;
	if(ord>_5){ord=0;}	
		
	}
	
	put_cursor(4,79+ord*8,7);	
		
	}//seconder side end
	
	
	
		

	if(pressed_button==up_pressed && save_lock==0){ 
	
	
		
	flashNew.data.vt_primer=screenData2flash  (vt_digit_p,6);
	flashNew.data.vt_seconder=screenData2flash(vt_digit_s,6);

	if((  flashNew.data.vt_primer  !=flash.data.vt_primer) || 
		 (  flashNew.data.vt_seconder!=flash.data.vt_seconder)){
	
		save_lock=1;
			 
		currentSaveMenu=save_option_menu;		 
			 
		entered=0;	 
			 
	}else{current_menu=settings_menu;}	
 }
};


void staticData_CT(struct display_menu_handles menu_item){

	enum letter_codes_8pt primary[9]=  {p,r,i,m,e,r,_,_,_};
	enum letter_codes_8pt secondary[9]={s,e,k,o,n,d,e,r,_};
	enum letter_codes_8pt phase[9]={f,a,z,_,a,y,a,r,i};
	enum letter_codes_8pt direction[9]={a,k,i,m,_,y,o,n,u};
	
	uint8_t i;
	
	uint8_t column=1;
	
	uint8_t page=0;
	
	for(i=0;i<21;i++){
		
	column=letter_transfer_8pt(menu_item.title[i],page,column);
	
	}
	
	line_highlighter(0,128);
	
	
	column=1;
	
	page=1;
	
	for(i=0;i<9;i++){
		
	column=letter_transfer_8pt(primary[i],page,column);
	
	}
	
	
	column=1;
	page=2;
	for(i=0;i<9;i++){
		
	column=letter_transfer_8pt(secondary[i],page,column);
		
	}
	
	
	column=1;
	page=4;
	for(i=0;i<9;i++){
		
	column=letter_transfer_8pt(phase[i],page,column);
		
	}
	
	
	column=1;
	page=5;
	
	for(i=0;i<9;i++){
		
	column=letter_transfer_8pt(direction[i],page,column);
		
	}
	
	
	symbol_transfer(menu_item.symbol[0],7,1);
	symbol_transfer(menu_item.symbol[1],7,28);
	symbol_transfer(menu_item.symbol[2],7,59);
	symbol_transfer(menu_item.symbol[3],7,88);
	symbol_transfer(menu_item.symbol[4],7,119);


}


void dynamicData_CT(struct display_menu_handles menu_item){
	
	
	static enum digit_codes_14pt ct_digit_p[5]={0};
	static enum digit_codes_14pt ct_digit_s[5]={0};
	static enum digit_codes_14pt ct_digit_phase[2]={0};

	
	static uint8_t ord=0;//order of  digits 0...5
	static uint8_t sel=-1;//primary/secondary selection
	static uint8_t entered=0;
	
	static uint8_t current_dir=0;
	static uint8_t phase_dir=0;
	
	uint8_t i;
	uint8_t column,page;
	
	clearColumns(1,79,128);
	clearColumns(2,79,128);
		
	clearColumns(4,79,128);
	clearColumns(5,79,128);
	
	page=1;
	column=90;
		
	for(i=0;i<5;i++){ //primary digit tranfer
	
	digit_transfer_8pt(ct_digit_p[i],page,column);
	column+=8;	

	}
		
	page=2;
	column=90;
		
		
	for(i=0;i<5;i++){ //secondary digit tranfer
	
	digit_transfer_8pt(ct_digit_s[i],page,column);
	column+=8;	

	}
	
	page=4;
	column=98;
		
	//phase digit tranfer
	
	if(phase_dir){
	
	put_minus(page,90);
		
	}else{
		
	put_plus(page,90);
	
	}

	
	digit_transfer_8pt(ct_digit_phase[0],page,column);
	
	put_dot(page,column+6);
	
	digit_transfer_8pt(ct_digit_phase[1],page,column+8);
	
	
	//dir
	
	
	page=5;
	column=100;
	
	
	if(current_dir){
	
	  symbol_transfer(menu_from,page,column);
		
	}else{
		
		symbol_transfer(menu_into,page,column);
	
	}
	
	
	
	
	
	
	if(!entered && save_lock==0){
		
	
		
		ct_digit_p[4]=flashData2LCD(flash.data.ct_primer,1);
		ct_digit_p[3]=flashData2LCD(flash.data.ct_primer,2);
		ct_digit_p[2]=flashData2LCD(flash.data.ct_primer,3);
		ct_digit_p[1]=flashData2LCD(flash.data.ct_primer,4);
		ct_digit_p[0]=flashData2LCD(flash.data.ct_primer,5);
		

		ct_digit_s[4]=flashData2LCD(flash.data.ct_seconder,1);
		ct_digit_s[3]=flashData2LCD(flash.data.ct_seconder,2);
		ct_digit_s[2]=flashData2LCD(flash.data.ct_seconder,3);
		ct_digit_s[1]=flashData2LCD(flash.data.ct_seconder,4);
		ct_digit_s[0]=flashData2LCD(flash.data.ct_seconder,5);
		
		
		ct_digit_phase[1]=flashData2LCD(flash.data.ct_phase_shift,1);
		ct_digit_phase[0]=flashData2LCD(flash.data.ct_phase_shift,2);
		
		
		current_dir=flash.data.configBit.current_direction;
		phase_dir=flash.data.configBit.phase_comp_direction;
		

	}
	
	
	if(pressed_button==enter_pressed){sel++;ord=0;entered=1;}
	
	
	if(sel==0 && entered==1){//primer side start
		
	if(pressed_button==left_pressed){  // left is plus @VT
	
	
	if(++ct_digit_p[ord]>_9){ct_digit_p[ord]=_0;}	
		
	}
	
	if(pressed_button==right_pressed){ // left is plus @VT
	
	
	if(--ct_digit_p[ord]==_m1){ct_digit_p[ord]=_9;}	
		
	}
	
	
	if(pressed_button==down_pressed){  // down is right pos change
	
	ord++;
	if(ord>_4){ord=0;}	
		
	}
	
	
	put_cursor(1,89+ord*8,7);
	
	
	}//primer side end
	
	
	
	if(sel==1 && entered==1){//seconder side start
		
		
		
		
	if(pressed_button==left_pressed){  // left is plus @VT
	
	
	if(++ct_digit_s[ord]>_9){ct_digit_s[ord]=_0;}	
		
	}
	
	if(pressed_button==right_pressed){ // left is plus @VT
	
	
	if(--ct_digit_s[ord]==_m1){ct_digit_s[ord]=_9;}	
		
	}
	
	
	if(pressed_button==down_pressed){  // down is right pos change
	
	ord++;
	if(ord>_4){ord=0;}	
		
	}
	
	put_cursor(2,89+ord*8,7);	
		
	}//seconder side end
	
	
	if(sel==2 && entered==1){//phase started
		

	if(ord==0){
	
	
	if(pressed_button==left_pressed || pressed_button==right_pressed){  // left is plus @VT
	
		phase_dir^=1;
		
	}
	
	
	}else{
		
	if(pressed_button==left_pressed){  // left is plus @VT
	
	
	if(++ct_digit_phase[ord-1]>_9){ct_digit_phase[ord-1]=_0;}	
	
	if(ct_digit_phase[0]>1){ct_digit_phase[0]=1;};
		
	}
	
	if(pressed_button==right_pressed){ // left is plus @VT
	
	
	if(--ct_digit_phase[ord-1]==_m1){ct_digit_phase[ord-1]=_9;}	
	
	if(ct_digit_phase[0]>1){ct_digit_phase[0]=1;};
		
	 }
	
	
	}
	
	
	if(pressed_button==down_pressed){  // down is right pos change
	
	ord++;
	if(ord>_2){ord=0;}	
		
	}
	
	put_cursor(4,89+ord*8,7);	
	
	
	}
	
	

	
	if(sel==3 && entered==1){//dir start
		
	if(pressed_button==left_pressed || pressed_button==right_pressed){  // left is plus @VT
	
		current_dir^=1;
		
	}
	
	

	
	put_cursor(5,100,8);
		
		
		
	}
	
	
	if(sel==4){sel=0;}
	
	
	 flashNew.data.ct_primer=screenData2flash(ct_digit_p,5);
	 flashNew.data.ct_seconder=screenData2flash(ct_digit_s,5);
	 flashNew.data.ct_phase_shift=screenData2flash(ct_digit_phase,2);//cau
	 flashNew.data.configBit.phase_comp_direction=phase_dir;//cau
	 flashNew.data.configBit.current_direction=current_dir;//cau

		

	if(pressed_button==up_pressed && save_lock==0){ 
	
	
		

	if((flashNew.data.ct_primer											!=flash.data.ct_primer	) 										|| 
		 (flashNew.data.ct_seconder										!=flash.data.ct_seconder) 										||
		 (flashNew.data.ct_phase_shift								!=flash.data.ct_phase_shift) 									||
		 (flashNew.data.configBit.phase_comp_direction!=flash.data.configBit.phase_comp_direction) 	||
	   (flashNew.data.configBit.current_direction		!=flash.data.configBit.current_direction)
	){
	
		save_lock=1;
			 
		currentSaveMenu=save_option_menu;		 
			 
		entered=0;	 //cau
			 
	}else{current_menu=settings_menu;}			
 }
};


void staticData_input(struct display_menu_handles menu_item){

	enum letter_codes_8pt energy_reset[12]=  {e,n,e,r,j,i,_,r,e,s,e,t};
	enum letter_codes_8pt record_start[12]=  {k,a,y,i,t,_,b,a,s,l,a,t};
	
	uint8_t i;
	uint8_t column=1;
	uint8_t page=0;
	


	for(i=0;i<21;i++){
		
	column=letter_transfer_8pt(menu_item.title[i],page,column);
	
		
	}
	
	line_highlighter(0,128);
	
	column=0;
	page=2;
	
	for(i=0;i<12;i++){
		
	column=letter_transfer_8pt(energy_reset[i],page,column);
	
	}
	
	
	column=0;
	page=4;
	
	for(i=0;i<12;i++){
		
	column=letter_transfer_8pt(record_start[i],page,column);
		
	}
	
	
	symbol_transfer(menu_item.symbol[0],7,1);
	symbol_transfer(menu_item.symbol[1],7,28);
	symbol_transfer(menu_item.symbol[2],7,59);
	symbol_transfer(menu_item.symbol[3],7,88);
	symbol_transfer(menu_item.symbol[4],7,119);
	
	
	
};


void dynamicData_input(struct display_menu_handles menu_item){
	

	struct option_bits{
	
		uint8_t input_energy_reset_EN:1;
		uint8_t input_energy_reset_edge:1;
		uint8_t input_record_start_EN:1;
		uint8_t input_record_start_edge:1;
		uint8_t cursor_pos:2;
		
		uint8_t rem:2;
			
	};
	
	static struct option_bits obit={0};
	
	
	static uint8_t sel=-1;//primary/secondary selection
	static uint8_t entered=0;
	static uint8_t col=0;
	
	uint8_t i;
	uint8_t column,page;
	

	clearColumns(2,79,128);
	clearColumns(4,79,128);

	
	page=2;
	column=90;
	
	
	if(obit.input_energy_reset_EN){
		
	symbol_transfer(menu_tick,page,column);
	
	}else{
	
	symbol_transfer(menu_cross,page,column);
	
	}
	
	
	column=110;
	
	if(obit.input_energy_reset_edge){
		
	symbol_transfer(menu_risingEdge,page,column);
	
	}else{
	
	symbol_transfer(menu_fallingEdge,page,column);
	
	}
	
	
	
	
	page=4;
	column=90;
	
	
	if(obit.input_record_start_EN){
		
	symbol_transfer(menu_tick,page,column);
	
	}else{
	
	symbol_transfer(menu_cross,page,column);
	
	}
	
	
	column=110;
	
	if(obit.input_record_start_edge){
		
	symbol_transfer(menu_risingEdge,page,column);
	
	}else{
	
	symbol_transfer(menu_fallingEdge,page,column);
	
	}
	
	
	
	
	
	
	if(!entered && save_lock==0){
	
		obit.input_energy_reset_EN=flash.data.configBit.input_energy_reset_EN;
		obit.input_energy_reset_edge=flash.data.configBit.input_energy_reset_edge;
		obit.input_record_start_EN=flash.data.configBit.input_record_start_EN;
		obit.input_record_start_edge=flash.data.configBit.input_record_start_edge;
		
	}
	
	
	if(pressed_button==enter_pressed){sel++; entered=1;col=0;}
	
	
	if(sel==0 && entered==1){//primer side start
		
		
	if(pressed_button==left_pressed && col==0 ){
	
		obit.input_energy_reset_EN^=1;
	
	}


	if(pressed_button==left_pressed && col==1 ){
	
		obit.input_energy_reset_edge^=1;
	
	}		
		
		
	if(pressed_button==right_pressed ){
	
		col^=1;
	
	}	
		
	put_cursor(2,90+col*20,8);
	
	
	}//primer side end
	
	
	
	if(sel==1 && entered==1){//seconder side start
		
		
	if(pressed_button==left_pressed && col==0 ){
	
		obit.input_record_start_EN^=1;
	
	}


	if(pressed_button==left_pressed && col==1 ){
	
		obit.input_record_start_edge^=1;
	
	}		
		
		
	if(pressed_button==right_pressed ){
	
		col^=1;
	
	}		
		

	
  put_cursor(4,90+col*20,8);
	
	
	}
	
	

	

	
	
	
	if(sel==2){sel=0;}
	
	


		

	if(pressed_button==up_pressed && save_lock==0){ 
	
	 flashNew.data.configBit.input_energy_reset_EN	=obit.input_energy_reset_EN;
	 flashNew.data.configBit.input_energy_reset_edge=obit.input_energy_reset_edge;
	 flashNew.data.configBit.input_record_start_EN	=obit.input_record_start_EN;
	 flashNew.data.configBit.input_record_start_edge=obit.input_record_start_edge;

		

		

	if(	(flashNew.data.configBit.input_energy_reset_EN		!=flash.data.configBit.input_energy_reset_EN) 	||
			(flashNew.data.configBit.input_energy_reset_edge	!=flash.data.configBit.input_energy_reset_edge) ||
			(flashNew.data.configBit.input_record_start_EN		!=flash.data.configBit.input_record_start_EN)		||
			(flashNew.data.configBit.input_record_start_edge	!=flash.data.configBit.input_record_start_edge)){//cau
	
		save_lock=1;
			 
		currentSaveMenu=save_option_menu;		 
			 
		entered=0;	 
			 
	}else{current_menu=settings_menu;}			
 }
	
}





