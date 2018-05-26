
#include "graphing_definitions.h"
#include "LCD_definitions.h"

#define hLineRow 15
#define hLineRowStart 15

#define vLineRow 15
#define vLineRowStart 15
#define vLineRowEnd 15

union LCD_map bitmap={0xFF};


uint8_t xpos=0;
uint8_t ypos=0;

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
	
	display_buffer[page][y]=1<<xBit;


}
void hline(uint8_t x, uint8_t lineStart,uint8_t lineEnd){
	
	uint8_t xPage;
	uint8_t xBit;
	uint8_t xData;
	uint8_t i;
	
	xPage=(uint8_t)(x/8);
	xBit=x%8;
	
	
	for(i=lineStart;i<lineEnd;i++){
	
	display_buffer[xPage][i]=1<<xBit;
	
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
	

	
	
	display_buffer[startPage][y]=startData;
	
	endPage=(uint8_t)(lineEnd/8);
	endBit=lineEnd%8;
	
	
	
	
	
	
	
	for(i=startPage;i<endPage;i++){
	
	display_buffer[i][y]=0xFF;
	
	}
	
	
	




}












void graphBaseLining(){
	
	
	setbit(xpos,ypos);
	

}


void graphDataTransfer(){
	
	
	hline(0, xpos,ypos);
	

}