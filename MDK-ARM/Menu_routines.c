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
	if(x>=_e9 && x<_e9){formatted_digit.range=u_G;x=x*_em9;}

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
	lcd_row2=formatDynamicData(*fp++);
	lcd_row3=formatDynamicData(*fp++);
	
	//digit-transfer
	
	page=1;
	column=64;
	
	if(lcd_row1.int100!=0											){	digit_transfer_14pt(lcd_row1.int100,page,column);}
	if(lcd_row1.int10!=0 || lcd_row1.int10!=0	){ 	digit_transfer_14pt(lcd_row1.int10,page,column+digit_width_14pt);}
																								digit_transfer_14pt(lcd_row1.int1,page,column+2*digit_width_14pt);
																								//symbol transfer for fraction dot (may be excluded from dynamic part)
																								digit_transfer_14pt(lcd_row1.fraction,page,column+(3*digit_width_14pt+5)); //cau 5 for dot space
	
	
									

};



void staticDataTripple(struct display_menu_handles menu_item){
	
	int i;
	int column=0;
	int page=0;

	for(i=0;i<20;i++){
		
	letter_transfer_8pt(menu_item.title[i],page,a);
	column=column+lowerCaseSmallLetterWidth;	
		
	}
	
	column=0;
	
	page=1;
	
	letter_transfer_14pt(menu_item.first_line[0],page,column);
	letter_transfer_14pt(menu_item.first_line[1],page,column+  upperCaseLargeLetterWidth);
	letter_transfer_14pt(menu_item.first_line[2],page,column+2*upperCaseLargeLetterWidth);
	
	
	page=3;
	
	letter_transfer_14pt(menu_item.second_line[0],page,column);
	letter_transfer_14pt(menu_item.second_line[1],page,column+  upperCaseLargeLetterWidth);
	letter_transfer_14pt(menu_item.second_line[2],page,column+2*upperCaseLargeLetterWidth);
	
	
	page=5;
	
	letter_transfer_14pt(menu_item.third_line[0],page,column);
	letter_transfer_14pt(menu_item.third_line[1],page,column+  upperCaseLargeLetterWidth);
	letter_transfer_14pt(menu_item.third_line[2],page,column+2*upperCaseLargeLetterWidth);
	

	// symbols should be generated
	
}
	





void SELECT_MENU(enum menu_list current){
	
	enum menu_list i;
	
	
		for(i=Vpn_true;i<Vpp_true;i++){
			
			
			
			
		
		
		
		}
	
	
	



}


void DISPLAY_MENU(){

	struct display_menu_handles local_menu={0};
	
	local_menu=MENU.all[current_menu];

	MENU.all[current_menu].staticDataTransfer(local_menu);
	MENU.all[current_menu].dynamicDataTransfer(local_menu);
	

};

