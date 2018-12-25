#ifndef __lcd_definitions_H
#define __lcd_definitions_H

#include <stdint.h>

#define upperCaseLargeLetterWidth 12
#define digit_width_14pt 14
#define lowerCaseSmallLetterWidth 7;


#define LCD_CS HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_RESET)
#define LCD_CD HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_SET)

#define LCD_RESET HAL_GPIO_WritePin(GPIOC,GPIO_PIN_11,GPIO_PIN_RESET)
#define LCD_nRESET HAL_GPIO_WritePin(GPIOC,GPIO_PIN_11,GPIO_PIN_SET) 

#define LCD_control_data_enable HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_RESET)
#define LCD_display_data_enable HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_SET)



extern const uint8_t LCD_batch_init_array[14];
extern uint8_t display_buffer[8][128];


extern const uint8_t arial_14ptBitmaps[]; 
extern const uint16_t Descriptors[][2];

extern const uint8_t arial_8ptBitmaps[]; 
extern const uint16_t Descriptors2[][2];

extern const uint8_t bookAntiqua_14ptBitmaps[];
extern const uint16_t Descriptors3[][2];

extern const uint8_t unit_charecters[];
extern const uint16_t Descriptors4[][2];

extern const uint8_t menu_units_ch[];
extern const uint16_t Descriptors5[][2];

extern const uint8_t arial_8ptBitmaps_lowerCaseDigits[];
extern const uint16_t Descriptors_lowerCaseDigits[][2];

extern const uint8_t button_symbols[][8];

enum letter_codes_14pt{
A,
B,
C,
D,
E,
F,
G,
H,
I,
J,
K,
L,
M,
N,
O,
P,
Q,
R,
S,
T,
U,
V,
W,
X,
Y,
Z,
__,
}; //enum for uppercase letters

enum letter_codes_8pt{
a,
b,
c,
d,
e,
f,
g,
h,
i,
j,
k,
l,
m,
n,
o,
p,
q,
r,
s,
t,
u,
v,
w,
x,
y,
z,
_,

}; //enum for lowercase letters


enum digit_codes_14pt{
	
	_m1=-1,
	_0=0,
	_1,
	_2,
	_3,
	_4,
	_5,
	_6,
	_7,
	_8,
	_9,


};

enum units {

u_G,		
u_K,
u_M,
u_N


};


enum menu_units{
	
	m_percent,
	m_A,
	m_R,
	m_V,
	m_W,
	m_h,
	m_


};


enum menu_symbols {

menu_blank,
menu_enter,
menu_escape,		
menu_left,
menu_right,
menu_down,
menu_up,
menu_plus,
menu_minus,
menu_slash,
menu_qmark,
menu_tick,
menu_cross,
menu_into,
menu_from		
};


struct digit_format{

	uint16_t int1:4;
	uint16_t int10:4;
	uint16_t int100:4;
	
	uint16_t fraction:4;
	
	uint8_t sign;
	
	enum units range;
	
};



extern enum units unit;
extern enum letter_codes_14pt letter;
extern enum letter_codes_14pt letter2;

uint8_t letter_transfer_14pt(enum letter_codes_14pt x, uint8_t page, uint8_t column);
uint8_t letter_transfer_8pt(enum letter_codes_8pt x, uint8_t page, uint8_t column);
void put_dot2x2(uint8_t page,uint8_t column);
void put_dot(uint8_t page,uint8_t column);

void put_plus(uint8_t page,uint8_t column);
void put_minus(uint8_t page,uint8_t column);

void line_highlighter(uint8_t page, uint8_t column);
void put_cursor(uint8_t page,uint8_t column,uint8_t width);
void clearColumns(uint8_t page,uint8_t columnStart,uint8_t columnEnd);


void noSave(void);
void saveScreen(void);
void savingScreen(void);
void notSavedScreen(void);



uint32_t flashData2LCD(uint32_t x,uint32_t n);
uint32_t screenData2flash(enum digit_codes_14pt* data,uint8_t N);

#endif
