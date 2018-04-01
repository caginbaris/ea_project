
#define b_oc 0.999685939389360f
#define a_oc 0.999371878778719f


struct offset_cancellation__filter_parameters{

	float xz;
	float yz;
	
	
};

struct offset_cancellation__filter_parameters offsetCancel[6]={0};


float offset_cancellation(float rtInput, struct offset_cancellation__filter_parameters *buf)
{
	float y;
	
	y=b_oc*(rtInput-(buf->xz))+a_oc*(buf->yz);
		
	buf->yz=y;
	buf->xz=rtInput;
	
	return y;
	
};

//cau check for filter cutoff for offset cancellation