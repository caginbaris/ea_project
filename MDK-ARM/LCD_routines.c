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


void put_dot(uint8_t page,uint8_t column){

	display_buffer[page][column]|=0x80;

}


void put_minus(uint8_t page,uint8_t column){

	display_buffer[page][column]=0x10;
	display_buffer[page][column+1]=0x10;
	display_buffer[page][column+2]=0x10;
	display_buffer[page][column+3]=0x10;
	display_buffer[page][column+4]=0x10;

}

void put_plus(uint8_t page,uint8_t column){

	display_buffer[page][column]=0x10;
	display_buffer[page][column+1]=0x10;
	display_buffer[page][column+2]=0x7c;
	display_buffer[page][column+3]=0x10;
	display_buffer[page][column+4]=0x10;

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







uint32_t flashData2LCD(uint32_t x,uint32_t n){

	uint32_t y;

	float factor=1.0f;

	while(--n>0){factor*=0.1f;}

	y=((uint32_t)(x*factor))%10;

	return y;
}


uint32_t screenData2flash(enum digit_codes_14pt* data){

	uint32_t combinedNumber;

	combinedNumber= data[0]*100000+
									data[1]*10000+
									data[2]*1000+
									data[3]*100+
									data[4]*10+
									data[5];

   

	return (combinedNumber);

}

















