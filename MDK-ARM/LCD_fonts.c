
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

	/* @74 'D' (12 pixels wide) */
	// #########   
	// ##########  
	// ########### 
	// ###     ### 
	// ###      ###
	// ###      ###
	// ###      ###
	// ###      ###
	// ###      ###
	// ###      ###
	// ###     ### 
	// ########### 
	// ##########  
	// #########   
	0xFF, 0xFF, 0xFF, 0x07, 0x07, 0x07, 0x07, 0x07, 0x0F, 0xFE, 0xFC, 0xF0, 
	0x3F, 0x3F, 0x3F, 0x38, 0x38, 0x38, 0x38, 0x38, 0x3C, 0x1F, 0x0F, 0x03, 

	/* @98 'E' (11 pixels wide) */
	// ###########
	// ###########
	// ###########
	// ###        
	// ###        
	// ########## 
	// ########## 
	// ########## 
	// ###        
	// ###        
	// ###        
	// ###########
	// ###########
	// ###########
	0xFF, 0xFF, 0xFF, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0x07, 
	0x3F, 0x3F, 0x3F, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 

	/* @120 'F' (10 pixels wide) */
	// ##########
	// ##########
	// ##########
	// ###       
	// ###       
	// ######### 
	// ######### 
	// ######### 
	// ###       
	// ###       
	// ###       
	// ###       
	// ###       
	// ###       
	0xFF, 0xFF, 0xFF, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0x07, 
	0x3F, 0x3F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	/* @140 'G' (13 pixels wide) */
	//     ######   
	//   ########## 
	//  ########### 
	//  ####    ####
	// ####      ## 
	// ###          
	// ###          
	// ###    ######
	// ###    ######
	// ####   ######
	//  ####     ###
	//  ############
	//   ########## 
	//     ######   
	0xF0, 0xFC, 0xFE, 0x1E, 0x0F, 0x07, 0x07, 0x87, 0x87, 0x8F, 0x9E, 0x9E, 0x88, 
	0x03, 0x0F, 0x1F, 0x1E, 0x3C, 0x38, 0x38, 0x3B, 0x3B, 0x3B, 0x1F, 0x1F, 0x0F, 

	/* @166 'H' (11 pixels wide) */
	// ###     ###
	// ###     ###
	// ###     ###
	// ###     ###
	// ###     ###
	// ###########
	// ###########
	// ###########
	// ###     ###
	// ###     ###
	// ###     ###
	// ###     ###
	// ###     ###
	// ###     ###
	0xFF, 0xFF, 0xFF, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xFF, 0xFF, 0xFF, 
	0x3F, 0x3F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x3F, 0x3F, 

	/* @188 'I' (3 pixels wide) */
	// ###
	// ###
	// ###
	// ###
	// ###
	// ###
	// ###
	// ###
	// ###
	// ###
	// ###
	// ###
	// ###
	// ###
	0xFF, 0xFF, 0xFF, 
	0x3F, 0x3F, 0x3F, 

	/* @194 'J' (10 pixels wide) */
	//        ###
	//        ###
	//        ###
	//        ###
	//        ###
	//        ###
	//        ###
	//        ###
	//        ###
	// ###    ###
	// ###    ###
	// ##########
	//  ######## 
	//   ######  
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 
	0x0E, 0x1E, 0x3E, 0x38, 0x38, 0x38, 0x38, 0x3F, 0x1F, 0x0F, 

	/* @214 'K' (12 pixels wide) */
	// ###     ####
	// ###    #### 
	// ###   ####  
	// ###  ####   
	// ###  ###    
	// ### ###     
	// ########    
	// #########   
	// ####  ###   
	// ###    ###  
	// ###    ###  
	// ###     ### 
	// ###      ###
	// ###      ###
	0xFF, 0xFF, 0xFF, 0xC0, 0xE0, 0xF8, 0xFC, 0xDE, 0x8F, 0x07, 0x03, 0x01, 
	0x3F, 0x3F, 0x3F, 0x01, 0x00, 0x00, 0x01, 0x07, 0x0F, 0x3E, 0x38, 0x30, 

	/* @238 'L' (10 pixels wide) */
	// ###       
	// ###       
	// ###       
	// ###       
	// ###       
	// ###       
	// ###       
	// ###       
	// ###       
	// ###       
	// ###       
	// ##########
	// ##########
	// ##########
	0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x3F, 0x3F, 0x3F, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 

	/* @258 'M' (15 pixels wide) */
	// #####     #####
	// #####     #####
	// ######   ######
	// ### ##   ## ###
	// ### ##   ## ###
	// ### ##   ## ###
	// ### ### ### ###
	// ###  ## ##  ###
	// ###  ## ##  ###
	// ###  ## ##  ###
	// ###  #####  ###
	// ###   ###   ###
	// ###   ###   ###
	// ###   ###   ###
	0xFF, 0xFF, 0xFF, 0x07, 0x7F, 0xFC, 0xC0, 0x00, 0xC0, 0xFC, 0x7F, 0x07, 0xFF, 0xFF, 0xFF, 
	0x3F, 0x3F, 0x3F, 0x00, 0x00, 0x07, 0x3F, 0x3C, 0x3F, 0x07, 0x00, 0x00, 0x3F, 0x3F, 0x3F, 

	/* @288 'N' (11 pixels wide) */
	// ####    ###
	// ####    ###
	// #####   ###
	// #####   ###
	// ######  ###
	// ### ##  ###
	// ### ### ###
	// ###  ## ###
	// ###  ######
	// ###   #####
	// ###   #####
	// ###    ####
	// ###    ####
	// ###     ###
	0xFF, 0xFF, 0xFF, 0x1F, 0x7C, 0xF0, 0xC0, 0x00, 0xFF, 0xFF, 0xFF, 
	0x3F, 0x3F, 0x3F, 0x00, 0x00, 0x01, 0x07, 0x1F, 0x3F, 0x3F, 0x3F, 

	/* @310 'O' (13 pixels wide) */
	//     #####    
	//   #########  
	//  ########### 
	//  ####   #### 
	// ####     ####
	// ###       ###
	// ###       ###
	// ###       ###
	// ###       ###
	// ####     ####
	//  ####   #### 
	//  ########### 
	//   #########  
	//     #####    
	0xF0, 0xFC, 0xFE, 0x1E, 0x0F, 0x07, 0x07, 0x07, 0x0F, 0x1E, 0xFE, 0xFC, 0xF0, 
	0x03, 0x0F, 0x1F, 0x1E, 0x3C, 0x38, 0x38, 0x38, 0x3C, 0x1E, 0x1F, 0x0F, 0x03, 

	/* @336 'P' (11 pixels wide) */
	// #########  
	// ########## 
	// ###########
	// ###    ####
	// ###     ###
	// ###    ####
	// ###########
	// ########## 
	// #########  
	// ###        
	// ###        
	// ###        
	// ###        
	// ###        
	0xFF, 0xFF, 0xFF, 0xC7, 0xC7, 0xC7, 0xC7, 0xEF, 0xFF, 0xFE, 0x7C, 
	0x3F, 0x3F, 0x3F, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 

	/* @358 'Q' (14 pixels wide) */
	//     #####     
	//   #########   
	//  ###########  
	//  ####   ####  
	// ####     #### 
	// ###       ### 
	// ###       ### 
	// ###       ### 
	// ###    #  ### 
	// ####  ### ### 
	//  ####  #####  
	//  ###########  
	//   ########### 
	//     ##### ####
	//             # 
	0xF0, 0xFC, 0xFE, 0x1E, 0x0F, 0x07, 0x07, 0x07, 0x0F, 0x1E, 0xFE, 0xFC, 0xF0, 0x00, 
	0x03, 0x0F, 0x1F, 0x1E, 0x3C, 0x38, 0x3A, 0x3F, 0x3E, 0x1C, 0x3F, 0x3F, 0x73, 0x20, 

	/* @386 'R' (12 pixels wide) */
	// #########   
	// ##########  
	// ########### 
	// ###     ### 
	// ###     ### 
	// ###     ### 
	// ##########  
	// ##########  
	// ########    
	// ###  ####   
	// ###   ####  
	// ###    ###  
	// ###    #### 
	// ###     ####
	0xFF, 0xFF, 0xFF, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xFF, 0xFE, 0x3C, 0x00, 
	0x3F, 0x3F, 0x3F, 0x01, 0x01, 0x03, 0x07, 0x1F, 0x3E, 0x3C, 0x30, 0x20, 

	/* @410 'S' (11 pixels wide) */
	//   ######   
	//  ######### 
	// ########## 
	// ###    ####
	// ###     ###
	// #####      
	//  #######   
	//   ######## 
	//       #####
	// ###     ###
	// ####    ###
	//  ##########
	//  ######### 
	//    ######  
	0x3C, 0x7E, 0xFF, 0xE7, 0xE7, 0xC7, 0xC7, 0xCF, 0x9E, 0x9E, 0x18, 
	0x06, 0x1E, 0x1E, 0x3C, 0x38, 0x38, 0x39, 0x39, 0x3F, 0x1F, 0x0F, 

	/* @432 'T' (11 pixels wide) */
	// ###########
	// ###########
	// ###########
	//     ###    
	//     ###    
	//     ###    
	//     ###    
	//     ###    
	//     ###    
	//     ###    
	//     ###    
	//     ###    
	//     ###    
	//     ###    
	0x07, 0x07, 0x07, 0x07, 0xFF, 0xFF, 0xFF, 0x07, 0x07, 0x07, 0x07, 
	0x00, 0x00, 0x00, 0x00, 0x3F, 0x3F, 0x3F, 0x00, 0x00, 0x00, 0x00, 

	/* @454 'U' (11 pixels wide) */
	// ###     ###
	// ###     ###
	// ###     ###
	// ###     ###
	// ###     ###
	// ###     ###
	// ###     ###
	// ###     ###
	// ###     ###
	// ###     ###
	// ####   ####
	//  ######### 
	//  ######### 
	//    #####   
	0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 
	0x07, 0x1F, 0x1F, 0x3C, 0x38, 0x38, 0x38, 0x3C, 0x1F, 0x1F, 0x07, 

	/* @476 'V' (13 pixels wide) */
	// ###       ###
	//  ###     ### 
	//  ###     ### 
	//  ###     ### 
	//   ###   ###  
	//   ###   ###  
	//   ###   ###  
	//    ### ###   
	//    ### ###   
	//    ### ###   
	//     #####    
	//     #####    
	//     #####    
	//      ###     
	0x01, 0x0F, 0x7F, 0xFE, 0xF0, 0x80, 0x00, 0x80, 0xF0, 0xFE, 0x7F, 0x0F, 0x01, 
	0x00, 0x00, 0x00, 0x03, 0x1F, 0x3F, 0x3C, 0x3F, 0x1F, 0x03, 0x00, 0x00, 0x00, 

	/* @502 'W' (17 pixels wide) */
	// ###    ###    ###
	// ###    ###    ###
	// ###   #####   ###
	//  ###  #####  ### 
	//  ###  ## ##  ### 
	//  ###  ## ##  ### 
	//  ### ### ### ### 
	//  ### ### ### ### 
	//  ### ##   ## ### 
	//  ### ##   ## ### 
	//   #####   #####  
	//   #####   #####  
	//   ####     ####  
	//   ####     ####  
	0x07, 0xFF, 0xFF, 0xF8, 0x00, 0xC0, 0xFC, 0xFF, 0x0F, 0xFF, 0xFC, 0xC0, 0x00, 0xF8, 0xFF, 0xFF, 0x07, 
	0x00, 0x03, 0x3F, 0x3F, 0x3C, 0x3F, 0x0F, 0x00, 0x00, 0x00, 0x0F, 0x3F, 0x3C, 0x3F, 0x3F, 0x03, 0x00, 

	/* @536 'X' (11 pixels wide) */
	// ###     ###
	// ###     ###
	//  ###   ### 
	//   ### ###  
	//   ### ###  
	//    #####   
	//     ###    
	//     ###    
	//    #####   
	//   ### ###  
	//   ### ###  
	//  ###   ### 
	// ###     ###
	// ###     ###
	0x03, 0x07, 0x1F, 0x3C, 0xF8, 0xE0, 0xF8, 0x3C, 0x1F, 0x07, 0x03, 
	0x30, 0x38, 0x3E, 0x0F, 0x07, 0x01, 0x07, 0x0F, 0x3E, 0x38, 0x30, 

	/* @558 'Y' (11 pixels wide) */
	// ###     ###
	// ###     ###
	//  ###   ### 
	//  ###   ### 
	//   ### ###  
	//    #####   
	//    #####   
	//     ###    
	//     ###    
	//     ###    
	//     ###    
	//     ###    
	//     ###    
	//     ###    
	0x03, 0x0F, 0x1F, 0x7C, 0xF0, 0xE0, 0xF0, 0x7C, 0x1F, 0x0F, 0x03, 
	0x00, 0x00, 0x00, 0x00, 0x3F, 0x3F, 0x3F, 0x00, 0x00, 0x00, 0x00, 

	/* @580 'Z' (11 pixels wide) */
	//  ##########
	//  ##########
	//  ##########
	//        ####
	//       #### 
	//      ####  
	//     ####   
	//    ####    
	//   ####     
	//  ####      
	// ####       
	// ###########
	// ###########
	// ###########
	0x00, 0x07, 0x07, 0x87, 0xC7, 0xE7, 0xF7, 0x7F, 0x3F, 0x1F, 0x0F, 
	0x3C, 0x3E, 0x3F, 0x3F, 0x3B, 0x39, 0x38, 0x38, 0x38, 0x38, 0x38, 
};

