
#include "graphing_definitions.h"
#include "LCD_definitions.h"

#define hLineRow 15
#define hLineRowStart 15

#define vLineRow 15
#define vLineRowStart 15
#define vLineRowEnd 15

union LCD_map bitmap;

//graphing lines

//0,0 up left--64,128 down right

//x position of hLine
//line start vertical
//line end   vertical

void setbit(uint8_t x,uint8_t y){

	uint8_t page;
	uint8_t column;
	uint8_t xBit;
	uint8_t xData;
	
	page=(uint8_t)(x/8);
	xBit=x%8;
	
	switch(xBit){
	
		case 0: xData=bitmap.bit.b0;
		case 1: xData=bitmap.bit.b1;
		case 2: xData=bitmap.bit.b2;
		case 3: xData=bitmap.bit.b3;
		case 4: xData=bitmap.bit.b4;
		case 5: xData=bitmap.bit.b5;
		case 6: xData=bitmap.bit.b6;
		case 7: xData=bitmap.bit.b7;
	
	}
		
	display_buffer[page][y]=xData;


}
void hline(uint8_t x, uint8_t lineStart,uint8_t lineEnd){
	
	uint8_t xPage;
	uint8_t xBit;
	uint8_t xData;
	uint8_t i;
	
	xPage=(uint8_t)(x/8);
	xBit=x%8;
	
	switch(xBit){
	
		case 0: xData=bitmap.bit.b0;
		case 1: xData=bitmap.bit.b1;
		case 2: xData=bitmap.bit.b2;
		case 3: xData=bitmap.bit.b3;
		case 4: xData=bitmap.bit.b4;
		case 5: xData=bitmap.bit.b5;
		case 6: xData=bitmap.bit.b6;
		case 7: xData=bitmap.bit.b7;
	
	}
	
	
	for(i=lineStart;i<lineEnd;i++){
	
	display_buffer[xPage][i]=xData;
	
	}
	
}


void vline(uint8_t y, uint8_t lineStart,uint8_t lineEnd){

	uint8_t startPage;
	uint8_t startBit;
	uint8_t startData;
	uint8_t endPage;
	uint8_t endBit;
	uint8_t i;
	
	
	startPage=(uint8_t)(lineStart/8);
	startBit=lineStart%8;
	
	switch(startBit){
	
		case 0: startData=0xFF; //cau row sequnce has to be checked
		case 1: startData=0xFE;
		case 2: startData=bitmap.bit.b2;
		case 3: startData=bitmap.bit.b3;
		case 4: startData=bitmap.bit.b4;
		case 5: startData=bitmap.bit.b5;
		case 6: startData=bitmap.bit.b6;
		case 7: startData=bitmap.bit.b7;
	
	}
	
	
	display_buffer[startPage][y]=startData;
	
	endPage=(uint8_t)(lineEnd/8);
	endBit=lineEnd%8;
	
	
	
	
	
	
	
	for(i=startPage;i<endPage;i++){
	
	display_buffer[i][y]=0xFF;
	
	}
	
	
	




}












void graphBaseLining(){
	

}