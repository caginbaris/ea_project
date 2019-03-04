#include "conversion.h"
#include "measurement_definitions.h"


float snap[6][20]={0};
uint8_t snap_start=0;

void  waveformSnap(){
	

	
	static uint8_t lock=0;
	static uint8_t decimation_count=0;
	static uint8_t end_count=0;
	
	if((phase>0.0f && phase<0.017f) && snap_start==1 ){lock=1;snap_start=0;}
	
	
	if(lock){
	

	switch(decimation_count){
	
		case 1:snap[0][end_count]=AN_pc.data.Van;	
				   snap[1][end_count]=AN_pc.data.Ia;	break;
		
		case 2:snap[2][end_count]=AN_pc.data.Vbn;
					 snap[3][end_count]=AN_pc.data.Ib;	break;
		
		case 3:snap[4][end_count]=AN_pc.data.Vcn;	
					 snap[5][end_count]=AN_pc.data.Ic;	break;
		
		case 10:decimation_count=0;end_count++;break;
	
	
	}
	
	decimation_count++;
	if(end_count>19){lock=0;decimation_count=0;end_count=0;}
	
	}
	
}