/* Character descriptors for Arial 14pt */
/* { [Char width in bits], [Offset into arial_14ptCharBitmaps in bytes] } */
const uint16_t Descriptors[][2] = 
{
	{13, 0}, 		/* A */ 
	{12, 26}, 		/* B */ 
	{12, 50}, 		/* C */ 
	{12, 74}, 		/* D */ 
	{11, 98}, 		/* E */ 
	{10, 120}, 		/* F */ 
	{13, 140}, 		/* G */ 
	{11, 166}, 		/* H */ 
	{3, 188}, 		/* I */ 
	{10, 194}, 		/* J */ 
	{12, 214}, 		/* K */ 
	{10, 238}, 		/* L */ 
	{15, 258}, 		/* M */ 
	{11, 288}, 		/* N */ 
	{13, 310}, 		/* O */ 
	{11, 336}, 		/* P */ 
	{14, 358}, 		/* Q */ 
	{12, 386}, 		/* R */ 
	{11, 410}, 		/* S */ 
	{11, 432}, 		/* T */ 
	{11, 454}, 		/* U */ 
	{13, 476}, 		/* V */ 
	{17, 502}, 		/* W */ 
	{11, 536}, 		/* X */ 
	{11, 558}, 		/* Y */ 
	{11, 580}, 		/* Z */ 
};



