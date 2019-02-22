
#include "stm32f3xx_hal.h"
#include "main.h"
#include "menu_definitions.h"
#include "aux_functions.h"


#define qual_sample 100

union push_buttons pb={0};
enum  input pressed_button=invalid;

enum input pushButtonHandling(){
	
		enum  input button=invalid;
		static uint32_t counter_pb[5]={0};

	
		
		pb.button.enter	=on_delay(HAL_GPIO_ReadPin(BTN1_GPIO_Port,BTN1_Pin),pb.button.enter,	(uint16_t)qual_sample,&counter_pb[0]);
		pb.button.left 	=on_delay(HAL_GPIO_ReadPin(BTN2_GPIO_Port,BTN2_Pin),pb.button.left,		(uint16_t)qual_sample,&counter_pb[1]);
		pb.button.right =on_delay(HAL_GPIO_ReadPin(BTN3_GPIO_Port,BTN3_Pin),pb.button.right,	(uint16_t)qual_sample,&counter_pb[2]);
		pb.button.down	=on_delay(HAL_GPIO_ReadPin(BTN4_GPIO_Port,BTN4_Pin),pb.button.down,		(uint16_t)qual_sample,&counter_pb[3]);
		pb.button.up 		=on_delay(HAL_GPIO_ReadPin(BTN5_GPIO_Port,BTN5_Pin),pb.button.up,			(uint16_t)qual_sample,&counter_pb[4]);
		
		
		if(pb.all!=0){
			
			
		switch(pb.all){
		
			case 1	:button	=enter_pressed;	break; 
			case 2	:button	=left_pressed;	break; 
			case 4	:button	=right_pressed;	break; 
			case 8	:button	=down_pressed;	break; 
			case 16	:button	=up_pressed;		break; 
			default :button	=invalid;				break;
		}	
			

		
		pb.all=0;
		
		}

		
		// switch(pl)
		
		return button;

}





