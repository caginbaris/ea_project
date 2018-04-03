#ifndef __lcd_definitions_H
#define __lcd_definitions_H

#include <stdint.h>

#define LCD_CS HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_RESET)
#define LCD_CD HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_SET)

#define LCD_RESET HAL_GPIO_WritePin(GPIOC,GPIO_PIN_11,GPIO_PIN_RESET)
#define LCD_nRESET HAL_GPIO_WritePin(GPIOC,GPIO_PIN_11,GPIO_PIN_SET) 

#define LCD_control_data_enable HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_RESET)
#define LCD_display_data_enable HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_SET)

extern const uint8_t LCD_batch_init_array[14];
extern uint8_t display_buffer[8][128];


extern const uint8_t arial_14ptBitmaps[]; 
extern const uint8_t Descriptors[][2];

enum letter_codes{

	A,
	B, 
	C

};


extern enum letter_codes letter;



#endif