const uint8_t arial_8ptBitmaps[] = 
{
	/* @0 'A' (7 pixels wide) */
	//    #   
	//   # #  
	//   # #  
	//   # #  
	//  #   # 
	//  ##### 
	// #     #
	// #     #
	0xC0, 0x30, 0x2E, 0x21, 0x2E, 0x30, 0xC0, 

	/* @7 'B' (6 pixels wide) */
	// ##### 
	// #    #
	// #    #
	// ######
	// #    #
	// #    #
	// #    #
	// ##### 
	0xFF, 0x89, 0x89, 0x89, 0x89, 0x7E, 

	/* @13 'C' (6 pixels wide) */
	//   ### 
	//  #   #
	// #     
	// #     
	// #     
	// #     
	//  #   #
	//   ### 
	0x3C, 0x42, 0x81, 0x81, 0x81, 0x42, 

	/* @19 'D' (6 pixels wide) */
	// ####  
	// #   # 
	// #    #
	// #    #
	// #    #
	// #    #
	// #   # 
	// ####  
	0xFF, 0x81, 0x81, 0x81, 0x42, 0x3C, 

	/* @25 'E' (5 pixels wide) */
	// #####
	// #    
	// #    
	// #####
	// #    
	// #    
	// #    
	// #####
	0xFF, 0x89, 0x89, 0x89, 0x89, 

	/* @30 'F' (5 pixels wide) */
	// #####
	// #    
	// #    
	// #### 
	// #    
	// #    
	// #    
	// #    
	0xFF, 0x09, 0x09, 0x09, 0x01, 

	/* @35 'G' (7 pixels wide) */
	//   ###  
	//  #   # 
	// #     #
	// #      
	// #   ###
	// #     #
	//  #   # 
	//   ###  
	0x3C, 0x42, 0x81, 0x81, 0x91, 0x52, 0x34, 

	/* @42 'H' (6 pixels wide) */
	// #    #
	// #    #
	// #    #
	// ######
	// #    #
	// #    #
	// #    #
	// #    #
	0xFF, 0x08, 0x08, 0x08, 0x08, 0xFF, 

	/* @48 'I' (1 pixels wide) */
	// #
	// #
	// #
	// #
	// #
	// #
	// #
	// #
	0xFF, 

	/* @49 'J' (4 pixels wide) */
	//    #
	//    #
	//    #
	//    #
	//    #
	// #  #
	// #  #
	//  ## 
	0x60, 0x80, 0x80, 0x7F, 

	/* @53 'K' (6 pixels wide) */
	// #    #
	// #   # 
	// #  #  
	// # ##  
	// ## #  
	// #   # 
	// #   # 
	// #    #
	0xFF, 0x10, 0x08, 0x1C, 0x62, 0x81, 

	/* @59 'L' (5 pixels wide) */
	// #    
	// #    
	// #    
	// #    
	// #    
	// #    
	// #    
	// #####
	0xFF, 0x80, 0x80, 0x80, 0x80, 

	/* @64 'M' (7 pixels wide) */
	// #     #
	// ##   ##
	// ##   ##
	// # # # #
	// # # # #
	// # # # #
	// #  #  #
	// #  #  #
	0xFF, 0x06, 0x38, 0xC0, 0x38, 0x06, 0xFF, 

	/* @71 'N' (6 pixels wide) */
	// #    #
	// ##   #
	// # #  #
	// # #  #
	// #  # #
	// #  # #
	// #   ##
	// #    #
	0xFF, 0x02, 0x0C, 0x30, 0x40, 0xFF, 

	/* @77 'O' (7 pixels wide) */
	//   ###  
	//  #   # 
	// #     #
	// #     #
	// #     #
	// #     #
	//  #   # 
	//   ###  
	0x3C, 0x42, 0x81, 0x81, 0x81, 0x42, 0x3C, 

	/* @84 'P' (5 pixels wide) */
	// #### 
	// #   #
	// #   #
	// #   #
	// #### 
	// #    
	// #    
	// #    
	0xFF, 0x11, 0x11, 0x11, 0x0E, 

	/* @89 'Q' (7 pixels wide) */
	//   ###  
	//  #   # 
	// #     #
	// #     #
	// #     #
	// #  ## #
	//  #   # 
	//   ### #
	0x3C, 0x42, 0x81, 0xA1, 0xA1, 0x42, 0xBC, 

	/* @96 'R' (6 pixels wide) */
	// ##### 
	// #    #
	// #    #
	// ##### 
	// #  #  
	// #   # 
	// #   # 
	// #    #
	0xFF, 0x09, 0x09, 0x19, 0x69, 0x86, 

	/* @102 'S' (6 pixels wide) */
	//  #### 
	// #    #
	// #     
	//  ##   
	//    ## 
	//      #
	// #    #
	//  #### 
	0x46, 0x89, 0x89, 0x91, 0x91, 0x62, 

	/* @108 'T' (5 pixels wide) */
	// #####
	//   #  
	//   #  
	//   #  
	//   #  
	//   #  
	//   #  
	//   #  
	0x01, 0x01, 0xFF, 0x01, 0x01, 

	/* @113 'U' (6 pixels wide) */
	// #    #
	// #    #
	// #    #
	// #    #
	// #    #
	// #    #
	// #    #
	//  #### 
	0x7F, 0x80, 0x80, 0x80, 0x80, 0x7F, 

	/* @119 'V' (7 pixels wide) */
	// #     #
	// #     #
	//  #   # 
	//  #   # 
	//   # #  
	//   # #  
	//    #   
	//    #   
	0x03, 0x0C, 0x30, 0xC0, 0x30, 0x0C, 0x03, 

	/* @126 'W' (11 pixels wide) */
	// #    #    #
	// #   # #   #
	//  #  # #  # 
	//  #  # #  # 
	//  # #   # # 
	//  # #   # # 
	//   #     #  
	//   #     #  
	0x03, 0x3C, 0xC0, 0x30, 0x0E, 0x01, 0x0E, 0x30, 0xC0, 0x3C, 0x03, 

	/* @137 'X' (6 pixels wide) */
	// #    #
	//  #  # 
	//  #  # 
	//   ##  
	//   ##  
	//  #  # 
	//  #  # 
	// #    #
	0x81, 0x66, 0x18, 0x18, 0x66, 0x81, 

	/* @143 'Y' (7 pixels wide) */
	// #     #
	//  #   # 
	//  #   # 
	//   # #  
	//    #   
	//    #   
	//    #   
	//    #   
	0x01, 0x06, 0x08, 0xF0, 0x08, 0x06, 0x01, 

	/* @150 'Z' (6 pixels wide) */
	//  #####
	//     # 
	//    #  
	//    #  
	//   #   
	//   #   
	//  #    
	// ######
	0x80, 0xC1, 0xB1, 0x8D, 0x83, 0x81, 
	
	//space
	
	0x00,0x00,0x00,0x00
	
	

};

