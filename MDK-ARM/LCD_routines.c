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
	
	
	for(page=0xB0;page<0xB8;page++){
 
	page_change(&page);
	column_change(column);
	HAL_SPI_Transmit(&hspi3,&display_buffer[0][0],128,100);
	
	}
	

}




