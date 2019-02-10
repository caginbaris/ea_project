
#ifndef __prefilter_H
#define __prefilter_H




struct offset_cancellation_filter_parameters{

	float xz;
	float yz;
	
	
};

extern struct offset_cancellation_filter_parameters oc_buff[6];
float offset_cancellation(float rtInput, struct offset_cancellation_filter_parameters *buf);


#endif



