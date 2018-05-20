
#ifndef __prefilter_H
#define __prefilter_H

// hpf @ 0.5Hz for offset removal

#define b_oc 0.999842945036165f
#define a_oc 0.999685890072330f


struct offset_cancellation_filter_parameters{

	float xz;
	float yz;
	
	
};

extern struct offset_cancellation_filter_parameters oc_buff[6];
float offset_cancellation(float rtInput, struct offset_cancellation_filter_parameters *buf);


#endif