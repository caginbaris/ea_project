#include "conversion.h"
#include "measurement_definitions.h"


float snap[6][20]={0};
uint8_t snap_start=0;

void  waveformSnap(){
	

	
	static uint8_t lock=0;
	static uint8_t sample_count=0;
	static uint8_t decimation_count=0;
	
	if((phase.data.Van>0.0f && phase.data.Van<0.017f) && snap_start==1 ){lock=1;}
	
	
	if(lock){
	

	switch(decimation_count){
	
		case 0:snap[0][0]=AN_pc.data.Van;	break;
		case 1:snap[1][0]=AN_pc.data.Vbn;	break;
		case 2:snap[2][0]=AN_pc.data.Vcn;	break;
		
		case 3:snap[3][0]=AN_pc.data.Ia;	break;
		case 4:snap[4][0]=AN_pc.data.Ib;	break;
		case 5:snap[5][0]=AN_pc.data.Ic;	break;
		
		case 10:decimation_count=0;break;
	
	
	}
	
	decimation_count++;


	

		
		
	
	
	
	
	}
	
	
	
	
	
	


}