/* Character descriptors for Arial 8pt */
/* { [Char width in bits], [Offset into arial_8ptCharBitmaps in bytes] } */
const uint16_t Descriptors2[][2] = 
{
	{7, 0}, 		/* A */ 
	{6, 7}, 		/* B */ 
	{6, 13}, 		/* C */ 
	{6, 19}, 		/* D */ 
	{5, 25}, 		/* E */ 
	{5, 30}, 		/* F */ 
	{7, 35}, 		/* G */ 
	{6, 42}, 		/* H */ 
	{1, 48}, 		/* I */ 
	{4, 49}, 		/* J */ 
	{6, 53}, 		/* K */ 
	{5, 59}, 		/* L */ 
	{7, 64}, 		/* M */ 
	{6, 71}, 		/* N */ 
	{7, 77}, 		/* O */ 
	{5, 84}, 		/* P */ 
	{7, 89}, 		/* Q */ 
	{6, 96}, 		/* R */ 
	{6, 102}, 		/* S */ 
	{5, 108}, 		/* T */ 
	{6, 113}, 		/* U */ 
	{7, 119}, 		/* V */ 
	{11, 126}, 		/* W */ 
	{6, 137}, 		/* X */ 
	{7, 143}, 		/* Y */ 
	{6, 150}, 		/* Z */ 
	{4, 156}, 		/* space */ 
};



