
#include "stm32f3xx_hal.h"
#include "sdadc.h"
#include "adc.h"
#include "stm32f3xx_hal_adc_ex.h"
#include "tim.h"
#include "conversion.h"



struct calibrationFlags calFlags	={0};
union  uConversionFlags 	convFlags	={0};
union  uAdcData rawAdc	={0};
union  uAdcData AN			={0};







void init_conversion(void){

	//sdadc
	
	HAL_SDADC_CalibrationStart_IT(&hsdadc1,SDADC_CALIBRATION_SEQ_1);
	HAL_SDADC_CalibrationStart_IT(&hsdadc2,SDADC_CALIBRATION_SEQ_1);
	HAL_SDADC_CalibrationStart_IT(&hsdadc3,SDADC_CALIBRATION_SEQ_1);
	
	while(!calFlags.calibration_completed)
	
	HAL_SDADC_InjectedStart_IT(&hsdadc1);	
	HAL_SDADC_InjectedStart_IT(&hsdadc2);
	HAL_SDADC_InjectedStart_IT(&hsdadc3);
		
	
	//adc

	while(HAL_ADCEx_Calibration_Start(&hadc1)!=HAL_OK);
	HAL_ADC_Start_DMA(&hadc1,&rawAdc.uBuffer[3],3);
	
	// triggers
	
	__HAL_TIM_SET_COMPARE(&htim19,TIM_CHANNEL_2,1);
	__HAL_TIM_SET_COMPARE(&htim19,TIM_CHANNEL_3,1);
	
	__HAL_TIM_CLEAR_IT(&htim19,TIM_IT_CC2);
	__HAL_TIM_ENABLE_IT(&htim19,TIM_IT_CC2);
	
	__HAL_TIM_CLEAR_IT(&htim19,TIM_IT_CC3);
	__HAL_TIM_ENABLE_IT(&htim19,TIM_IT_CC3);
	
	
	// adc start compare
	
	HAL_TIM_OC_Start_IT(&htim19,TIM_CHANNEL_3);
	HAL_TIM_OC_Start_IT(&htim19,TIM_CHANNEL_2);

}

void HAL_SDADC_CalibrationCpltCallback(SDADC_HandleTypeDef* hsdadc){
	
	
	
	
	if(hsdadc->Instance ==SDADC1){
		
		calFlags.sd_adc1_calibrated=1;

	
	}
	
	
	if(hsdadc->Instance ==SDADC2){
		
		calFlags.sd_adc2_calibrated=1;
	
	}
	
	
	if(hsdadc->Instance ==SDADC3){
		
		
		calFlags.sd_adc3_calibrated=1;
		

	}
	
	
	if(	calFlags.sd_adc1_calibrated==1 && 
			calFlags.sd_adc2_calibrated==1 && 
			calFlags.sd_adc3_calibrated==1){
		
			calFlags.calibration_completed=1;
		
		//cau: error routine req. for improper calibration sequence
	
	}
	
	

	
}




void HAL_SDADC_InjectedConvCpltCallback(SDADC_HandleTypeDef* hsdadc){
	
	uint32_t sd_channel=0;
	
	if(hsdadc->Instance==SDADC1){ 
	
	rawAdc.uBuffer[0]=HAL_SDADC_InjectedGetValue(&hsdadc1,&sd_channel);
	convFlags.bit.sd_adc1_completed=1;}
	
	
	if(hsdadc->Instance==SDADC2){ 
	
	rawAdc.uBuffer[1]=HAL_SDADC_InjectedGetValue(&hsdadc2,&sd_channel);
	convFlags.bit.sd_adc2_completed=1;}

	if(hsdadc->Instance==SDADC3){ 
	
	rawAdc.uBuffer[2]=HAL_SDADC_InjectedGetValue(&hsdadc3,&sd_channel);
	convFlags.bit.sd_adc3_completed=1;
	}
	
	
	
	
}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	
	convFlags.bit.sar_adc_completed=1;
	
	
	if(convFlags.all & 0x0F){
	
	convFlags.bit.conversion_completed=1;
	convFlags.all &= 0x10;	
	HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
		
	}
	
}












