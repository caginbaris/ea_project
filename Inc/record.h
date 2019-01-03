#ifndef __record_H__
#define __record_H__

#include "conversion.h"
#include "measurement_Definitions.h"


#define recWordSize 46
#define recByteSize recWordSize*4

union recorded_data{

struct{
	
union uAdcData 							tRMS;
union uAdcData 							fRMS;
union powerParameters 			power_iq;
union symmetricalComponents sym;	
}data;


float word[recWordSize];
float byte[recByteSize];


};

extern union recorded_data rec;
extern uint8_t recordFlag;

void recordEmAll(void);







#endif


