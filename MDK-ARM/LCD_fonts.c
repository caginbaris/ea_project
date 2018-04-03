
#include <stdint.h>
#include "LCD_definitions.h"

/* 
**  Font data for Arial 14pt
*/

/* Character bitmaps for Arial 14pt */
const uint8_t arial_14ptBitmaps[] = 
{
	/* @0 'A' (13 pixels wide) */
	//     #####    
	//     #####    
	//     #####    
	//    ### ###   
	//    ### ###   
	//    ### ###   
	//   ###   ###  
	//   ###   ###  
	//   #########  
	//  ########### 
	//  ########### 
	//  ###     ### 
	// ###       ###
	// ###       ###
	0x00, 0x00, 0xC0, 0xF8, 0xFF, 0x3F, 0x07, 0x3F, 0xFF, 0xF8, 0xC0, 0x00, 0x00, 
	0x30, 0x3E, 0x3F, 0x0F, 0x07, 0x07, 0x07, 0x07, 0x07, 0x0F, 0x3F, 0x3E, 0x30, 

	/* @26 'B' (12 pixels wide) */
	// #########   
	// ##########  
	// ########### 
	// ###     ### 
	// ###     ### 
	// ##########  
	// ##########  
	// ########### 
	// ###      ###
	// ###      ###
	// ###      ###
	// ############
	// ########### 
	// ##########  
	0xFF, 0xFF, 0xFF, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xFF, 0xFE, 0x9C, 0x00, 
	0x3F, 0x3F, 0x3F, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x3F, 0x1F, 0x0F, 

	/* @50 'C' (12 pixels wide) */
	//     #####   
	//   ######### 
	//  ########## 
	//  ###    ####
	// ###      ## 
	// ###         
	// ###         
	// ###         
	// ###         
	// ###      ## 
	//  ###    ####
	//  ########## 
	//   ######### 
	//     #####   
	0xF0, 0xFC, 0xFE, 0x0E, 0x07, 0x07, 0x07, 0x07, 0x0F, 0x1E, 0x1E, 0x08, 
	0x03, 0x0F, 0x1F, 0x1C, 0x38, 0x38, 0x38, 0x38, 0x3C, 0x1E, 0x1E, 0x04, 
};

/* Character descriptors for Arial 14pt */
/* { [Char width in bits], [Offset into arial_14ptCharBitmaps in bytes] } */
const uint8_t Descriptors[][2] = 
{
	{13, 0}, 			/* A */ 
	{12, 26}, 		/* B */ 
	{12, 50}, 		/* C */ 
};
























