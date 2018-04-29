

#include "conversion.h"
#include "measurement_definitions.h"
#include <math.h>




union uAdcData true_RMS(union uAdcData input,uint8_t numberOfPeriod){

	static union uAdcData rms_sum,rms;
	static uint16_t counter=0;
	float inverse_avg_sample=1.0f;
	uint8_t i=0;
	
	
	inverse_avg_sample=1/(periodSampleNo*numberOfPeriod);
	
	
	
	for(i=0;i<9;i++){
	
		rms_sum.buffer[i]+=input.buffer[i];
	
	}
	
	switch(counter){
	
		case 0:rms.buffer[0]=sqrtf(rms_sum.buffer[0]*inverse_avg_sample);rms_sum.buffer[0]=0.0f;break;
		case 1:rms.buffer[1]=sqrtf(rms_sum.buffer[1]*inverse_avg_sample);rms_sum.buffer[1]=0.0f;break;
		case 2:rms.buffer[2]=sqrtf(rms_sum.buffer[2]*inverse_avg_sample);rms_sum.buffer[2]=0.0f;break;
		
		case 3:rms.buffer[3]=sqrtf(rms_sum.buffer[3]*inverse_avg_sample);rms_sum.buffer[3]=0.0f;break;
		case 4:rms.buffer[4]=sqrtf(rms_sum.buffer[4]*inverse_avg_sample);rms_sum.buffer[4]=0.0f;break;
		case 5:rms.buffer[5]=sqrtf(rms_sum.buffer[5]*inverse_avg_sample);rms_sum.buffer[5]=0.0f;break;
		
		case 6:rms.buffer[6]=sqrtf(rms_sum.buffer[6]*inverse_avg_sample);rms_sum.buffer[6]=0.0f;break;
		case 7:rms.buffer[7]=sqrtf(rms_sum.buffer[7]*inverse_avg_sample);rms_sum.buffer[7]=0.0f;break;
		case 8:rms.buffer[8]=sqrtf(rms_sum.buffer[8]*inverse_avg_sample);rms_sum.buffer[8]=0.0f;break;
		
		default: break;
	}
	
	
	
	if(counter++>=periodSampleNo*numberOfPeriod){counter=0;}

	return rms;
}

//def second order section filter implementations 
//1 	coeff is sequenced sos coefficents suxh --> b1,b2,b3,a2,a3 order
//2.0 function invocation shown below  
//2.1 "output=sos_implementation(input(real-time),output(lef-side),coeff_data(array_name),SOS2data(different for all parameters ));

float sos_implementation(float x,float xBack, float *coeffs, struct SOS *back){

	float y;
	float *coeff;
	
	coeff=coeffs;
	
	y=x*(*coeff)	+	xBack*(*coeff++)					+	(back->xz2)*(*coeff++)
								- (back->yz1)*(*coeff++)		+	(back->yz2)*(*coeff++);

	back->yz2=back->yz1;
	back->yz1=y;
	back->xz2=xBack;
	
	return y;
}


//inphase and quadrature  parameters derivation part

void iq_generation( union uAdcData input,union uAdcData *iq,float *iq_coeffs,struct SOS *all){

	uint8_t i;
	
	
	for (i=0;i<9;i++){
	
		iq->buffer[i]		=sos_implementation(input.buffer[i],iq->buffer[i],iq_coeffs,&all[i]);
		
	}
	
	
}


