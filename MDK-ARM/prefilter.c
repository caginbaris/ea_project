

#include "prefilter.h"






struct offset_cancellation_filter_parameters oc_buff[6]={0};


float offset_cancellation(float rtInput, struct offset_cancellation_filter_parameters *buf)
{
	float y;
	
	y=b_oc*(rtInput-(buf->xz))+a_oc*(buf->yz);
		
	buf->yz=y;
	buf->xz=rtInput;
	
	return y;
	
};

//cau check for filter cutoff for offset cancellation