#include "stm32f3xx_hal.h"
#include "spi.h"
#include "tim.h"
#include "LCD_definitions.h"





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
	
	__HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_2,16000);
	__HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_3,16000);


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


void letter_transfer_14pt(enum letter_codes_14pt x, uint8_t page, uint8_t column){
	
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


}


void letter_transfer_8pt(enum letter_codes_8pt x, uint8_t page, uint8_t column){
	
	uint16_t i;
	uint8_t letter_width;
	uint16_t letter_offset;
	
	letter_width=Descriptors2[x][0];
	letter_offset=Descriptors2[x][1];
	
	
	
	for(i=0;i<letter_width;i++){
		
		display_buffer[page][column+i]			=arial_8ptBitmaps[i+letter_offset];

	}


}


void line_highlighter(uint8_t page, uint8_t column){
	
	uint8_t i;
	
	
	for(i=0;i<column;i++){
	
	display_buffer[page][i]^=0xff;
		
	}

}


void font_transfer(){
	
	uint16_t i;
	uint16_t page=1;
	uint16_t column=0;
	
	letter_transfer_14pt(C,page,0);
	letter_transfer_14pt(B,page,13);
	letter_transfer_14pt(A,page,26);
	
	letter_transfer_14pt(C,page+2,26);
	letter_transfer_14pt(C,page+2,0);
	

}


void font_transfer2(){
	
	uint16_t i;
	uint16_t page=0;
	uint16_t column=0;
	
	letter_transfer_8pt(a,0,2);
	letter_transfer_8pt(b,0,8);
	letter_transfer_8pt(c,0,14);
	
	letter_transfer_8pt(c,1,0);
	letter_transfer_8pt(b,1,6);
	letter_transfer_8pt(a,1,12);
	line_highlighter(0, 127);

}




