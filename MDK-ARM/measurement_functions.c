

#include "conversion.h"


union uAdcData true_RMS(union uAdcData input,uint8_t numberOfPeriod){

	static union uAdcData rms_sum,rms;
	static uint16_t counter=0;
	uint8_t i=0;
	
	
	
	for(i=0;i<8;i++){
	
		rms_sum.buffer[i]+=input.buffer[i];
		
	}
	
	
	if(counter++>=periodSampleNo){counter=0;}

	return rms;
}


