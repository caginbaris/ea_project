
#include "stm32f3xx_hal.h"
#include "main.h"
#include "menu_definitions.h"
#include "aux_functions.h"

#define pb_refresh_rate 1000.0f
#define qual_time 0.02f // in second
#define qual_sample pb_refresh_rate*qual_time

union push_buttons pb={0};
enum  input pressed_button;

void pushButtonHandlings(){
	
		static uint32_t counter_pb[5]={0};
	
		// may be on-delayed
	
		pb.button.enter	=on_off_delay(HAL_GPIO_ReadPin(BTN1_GPIO_Port,BTN1_Pin),pb.button.enter,	(uint16_t)qual_sample,&counter_pb[0]);
		pb.button.left 	=on_off_delay(HAL_GPIO_ReadPin(BTN2_GPIO_Port,BTN2_Pin),pb.button.left,		(uint16_t)qual_sample,&counter_pb[1]);
		pb.button.right =on_off_delay(HAL_GPIO_ReadPin(BTN3_GPIO_Port,BTN3_Pin),pb.button.right,	(uint16_t)qual_sample,&counter_pb[2]);
		pb.button.down	=on_off_delay(HAL_GPIO_ReadPin(BTN4_GPIO_Port,BTN4_Pin),pb.button.down,		(uint16_t)qual_sample,&counter_pb[3]);
		pb.button.up 		=on_off_delay(HAL_GPIO_ReadPin(BTN5_GPIO_Port,BTN5_Pin),pb.button.up,			(uint16_t)qual_sample,&counter_pb[4]);
		
		if(pb.button.enter){pb.all&=enter_pressed;}
		if(pb.button.left){pb.all&=enter_pressed;}
		
		
		// switch(pl)
		
		pressed_button=(enum input)(pb.all);

}


