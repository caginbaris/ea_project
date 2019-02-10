

#include "prefilter.h"


// hpf @ 0.5Hz for offset removal

float b_oc=0.999842945036165;
float a_oc=0.999685890072330;



struct offset_cancellation_filter_parameters oc_buff[6]={0};


float offset_cancellation(float rtInput, struct offset_cancellation_filter_parameters *buf)
{
	float y;
	
	y=b_oc*(rtInput-(buf->xz))+a_oc*(buf->yz);
		
	buf->yz=y;
	buf->xz=rtInput;
	
	return y;
	
};



//check for filter cutoff for offset cancellation

