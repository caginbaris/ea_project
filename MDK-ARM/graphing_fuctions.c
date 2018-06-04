#include "conversion.h"
#include "graphing_definitions.h"
#include "LCD_definitions.h"
#include "aux_functions.h"
#include "measurement_definitions.h"
#include "menu_definitions.h"
#include <math.h>

#define scope_ypos1 27
#define scope_ypos2 127


float scope_array[100]={0};
float bin_array[20]={0};




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
	uint8_t i;
	
	page=(uint8_t)(x/8);
	xBit=x%8;
	
	for(i=0;i<8;i++){
	
	display_buffer[i][y]=0;
		
	}
	
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
	
	display_buffer[xPage][i]|=1<<xBit;
	
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
	
	display_buffer[startPage][y]|=Data;
	Data=0;	
		
	
	}else{
		
		
	for(i=(startBit);i<8;i++){Data|=(1<<(i));}
		
	display_buffer[startPage][y]|=Data;
	startPage++;

	if(startPage!=endPage){
		
	for(i=(startPage);i<endPage;i++){
	
	display_buffer[i][y]|=0xFF;
	
		}
	}

	Data=0;
	
	for(i=0;i<endBit;i++){Data|=(1<<(i));}
	
	display_buffer[endPage][y]|=Data;
	
	
	}
	
}


void plot_data_formatting(float x,float rms){

	static uint8_t snap_flag=0;
	static long gap_counter=0;
	static uint8_t i=0,j=0;
	float pass_level=0;
	
	
	if(fundRMS.data.Van>20.0 && (phase.data.Van>0.0f && phase.data.Van<0.017f) && snap_flag==0 ){snap_flag=1;}
	
	
	switch(current_menu){
	
		case Scope_Van:pass_level=10;break;
		case Scope_Vbn:pass_level=10;break;
		case Scope_Vcn:pass_level=10;break;
		
		case Scope_Ia:pass_level=0.1;break;
		case Scope_Ib:pass_level=0.1;break;
		case Scope_Ic:pass_level=0.1;break;
		
		default: pass_level=0;break;
	
	}
	
	
	if(rms>pass_level){
	
	
	if(snap_flag){

		if((i++)%2){scope_array[j++]=22.0f*x/(rms*1.414213f);}
		
		
		if(i==200){i=0;j=0;snap_flag=0;}
	
	}

}else{


	scope_array[j++]=0;
	
	if(j==100){j=0;}


}
	
	
	
	
	
}


void scope_plotting(){
	
	
	static uint8_t i=scope_ypos1;
	static uint8_t n=0,s=0;
	int8_t val;
	
	
	for(s=0;s<5;s++){
	
	val=scope_array[n++];
	if(n==100){n=0;}
	
	
	i_limiter(-25,25,&val);
	
	setbit(25-val,i++);
	
	if(i==scope_ypos2){i=scope_ypos1;}
	
}

}


void scope_routine(){
	
	

	
	
	plot_data_formatting(*MENU.all[current_menu].values,trueRMS.buffer[MENU.all[current_menu].first_line[0]]);
	


}









void graphBaseLining(){
	
	uint8_t i;
	
	hline(50,25,125);
	hline(25,24,27);
	hline(12,24,27);
	hline(37,24,27);
	vline(25,0,50);
	vline(50,49,52);
	vline(75,49,52);
	vline(100,49,52);
	
	
	for(i=6;i<14;i++){
	
	
		display_buffer[1][i]=0;
		display_buffer[3][i]=0;
		display_buffer[5][i]=0;
	
	}
	
	letter_transfer_8pt(MENU.all[current_menu].title[0],1,6);
	letter_transfer_8pt(MENU.all[current_menu].title[1],3,6);
	letter_transfer_8pt(MENU.all[current_menu].title[2],5,6);
	
	
	symbol_transfer(MENU.all[current_menu].symbol[0],7,1);
	symbol_transfer(MENU.all[current_menu].symbol[1],7,28);
	symbol_transfer(MENU.all[current_menu].symbol[2],7,59);
	symbol_transfer(MENU.all[current_menu].symbol[3],7,88);
	symbol_transfer(MENU.all[current_menu].symbol[4],7,119);
	
	

}


void graphDataTransfer(){
	
	
	
	scope_plotting();
	


}


void harmonicBaseLine(){
	
	uint8_t column,i;
	
	//title
	
	for(i=0;i<17;i++){
		
	column=letter_transfer_8pt(MENU.all[current_menu].title[i],0,column);
	
	}
	
	line_highlighter(0,128);
	
	//measurement side border
	vline(102,9,55);
	hline(55,0,127);
	
	
	symbol_transfer(MENU.all[current_menu].symbol[0],7,1);
	symbol_transfer(MENU.all[current_menu].symbol[1],7,28);
	symbol_transfer(MENU.all[current_menu].symbol[2],7,59);
	symbol_transfer(MENU.all[current_menu].symbol[3],7,88);
	symbol_transfer(MENU.all[current_menu].symbol[4],7,119);
	
	

}
