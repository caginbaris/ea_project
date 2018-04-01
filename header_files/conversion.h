#ifndef __conversion_H
#define __conversion_H

#include <stdint.h>

#define sd_adc_offset 32767.0f
#define sar_adc_offset 0.0f

struct calibrationFlags{
	
	uint16_t sd_adc1_calibrated:1;
	uint16_t sd_adc2_calibrated:1;
	uint16_t sd_adc3_calibrated:1;
	
	uint16_t calibration_completed:1;
	


};


struct conversionFlags{
	
	
	uint8_t sar_adc_completed:1;
	uint8_t sd_adc1_completed:1;
	uint8_t sd_adc2_completed:1;
	uint8_t sd_adc3_completed:1;
	
	

};

union uConversionFlags{

	struct conversionFlags bit;
	uint8_t  all;

};


struct adcData{
	
	float Van;
	float Vbn;
	float Vcn;
	
	float Ia;
	float Ib;
	float Ic;
	
};

union uAdcData{
	
	struct adcData data;
	float  buffer[6];
	
};

extern struct calibrationFlags calFlags;
extern union  uConversionFlags convFlags;
extern union  uAdcData rawAdc;
extern union  uAdcData AN;





#endif