//symbol fonts-generated by hand


const uint8_t button_symbols[][8]={

//blank
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
//enter
{0x00, 0x1f, 0x3f, 0x30, 0x30, 0xfc, 0x78, 0x30},
//escape
{0x78, 0xc8, 0xbe, 0x9d, 0x89, 0xc3, 0x7e, 0x18},
//left
{ 0x18, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3},
//right
{0xc3, 0xc3, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x18},
//down
{0x03, 0x0e, 0x3c, 0xf0, 0xf0, 0x3c, 0x0e, 0x03},
//up
{ 0xc0, 0x78, 0x1c, 0x07, 0x07, 0x1c, 0x78, 0xc0},

	

};



/* 
**  Font data for Book Antiqua 14pt
*/

/* Character bitmaps for Book Antiqua 14pt */
const uint8_t bookAntiqua_14ptBitmaps[] = 
{
	/* @0 '0' (11 pixels wide) */
	//    ####    
	//   ##  ##   
	//   ##  ###  
	//  ###  ###  
	//  ###  ###  
	//  ###  ###  
	//  ###  ###  
	//  ###  ###  
	//  ###  ###  
	//  ###  ###  
	//  ###  ##   
	//   ##  ##   
	//    ####    
	0x00, 0xF8, 0xFE, 0xFF, 0x01, 0x01, 0xFF, 0xFE, 0xFC, 0x00, 0x00, 
	0x00, 0x07, 0x0F, 0x1F, 0x10, 0x10, 0x1F, 0x0F, 0x03, 0x00, 0x00, 

	/* @22 '1' (11 pixels wide) */
	//       #    
	//    ####    
	//  ## ###    
	//     ###    
	//     ###    
	//     ###    
	//     ###    
	//     ###    
	//     ###    
	//     ###    
	//     ###    
	//     ###    
	//   #######  
	0x00, 0x04, 0x04, 0x02, 0xFE, 0xFE, 0xFF, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x10, 0x10, 0x1F, 0x1F, 0x1F, 0x10, 0x10, 0x00, 0x00, 

	/* @44 '2' (11 pixels wide) */
	//   #####    
	// ########   
	// ##   ####  
	// #     ###  
	// #     ###  
	//       ##   
	//      ###   
	//      ##    
	//     ##     
	//    #       
	//   #        
	//  ########  
	// #########  
	0x1E, 0x06, 0x03, 0x03, 0x03, 0xC7, 0xFF, 0x7E, 0x1C, 0x00, 0x00, 
	0x10, 0x18, 0x1C, 0x1A, 0x19, 0x19, 0x18, 0x18, 0x18, 0x00, 0x00, 

	/* @66 '3' (11 pixels wide) */
	//    #####   
	//   #######  
	//  ##   ###  
	//  #    ###  
	//       ##   
	//      ##    
	//    #####   
	//      ####  
	//       ###  
	// #     ###  
	// ##    ##   
	//  #   ###   
	//  #####     
	0x00, 0x0C, 0x06, 0x43, 0x43, 0xE3, 0xFF, 0xDF, 0x8E, 0x00, 0x00, 
	0x06, 0x1C, 0x10, 0x10, 0x10, 0x18, 0x0F, 0x0F, 0x03, 0x00, 0x00, 

	/* @88 '4' (11 pixels wide) */
	//      ###   
	//     ####   
	//     ####   
	//    # ###   
	//   #  ###   
	//   #  ###   
	//  #   ###   
	//  #   ###   
	// ###########
	// ###########
	//      ###   
	//      ###   
	//    ####### 
	0x00, 0xC0, 0x30, 0x08, 0x06, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 
	0x03, 0x03, 0x03, 0x13, 0x13, 0x1F, 0x1F, 0x1F, 0x13, 0x13, 0x03, 

	/* @110 '5' (11 pixels wide) */
	//  ########  
	//  ########  
	//  #         
	//  #         
	//  #         
	//  ######    
	//  #######   
	//  #   ####  
	//       ###  
	//       ###  
	// #     ##   
	// ##   ##    
	//  #####     
	0x00, 0xFF, 0x63, 0x63, 0x63, 0xE3, 0xE3, 0xC3, 0x83, 0x00, 0x00, 
	0x0C, 0x18, 0x10, 0x10, 0x10, 0x18, 0x0F, 0x07, 0x03, 0x00, 0x00, 

	/* @132 '6' (11 pixels wide) */
	//      ###   
	//     ##     
	//    ##      
	//   ##       
	//  ### ###   
	//  ########  
	//  ###  ###  
	//  ###  ###  
	//  ###  ###  
	//  ###  ###  
	//  ###  ###  
	//   ##  ##   
	//    ####    
	0x00, 0xF0, 0xF8, 0xFC, 0x26, 0x33, 0xF1, 0xF1, 0xE0, 0x00, 0x00, 
	0x00, 0x07, 0x0F, 0x1F, 0x10, 0x10, 0x1F, 0x0F, 0x07, 0x00, 0x00, 

	/* @154 '7' (11 pixels wide) */
	//  ######### 
	//  ######### 
	//  #      #  
	//  #     ##  
	//  #     #   
	//       ##   
	//       #    
	//      ##    
	//     ##     
	//     ##     
	//    ##      
	//    ##      
	//   ##       
	0x00, 0x1F, 0x03, 0x03, 0x03, 0x83, 0xE3, 0x3B, 0x0F, 0x03, 0x00, 
	0x00, 0x00, 0x10, 0x1C, 0x0F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 

	/* @176 '8' (11 pixels wide) */
	//   #####    
	//  ##   ##   
	// ###   ##   
	// ###   ##   
	// ####  #    
	//  #####     
	//    #####   
	//  ##  ####  
	// ###   ###  
	// ###   ###  
	// ###   ###  
	//  ###  ##   
	//   #####    
	0x1C, 0xBE, 0xBF, 0x71, 0x61, 0xE1, 0xDF, 0xCE, 0x80, 0x00, 0x00, 
	0x07, 0x0F, 0x1F, 0x18, 0x10, 0x10, 0x1F, 0x0F, 0x07, 0x00, 0x00, 

	/* @198 '9' (11 pixels wide) */
	//    ####    
	//   ##  ##   
	//  ###  ###  
	//  ###  ###  
	//  ###  ###  
	//  ###  ###  
	//  ########  
	//   ### ###  
	//       ###  
	//      ###   
	//      ##    
	//     ##     
	//   ###      
	0x00, 0x7C, 0xFE, 0xFF, 0xC1, 0x41, 0xFF, 0xFE, 0xFC, 0x00, 0x00, 
	0x00, 0x00, 0x10, 0x10, 0x18, 0x0E, 0x07, 0x03, 0x01, 0x00, 0x00, 
};

