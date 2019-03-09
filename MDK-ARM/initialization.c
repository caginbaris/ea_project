

#include "lcd_definitions.h"
#include "aux_functions.h"
#include "initialization.h"

uint8_t initialization_flag=1;
uint32_t initialization_counter=0;

void brand_initialization(void){
	
	
	uint8_t column=0,h;

	enum letter_codes_14pt first[4]=  		{V,I,V,A};
	enum letter_codes_8pt second[10]=  		{e,l,e,k,t,r,o,n,i,k};
	
	

	
	clearColumns(2,0,127);
	clearColumns(3,0,127);
	clearColumns(4,0,127);	
	clearColumns(5,0,127);
	
	for(h=0;h<4;h++){
		
	column=letter_transfer_14pt(first[h],2,column);

	 }
	
	 
	 
	 
	 for(h=0;h<10;h++){
		
		column=letter_transfer_8pt(second[h],5,column);

	 }
	
	

}


void initialization_lag(){

	static uint8_t i=0;
	
	initialization_flag=off_delay(0,initialization_flag,2000,&initialization_counter);
	
	
	if(initialization_counter>1000){
	
	display_buffer[0][i]=0;
	display_buffer[1][i]=0;
	display_buffer[2][i]=0;
	display_buffer[3][i]=0;
	display_buffer[4][i]=0;
	display_buffer[5][i]=0;
	display_buffer[6][i]=0;	
	display_buffer[7][i]=0;	

	if((initialization_counter%7)==0){i++;}		
	
	}

}


