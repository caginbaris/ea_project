#ifndef __record_H__
#define __record_H__

#include "conversion.h"
#include "measurement_Definitions.h"

union recorded_data{

struct{
	
union uAdcData tRMS;
union uAdcData fRMS;

}data;


float all[18];



};


void recordEmAll(void);







#endif