/* Character descriptors for Book Antiqua 14pt */
/* { [Char width in bits], [Offset into bookAntiqua_14ptCharBitmaps in bytes] } */
const uint16_t Descriptors3[][2] = 
{
	{11, 0}, 		/* 0 */ 
	{11, 22}, 		/* 1 */ 
	{11, 44}, 		/* 2 */ 
	{11, 66}, 		/* 3 */ 
	{11, 88}, 		/* 4 */ 
	{11, 110}, 		/* 5 */ 
	{11, 132}, 		/* 6 */ 
	{11, 154}, 		/* 7 */ 
	{11, 176}, 		/* 8 */ 
	{11, 198}, 		/* 9 */ 
};








const uint8_t unit_charecters[] = {
	
	/* @0 'G' (6 pixels wide) */
	//  #### 
	// ##  ##
	// ##  ##
	// ##    
	// ## ###
	// ##  ##
	// ##  ##
	// ##  ##
	//  #### 
	0xFE, 0xFF, 0x01, 0x11, 0xF7, 0xF6, 
	0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 

	/* @12 'K' (6 pixels wide) */
	// ##  ##
	// ## ## 
	// ## ## 
	// ####  
	// ##### 
	// ## ## 
	// ##  ##
	// ##  ##
	// ##  ##
	0xFF, 0xFF, 0x18, 0x3E, 0xF7, 0xC1, 
	0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 

	/* @24 'M' (7 pixels wide) */
	// ##   ##
	// ##   ##
	// ##   ##
	// ### ###
	// ### ###
	// #### ##
	// ## # ##
	// ## # ##
	// ## # ##
	0xFF, 0xFF, 0x38, 0xE0, 0x18, 0xFF, 0xFF, 
	0x01, 0x01, 0x00, 0x01, 0x00, 0x01, 0x01, 





};


