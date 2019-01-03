#include "aux_functions.h"


uint8_t on_delay(uint8_t input, uint8_t mem, uint32_t qual_sample, uint32_t *count){

	uint8_t out;

	out = mem;

	if (input == 1 && mem == 0)
	{
		*count = *count + 1;

		if ((*count) == qual_sample)
		{
			out = 1;
			*count = 0;
		}

	}

	else
	{
		*count = 0;
	}

	if (input == 0)
	{
		out = 0;
		*count = 0;
	}

	return out;

}



uint8_t off_delay(uint8_t input, uint8_t mem, uint32_t qual_sample, uint32_t *count){

	uint8_t out;

	out = mem;

	if (input == 0 && mem == 1)
	{
		*count = *count + 1;

		if ((*count) == qual_sample)
		{
			out = 0;
			*count = 0;
		}

	}

	else
	{
		*count = 0;
	}

	if (input == 1)
	{
		out = 1;
		*count = 0;
	}

	return out;

}



uint8_t on_off_delay( uint8_t input,  uint8_t mem, uint32_t qual_sample, uint32_t *count){

	uint8_t out;

	out = mem;

	if (input ^ mem)
	{
		*count = *count + 1;

		if ((*count) == qual_sample)
		{
			out = input;
			*count = 0;
		}

	}

	else
	{
		*count = 0;
	}

	return out;

}



uint8_t risingEdgeDetection(uint8_t input, uint8_t* inputBack){
	
	uint8_t output=0;


	output=0;

	if(input==1 && *inputBack==0){
	
		output=1;

	}

	*inputBack=input;

	return output;


}


uint8_t fallingEdgeDetection(uint8_t input, uint8_t* inputBack){
	
	uint8_t output=0;


	output=0;

	if(input==0 && *inputBack==1){
	
		output=1;

	}

	*inputBack=input;

	return output;


}


uint8_t risingEdgeDetectionWithOnDelay(uint8_t input, uint8_t* inputBack,uint8_t* meta, uint32_t qual_sample, uint32_t *count){

uint8_t out;

*meta=on_delay(input, *meta, qual_sample,count);
out=risingEdgeDetection(*meta,inputBack);

return out;	


}

uint8_t fallingEdgeDetectionWithOffDelay(uint8_t input, uint8_t* inputBack,uint8_t* meta, uint32_t qual_sample, uint32_t *count){

uint8_t out;

*meta=off_delay(input, *meta, qual_sample,count);
out=fallingEdgeDetection(*meta,inputBack);

return out;	


}


uint8_t pulseGeneration(uint32_t  period, uint32_t duty, uint32_t *EN,uint32_t *prdCount){

static uint8_t out=0,latch=0;

if((*EN)!=0 && latch==0){out=1;latch=1;*EN-=1;}

if(latch==1){*prdCount+=1;}

if((*prdCount)>duty && (*prdCount)<period){out=0;}

if((*prdCount)==period){latch=0;*prdCount=0;}


return out;

}


void i_limiter(int8_t down_limit,int8_t up_limit,int8_t *value ){
	
	if(*value>up_limit)		{*value	=	 up_limit;}
	if(*value<down_limit)	{*value	=down_limit;}

}

void ui_limiter(uint8_t down_limit,uint8_t up_limit,uint8_t *value ){
	
	if(*value>up_limit)		{*value	=	 up_limit;}
	if(*value<down_limit)	{*value	=down_limit;}

}


