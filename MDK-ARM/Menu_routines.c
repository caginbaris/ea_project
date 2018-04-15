#include "menu_definitions.h"
#include "lcd_definitions.h"
#include "ch_format.h"
#include "measurement_definitions.h"





struct digit_format  formatDynamicData(float x){
	
	struct digit_format formatted_digit;
	int32_t transferred;
	
	if(x<_e3){formatted_digit.range=u_N;}
	if(x>=_e3 && x<_e6){formatted_digit.range=u_K;x=x*_em3;}
	if(x>=_e6 && x<_e9){formatted_digit.range=u_M;x=x*_em6;}
	if(x>=_e9 && x<_e12){formatted_digit.range=u_G;x=x*_em9;}

	formatted_digit.fraction=10.0f*(x-(int16_t)x);
	formatted_digit.int100	=(x*_em2); 
	formatted_digit.int10		=((int16_t)(x*_em1) % 10);
	formatted_digit.int1		=((int16_t)x % 10);

	return formatted_digit;
	
}





	
void dynamicDataTripple(struct display_menu_handles menu_item){
	
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
	if(lcd_row1.int100!=0											){	digit_transfer_14pt(lcd_row1.int100,page,column);}
	if(lcd_row1.int10!=0 || lcd_row1.int10!=0	){ 	digit_transfer_14pt(lcd_row1.int10,page,column+digit_width_14pt);}
																								digit_transfer_14pt(lcd_row1.int1,page,column+2*digit_width_14pt);
																								put_dot2x2(page+1,column+3*digit_width_14pt);
																								digit_transfer_14pt(lcd_row1.fraction,page,column+(3*digit_width_14pt+5)); //cau 5 for dot space
	
	
	if(lcd_row1.range==u_K){unit_transfer(u_K,page,column+(3*digit_width_14pt+digit_width_14pt));}
	if(lcd_row1.range==u_M){unit_transfer(u_M,page,column+(3*digit_width_14pt+digit_width_14pt));}	
	if(lcd_row1.range==u_G){unit_transfer(u_G,page,column+(3*digit_width_14pt+digit_width_14pt));}

	page=3;
	//second row
	if(lcd_row2.int100!=0											){	digit_transfer_14pt(lcd_row2.int100,page,column);}
	if(lcd_row2.int10!=0 || lcd_row2.int10!=0	){ 	digit_transfer_14pt(lcd_row2.int10,page,column+digit_width_14pt);}
																								digit_transfer_14pt(lcd_row2.int1,page,column+2*digit_width_14pt);
																								put_dot2x2(page+1,column+3*digit_width_14pt);
																								digit_transfer_14pt(lcd_row2.fraction,page,column+(3*digit_width_14pt+5)); //cau 5 for dot space
	
	
	if(lcd_row2.range==u_K){unit_transfer(u_K,page,column+(3*digit_width_14pt+digit_width_14pt));}
	if(lcd_row2.range==u_M){unit_transfer(u_M,page,column+(3*digit_width_14pt+digit_width_14pt));}	
	if(lcd_row2.range==u_G){unit_transfer(u_G,page,column+(3*digit_width_14pt+digit_width_14pt));}		
	

	page=5;
	//second row
	if(lcd_row3.int100!=0											){	digit_transfer_14pt(lcd_row3.int100,page,column);}
	if(lcd_row3.int10!=0 || lcd_row2.int10!=0	){ 	digit_transfer_14pt(lcd_row3.int10,page,column+digit_width_14pt);}
																								digit_transfer_14pt(lcd_row3.int1,page,column+2*digit_width_14pt);
																								put_dot2x2(page+1,column+3*digit_width_14pt);
																								digit_transfer_14pt(lcd_row3.fraction,page,column+(3*digit_width_14pt+5)); //cau 5 for dot space
	
	
	if(lcd_row3.range==u_K){unit_transfer(u_K,page,column+(3*digit_width_14pt+digit_width_14pt));}
	if(lcd_row3.range==u_M){unit_transfer(u_M,page,column+(3*digit_width_14pt+digit_width_14pt));}	
	if(lcd_row3.range==u_G){unit_transfer(u_G,page,column+(3*digit_width_14pt+digit_width_14pt));}		
	
	
	
									

};



void staticDataTripple(struct display_menu_handles menu_item){
	
	uint8_t i;
	uint8_t column=1;
	uint8_t page=0;
	


	for(i=0;i<17;i++){
		
	letter_transfer_8pt(menu_item.title[i],page,column);
	column=column+lowerCaseSmallLetterWidth;	
		
	}
	
	line_highlighter(0,128);
	
	column=0;
	
	page=1;
	
	letter_transfer_14pt(menu_item.first_line[0],page,column);
	letter_transfer_14pt(menu_item.first_line[1],page,column+  upperCaseLargeLetterWidth);
	letter_transfer_14pt(menu_item.first_line[2],page,column+2*upperCaseLargeLetterWidth);
	
	menu_unit_transfer(menu_item.menu_chars[0],page, menu_unit_vertical_position);
	
	
	for(i=1;i<4;i++){
		
		
		if(menu_item.menu_chars[i]==m_){break;}
		if(menu_item.menu_chars[0]==m_W){menu_unit_transfer(menu_item.menu_chars[i],page, menu_unit_vertical_position+11);}else{
		
		menu_unit_transfer(menu_item.menu_chars[i],page, menu_unit_vertical_position+7*i);
			
		}
		
		
	}
	
	
	
	
	page=3;
	
	letter_transfer_14pt(menu_item.second_line[0],page,column);
	letter_transfer_14pt(menu_item.second_line[1],page,column+  upperCaseLargeLetterWidth);
	letter_transfer_14pt(menu_item.second_line[2],page,column+2*upperCaseLargeLetterWidth);
	
	
	page=5;
	
	letter_transfer_14pt(menu_item.third_line[0],page,column);
	letter_transfer_14pt(menu_item.third_line[1],page,column+  upperCaseLargeLetterWidth);
	letter_transfer_14pt(menu_item.third_line[2],page,column+2*upperCaseLargeLetterWidth);
	

	// symbols should be generated
	

	symbol_transfer(menu_item.symbol[0],7,1);
	symbol_transfer(menu_item.symbol[1],7,28);
	symbol_transfer(menu_item.symbol[2],7,59);
	symbol_transfer(menu_item.symbol[3],7,88);
	symbol_transfer(menu_item.symbol[4],7,119);
	
	
	//menu units
	
	
	
	
	
}
	





enum menu_list SELECT_MENU(enum menu_list current,enum input button){
	
	uint8_t i;
	enum menu_list new_menu;
	
	
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

	struct display_menu_handles local_menu={0};
	
	current_menu=Vpn_true;
	
	local_menu=MENU.all[current_menu];

	MENU.all[current_menu].staticDataTransfer(local_menu);
	MENU.all[current_menu].dynamicDataTransfer(local_menu);
	

};

