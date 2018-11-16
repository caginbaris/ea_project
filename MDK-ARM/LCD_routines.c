#include "stm32f3xx_hal.h"
#include "spi.h"
#include "tim.h"
#include "LCD_definitions.h"
#include "menu_definitions.h"
#include "aux_functions.h"


uint16_t side_leds=160;
uint16_t center_leds=160;

extern uint8_t save_lock;
extern uint8_t currentSaveMenu;

void init_LCD(){
	

	LCD_nRESET; 							//  set reset pin to high
	//LCD_CS; 								//	set CS pin to low-cau hardware implemented
	LCD_control_data_enable;	//	set A0 pin to low to sent control data
	
	while(HAL_SPI_GetState(&hspi3)!=HAL_SPI_STATE_READY);
	
	HAL_SPI_Transmit(&hspi3,(uint8_t*) &LCD_batch_init_array,14,100);
	
	//LCD_CD ;


}

void init_backlight(){
	
	
	
	HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_3);
	
	HAL_TIM_Base_Start(&htim5);
	
	__HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_2,800);
	__HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_3,3599);


}



void page_change(uint8_t *page){
	
	
	LCD_control_data_enable;
	HAL_SPI_Transmit(&hspi3,page,1,100);
	LCD_display_data_enable;
	
	
}


void column_change(uint8_t *column){
	

	LCD_control_data_enable;
	HAL_SPI_Transmit(&hspi3,column,2,100);
	LCD_display_data_enable;
	
	
}


void write_lcd(){
	
	uint8_t page=0xB0;
	uint8_t column[]={0x10,0x00};
	uint8_t i=0;
	
	
	for(page=0xB0;page<0xB8;page++){
 
	page_change(&page);
	column_change(column);
	HAL_SPI_Transmit(&hspi3,&display_buffer[i++][0],128,100);
	
	}
	

}


uint8_t letter_transfer_14pt(enum letter_codes_14pt x, uint8_t page, uint8_t column){
	
	uint16_t i;
	uint8_t page_plus;
	uint8_t letter_width;
	uint16_t letter_offset;
	
	letter_width=Descriptors[x][0];
	letter_offset=Descriptors[x][1];
	
	page_plus=page+1;
	
	for(i=0;i<letter_width;i++){
		
		display_buffer[page][column+i]			=arial_14ptBitmaps[i+letter_offset];
		display_buffer[page_plus][column+i]	=arial_14ptBitmaps[i+letter_offset +letter_width];
	}

	return (column+i+1);
}


uint8_t letter_transfer_8pt(enum letter_codes_8pt x, uint8_t page, uint8_t column){
	
	uint16_t i;
	uint8_t letter_width;
	uint16_t letter_offset;
	
	letter_width=Descriptors2[x][0];
	letter_offset=Descriptors2[x][1];
	
	
	
	for(i=0;i<letter_width;i++){
		
		display_buffer[page][column+i]			=arial_8ptBitmaps[i+letter_offset];

	}
	
	
	return (column+i+1);


}

uint8_t digit_transfer_8pt(enum digit_codes_14pt x, uint8_t page, uint8_t column){
	
	uint16_t i;
	uint8_t letter_width;
	uint16_t letter_offset;
	
	letter_width=Descriptors_lowerCaseDigits[x][0];
	letter_offset=Descriptors_lowerCaseDigits[x][1];
	
	
	
	for(i=0;i<letter_width;i++){
		
		display_buffer[page][column+i]			=arial_8ptBitmaps_lowerCaseDigits[i+letter_offset];

	}
	
	
	return (column+i+1);


}



void digit_transfer_14pt(enum digit_codes_14pt x, uint8_t page, uint8_t column){
	
	uint16_t i;
	uint8_t page_plus;
	uint8_t letter_width;
	uint16_t letter_offset;
	
	letter_width=Descriptors3[x][0];
	letter_offset=Descriptors3[x][1];
	
	page_plus=page+1;
	
	for(i=0;i<letter_width;i++){
		
		display_buffer[page][column+i]			=bookAntiqua_14ptBitmaps[i+letter_offset];
		display_buffer[page_plus][column+i]	=bookAntiqua_14ptBitmaps[i+letter_offset +letter_width];
	}


}



