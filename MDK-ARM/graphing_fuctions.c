#include "conversion.h"
#include "graphing_definitions.h"
#include "LCD_definitions.h"
#include "aux_functions.h"
#include "measurement_definitions.h"

#define scope_xpos1 1
#define scope_xpos2 1
#define scope_ypos1 27
#define scope_ypos2 127

float scope_array[100]={0};


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
	uint8_t Data=0;
	uint8_t endPage;
	uint8_t endBit;
	uint8_t i;
	
	
	startPage=(uint8_t)(lineStart/8);
	startBit=lineStart%8;
	
	endPage=(uint8_t)(lineEnd/8);
	endBit=lineEnd%8;
	
	if(startPage==endPage){
	
	
	for(i=(startBit);i<endBit;i++){
	
		Data|=(1<<(i));
		
	}
	
	display_buffer[startPage][y]=Data;
		
		
	
	}else{
		
		
	for(i=(startBit);i<8;i++){Data|=(1<<(i));}
		
	display_buffer[startPage][y]=Data;
	startPage++;


	for(i=(startPage);i<endPage;i++){
	
	display_buffer[i][y]=0xFF;
	
	}	
	
	for(i=0;i<endBit;i++){Data|=(1<<(i));}
	
	display_buffer[endPage][y]=Data;
	
	
	}
	
}


void plot_data_formatting(float x,float rms){

	static uint8_t snap_flag=0;
	static long gap_counter=0;
	static uint8_t i=0,j=0;
	
	if((phase.data.Van>0.0f && phase.data.Van<0.017f) && snap_flag==0 ){snap_flag=1;}
	
	
	if(snap_flag){

		if((i++)%2){scope_array[j++]=20.0f*x/(rms*1.414213f);}
		
		if(i==200){i=0;j=0;snap_flag=0;}
	
	}
	
	
	
}


void scope_plotting(){
	
	
	static uint8_t i;
	int8_t val;
	
	val=scope_array[i];
	
	i_limiter(-25,25,&val);
	
	setbit(25-val,i++);
	
	if(i==scope_ypos2){i=scope_ypos1;}

}









void graphBaseLining(){
	
	
	
	

}


void graphDataTransfer(){
	
	
	
	

}