
#include "graphing_definitions.h"
#include "LCD_definitions.h"

#define hLineRow 15
#define hLineRowStart 15

#define vLineRow 15
#define vLineRowStart 15
#define vLineRowEnd 15

union LCD_map bitmap;

//graphing lines

void graphBaseLining(){
	
	uint8_t rowPosition;
	uint8_t rowPage;
	uint8_t rowData;
	uint8_t i;
	
	
	//horizontal line start
	
	rowPage=(uint8_t)(hLineRow/8);
	rowPosition=hLineRow%8;
	
	
	switch(rowPosition){
	
		case 0: rowData=bitmap.bit.b0;
		case 1: rowData=bitmap.bit.b1;
		case 2: rowData=bitmap.bit.b2;
		case 3: rowData=bitmap.bit.b3;
		case 4: rowData=bitmap.bit.b4;
		case 5: rowData=bitmap.bit.b5;
		case 6: rowData=bitmap.bit.b6;
		case 7: rowData=bitmap.bit.b7;
	
	}
	
	for(i=hLineRowStart;i<128;i++){
	
	display_buffer[rowPage][hLineRowStart]=rowData;
	
	}
	
	
	
	
	/*
	for(i=hLineRowStart;i<128;i++){
	
	display_buffer[rowPage][i]=rowData;
	
	}*/
	
	

	
	
	
	
	
	//horizontal_line
	
	
	
	
	
	
	
	
	
	
	
	
	





}