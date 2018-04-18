
#include "stm32f3xx_hal.h"
#include "main.h"
#include "menu_definitions.h"

union push_buttons pb;
enum  input pressed_button;

void pushButtonHandlings(){
	
		// may be on-delayed
	
		pb.button.enter	=HAL_GPIO_ReadPin(BTN1_GPIO_Port,BTN1_Pin);
		pb.button.left 	=HAL_GPIO_ReadPin(BTN2_GPIO_Port,BTN2_Pin);
		pb.button.right =HAL_GPIO_ReadPin(BTN3_GPIO_Port,BTN3_Pin);
		pb.button.down	=HAL_GPIO_ReadPin(BTN4_GPIO_Port,BTN4_Pin);
		pb.button.up 		=HAL_GPIO_ReadPin(BTN5_GPIO_Port,BTN5_Pin);
		
		pressed_button=(enum input)(pb.all);

}