void unit_transfer(enum units x, uint8_t page, uint8_t column){
	
	uint16_t i;
	uint8_t page_plus;
	uint8_t letter_width;
	uint16_t letter_offset;
	
	letter_width=Descriptors4[x][0];
	letter_offset=Descriptors4[x][1];
	
	page_plus=page+1;
	
	for(i=0;i<letter_width;i++){
		
		display_buffer[page][column+i]			=unit_charecters[i+letter_offset];
		display_buffer[page_plus][column+i]	=unit_charecters[i+letter_offset +letter_width];
	}


}


void menu_unit_transfer(enum menu_units x, uint8_t page, uint8_t column){
	
	uint16_t i;
	uint8_t page_plus;
	uint8_t letter_width;
	uint16_t letter_offset;
	
	letter_width=Descriptors5[x][0];
	letter_offset=Descriptors5[x][1];
	
	page_plus=page+1;
	
	for(i=0;i<letter_width;i++){
		
		display_buffer[page][column+i]			=menu_units_ch[i+letter_offset];
		display_buffer[page_plus][column+i]	=menu_units_ch[i+letter_offset +letter_width];
	}


}




void symbol_transfer(enum menu_symbols x, uint8_t page,uint8_t column){

	uint16_t i;

	for(i=0;i<8;i++){
	
		display_buffer[page][column+i]=button_symbols[x][i];
	
	}


}


void put_dot2x2(uint8_t page,uint8_t column){

	display_buffer[page][column]=0x0C;
	display_buffer[page][column+1]=0x0C;

}


void put_minus(uint8_t page,uint8_t column){

	display_buffer[page][column]=0xC0;
	display_buffer[page][column+1]=0xC0;
	display_buffer[page][column+2]=0xC0;
	display_buffer[page][column+3]=0xC0;
	display_buffer[page][column+4]=0xC0;

}





void line_highlighter(uint8_t page, uint8_t column){
	
	uint8_t i;
	
	
	for(i=0;i<column;i++){
	
	display_buffer[page][i]^=0xff;
		
	}

}


void put_cursor(uint8_t page,uint8_t column,uint8_t width){

	uint8_t i;
	
	for(i=0;i<width;i++){
	display_buffer[page][column+i]^=0xFF;
	}

}


void clearColumns(uint8_t page,uint8_t columnStart,uint8_t columnEnd){

	uint8_t i;
	
	for(i=columnStart;i<columnEnd;i++){
	display_buffer[page][i]=0x00;
	}

}


void loading_bar(uint8_t page,uint8_t columnStart,uint8_t columnEnd){


	static uint32_t loadBarCounter=7;
	
	uint8_t i;
	

	for(i=columnStart;i<loadBarCounter;i++){
		
		display_buffer[page][i]=0xff;
		display_buffer[page][i+1]=0xff;
		display_buffer[page][i+2]=0xff;
		display_buffer[page][i+3]=0xff;
		display_buffer[page][i+4]=0xff;
		

	}
	
	loadBarCounter+=5;
		
	if(loadBarCounter>columnEnd){loadBarCounter=columnStart;}



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
	if(save_lock==0){current_menu=settings_menu;}
	
	if(pressed_button==up_pressed && pbcheck==0){currentSaveMenu=1;pbcheck=1;}
	if(pressed_button==down_pressed && pbcheck==0){currentSaveMenu=2;pbcheck=1;}

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
	
	//cau flash operation needed
	
	loading_bar(6,7,120); //cau bar counter should be external
	save_lock=off_delay(0,save_lock,20,&timeOut);
	if(save_lock==0){current_menu=settings_menu;currentSaveMenu=0;}
	
	
	
	
	
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
	
	
	//saving
	
	for(i=0;i<12;i++){
		
	column=letter_transfer_8pt(notSaved[i],2,column);
	
	}
	
	
	save_lock=off_delay(0,save_lock,20,&timeOut);
	if(save_lock==0){current_menu=settings_menu;currentSaveMenu=0;}
	
	
}













uint32_t flashData2LCD(float x,uint32_t n){

	uint32_t y;

	float factor=1.0f;

	while(--n>0){factor*=0.1f;}

	y=((uint32_t)(x*factor))%10;

	return y;
}

uint32_t screenData2flash(uint32_t* data){

	uint32_t combinedNumber;

	combinedNumber= *(data++)*100000+
									*(data++)*10000+
									*(data++)*1000+
									*(data++)*100+
									*(data++)*10+
									*(data++);

	return combinedNumber;

}

















