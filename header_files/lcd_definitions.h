#ifndef __lcd_definitions_H
#define __lcd_definitions_H

#include <stdint.h>

#define upperCaseLargeLetterWidth 12

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

extern const uint8_t arial_8ptBitmaps[]; 
extern const uint8_t Descriptors2[][2];

enum letter_codes{

	A,
	B, 
	C

};

enum letter_codes2{

	a,
	b, 
	c

};



extern enum letter_codes letter;
extern enum letter_codes letter2;

void letter_transfer(enum letter_codes x, uint8_t page, uint8_t column);
void letter_transfer2(enum letter_codes2 x, uint8_t page, uint8_t column);

void font_transfer();
void font_transfer2();

#endif
