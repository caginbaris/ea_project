#include "aux_functions.h"


uint8_t on_delay(uint8_t input, uint8_t mem, uint16_t qual_sample, uint32_t *count)
{

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



uint8_t off_delay(uint8_t input, uint8_t mem, uint16_t qual_sample, uint32_t *count)
{

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



uint8_t on_off_delay( uint8_t input,  uint8_t mem, uint16_t qual_sample, uint32_t *count)
{

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


void i_limiter(int8_t down_limit,int8_t up_limit,int8_t *value ){
	
	if(*value>up_limit)		{*value	=	 up_limit;}
	if(*value<down_limit)	{*value	=down_limit;}

}



