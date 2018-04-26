
#include "stm32f3xx_hal.h"
#include "sdadc.h"
#include "adc.h"
#include "stm32f3xx_hal_adc_ex.h"
#include "tim.h"
#include "conversion.h"
#include "prefilter.h"


struct calibrationFlags calFlags	={0};
union  uConversionFlags 	convFlags	={0};
union  uAdcData rawAdc	={0};
union  uAdcData AN			={0};

uint32_t  uBuffer[6];





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
	HAL_ADC_Start_DMA(&hadc1,&uBuffer[3],3);
	
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
	
	uBuffer[0]=HAL_SDADC_InjectedGetValue(&hsdadc1,&sd_channel);
	convFlags.bit.sd_adc1_completed=1;}
	
	
	if(hsdadc->Instance==SDADC2){ 
	
	uBuffer[1]=HAL_SDADC_InjectedGetValue(&hsdadc2,&sd_channel);
	convFlags.bit.sd_adc2_completed=1;}

	if(hsdadc->Instance==SDADC3){ 
	
	uBuffer[2]=HAL_SDADC_InjectedGetValue(&hsdadc3,&sd_channel);
	convFlags.bit.sd_adc3_completed=1;
	}
	
	
	
	
}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	
	convFlags.bit.sar_adc_completed=1;
	
	
	if(convFlags.all==0x0F){
	
	
	convFlags.all =0;	
		
	HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
		
		
	AN.data.Van=offset_cancellation((uBuffer[3]-	sar_adc_offset),&oc_buff[0]);
	AN.data.Vbn=(uBuffer[4]-	sar_adc_offset);	
	AN.data.Vcn=(uBuffer[5]-	sar_adc_offset);

	AN.data.Ib=(uBuffer[0]+	sd_adc_offset)*3.0f/(65536.0f);
	AN.data.Ia=(uBuffer[1]+	sd_adc_offset)*3.0f/(65536.0f);
	AN.data.Ic=(uBuffer[2]+	sd_adc_offset)*3.0f/(65536.0f);
		
		
	AN.data.Vab=AN.data.Van-AN.data.Vbn;
	AN.data.Vbc=AN.data.Vbn-AN.data.Vcn;	
	AN.data.Vca=AN.data.Vcn-AN.data.Van;
			
		
	}
	
}