const uint16_t Descriptors4[][2] = 
{
	{6, 0}, 		/* G */ 
	{6, 12}, 		/* K */ 
	{7, 24}, 		/* M */ 
};





const uint8_t menu_units_ch[] = {
	
	/* @0 '%' (9 pixels wide) */
	// ###   #  
	// # #   #  
	// # #  #   
	// # #  #   
	// ### # ###
	//    #  # #
	//    #  # #
	//   #   # #
	//   #    ##
	0x1F, 0x11, 0x9F, 0x60, 0x10, 0x0C, 0xF3, 0x10, 0xF0, 
	0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 

	/* @18 'A' (7 pixels wide) */
	//   ###  
	//   ###  
	//  ## ## 
	//  ## ## 
	//  ## ## 
	//  ##### 
	//  ## ## 
	// ##   ##
	// ##   ##
	0x80, 0xFC, 0x7F, 0x23, 0x7F, 0xFC, 0x80, 
	0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 

	/* @32 'R' (7 pixels wide) */
	// #####  
	// ##  ## 
	// ##  ## 
	// ##  ## 
	// #####  
	// ## ##  
	// ## ### 
	// ##  ## 
	// ##   ##
	0xFF, 0xFF, 0x11, 0x71, 0xFF, 0xCE, 0x00, 
	0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 

	/* @46 'V' (7 pixels wide) */
	// ##   ##
	// ##   ##
	//  ## ## 
	//  ## ## 
	//  ## ## 
	//  ## ## 
	//  ## ## 
	//   ###  
	//   ###  
	0x03, 0x7F, 0xFC, 0x80, 0xFC, 0x7F, 0x03, 
	0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 

	/* @60 'W' (11 pixels wide) */
	// ##   #   ##
	// ##   #   ##
	//  ## # # ## 
	//  ## # # ## 
	//  ## # # ## 
	//  ## # # ## 
	//   ##  # #  
	//   ##   ##  
	//   ##   ##  
	0x03, 0x3F, 0xFC, 0xC0, 0x3C, 0x03, 0x7C, 0x80, 0xFC, 0x3F, 0x03, 
	0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 

	/* @82 'h' (6 pixels wide) */
	// ##    
	// ##    
	// ##### 
	// ##  ##
	// ##  ##
	// ##  ##
	// ##  ##
	// ##  ##
	// ##  ##
	0xFF, 0xFF, 0x04, 0x04, 0xFC, 0xF8, 
	0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 
	



};


/* Character descriptors for Arial Narrow 10pt */
/* { [Char width in bits], [Offset into arialNarrow_10ptCharBitmaps in bytes] } */
const uint16_t Descriptors5[][2]= 
{
	{9, 0}, 		/* % */ 
	{7, 18}, 		/* A */ 
	{7, 32}, 		/* R */ 
	{7, 46}, 		/* V */ 
	{11, 60}, 	/* W */ 
	{6, 82}, 		/* h */

};












