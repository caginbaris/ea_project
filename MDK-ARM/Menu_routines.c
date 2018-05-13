#include "menu_definitions.h"
#include "lcd_definitions.h"
#include "ch_format.h"
#include "measurement_definitions.h"
#include  <string.h>








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
	//third row
	if(lcd_row3.int100!=0											){	digit_transfer_14pt(lcd_row3.int100,page,column);}
	if(lcd_row3.int10!=0 || lcd_row2.int10!=0	){ 	digit_transfer_14pt(lcd_row3.int10,page,column+digit_width_14pt);}
																								digit_transfer_14pt(lcd_row3.int1,page,column+2*digit_width_14pt);
																								put_dot2x2(page+1,column+3*digit_width_14pt);
																								digit_transfer_14pt(lcd_row3.fraction,page,column+(3*digit_width_14pt+5)); //cau 5 for dot space
	
	
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

	for(i=0;i<17;i++){
		
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
	


void toMainDetect(){
	

	
	switch(previous_menu){
		
	
		
		case Vpn_true:									main_menu_entry=Vpn_main; break;
		case Vpn_fund:									main_menu_entry=Vpn_main; break;
		
		case Vpp_true:									main_menu_entry=Vpp_main; break;
		case Vpp_fund:									main_menu_entry=Vpp_main; break;
		
		case Ip_true:										main_menu_entry=Ip_main; break;
		case Ip_fund:										main_menu_entry=Ip_main; break;
		
		case Active_Power		:						main_menu_entry=	Active_Power_main; break;
		case Reactive_Power	:						main_menu_entry=Reactive_Power_main; break;
		case Apparent_Power	:						main_menu_entry=Apparent_Power_main; break;
		case Total_Power		:						main_menu_entry=Total_Power_main; break;
		
		case Power_Factors_true:				main_menu_entry=	Power_Factors_main; break;
		case Total_Power_Factor_true:		main_menu_entry=Total_Power_Factor_main; break;
		
		case Power_Factors_fund:				main_menu_entry=	Power_Factors_main; break;
		case Total_Power_Factor_fund:		main_menu_entry=Total_Power_Factor_main; break;
		
		default:main_menu_entry=Vpn_main;break;
		
	}
	

	
	current_menu=main_menu ;
	pressed_button=invalid;

}

void atMainOperation(){
	
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
		case Power_Factors_main:						current_menu=Power_Factors_true; 				break;
		case Total_Power_Factor_main:				current_menu=Total_Power_Factor_true; 	break;
		
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

	struct display_menu_handles local_menu={0};
	
	memset(display_buffer,0,1024); // DMA can be used
	
	local_menu=MENU.all[current_menu];

	if(previous_menu!=current_menu){
	
	MENU.all[current_menu].staticDataTransfer(local_menu);
	
	}
	
	MENU.all[current_menu].dynamicDataTransfer(local_menu);
	
};



