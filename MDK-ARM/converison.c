
#include "stm32f3xx_hal.h"
#include "sdadc.h"

uint32_t sd_adc_values[3]={0};
uint32_t sd_channel[3]={4};
uint8_t calibration_completed=0;

void HAL_SDADC_InjectedConvCpltCallback(SDADC_HandleTypeDef* hsdadc){
	
	
	if(hsdadc->Instance==SDADC1){ sd_adc_values[0]=HAL_SDADC_InjectedGetValue(&hsdadc1,&sd_channel[0]);}
	if(hsdadc->Instance==SDADC2){ sd_adc_values[1]=HAL_SDADC_InjectedGetValue(&hsdadc2,&sd_channel[1]);}
	if(hsdadc->Instance==SDADC3){ sd_adc_values[2]=HAL_SDADC_InjectedGetValue(&hsdadc3,&sd_channel[2]);}
	
	
}



void HAL_SDADC_CalibrationCpltCallback(SDADC_HandleTypeDef* hsdadc){
	
	
	if(hsdadc->Instance ==SDADC1){
		
	calibration_completed=1;
	
	}
	
}



