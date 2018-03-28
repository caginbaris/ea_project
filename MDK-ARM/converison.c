
#include "stm32f3xx_hal.h"
#include "sdadc.h"
#include "adc.h"
#include "stm32f3xx_hal_adc_ex.h"
#include "tim.h"

uint32_t sd_adc_values[3]={0};
uint32_t adc_values[3]={0};
uint32_t sd_channel[3]={4};
uint8_t calibration_completed=0;


void init_conversion(void){

	//sdadc
	HAL_SDADC_CalibrationStart_IT(&hsdadc1,SDADC_CALIBRATION_SEQ_1);
	HAL_SDADC_CalibrationStart_IT(&hsdadc2,SDADC_CALIBRATION_SEQ_1);
	HAL_SDADC_CalibrationStart_IT(&hsdadc3,SDADC_CALIBRATION_SEQ_1);
	
	while(!calibration_completed)
	
	HAL_SDADC_InjectedStart_IT(&hsdadc1);	
	HAL_SDADC_InjectedStart_IT(&hsdadc2);
	HAL_SDADC_InjectedStart_IT(&hsdadc3);
		
	
	
	//adc

	while(HAL_ADCEx_Calibration_Start(&hadc1)!=HAL_OK);
	HAL_ADC_Start_DMA(&hadc1,adc_values,3);
	
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

void HAL_SDADC_InjectedConvCpltCallback(SDADC_HandleTypeDef* hsdadc){
	
	if(hsdadc->Instance==SDADC1){ sd_adc_values[0]=HAL_SDADC_InjectedGetValue(&hsdadc1,&sd_channel[0]);HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);}
	if(hsdadc->Instance==SDADC2){ sd_adc_values[1]=HAL_SDADC_InjectedGetValue(&hsdadc2,&sd_channel[1]);}
	if(hsdadc->Instance==SDADC3){ sd_adc_values[2]=HAL_SDADC_InjectedGetValue(&hsdadc3,&sd_channel[2]);}
	
	
}



void HAL_SDADC_CalibrationCpltCallback(SDADC_HandleTypeDef* hsdadc){
	
	static uint8_t sdadc1_calibrated=0,sdadc2_calibrated=0,sdadc3_calibrated=0;
	
	
	if(hsdadc->Instance ==SDADC1){
		
		sdadc1_calibrated=1;

	
	}
	
	
	if(hsdadc->Instance ==SDADC2){
		
		sdadc2_calibrated=1;
	
	}
	
	
	if(hsdadc->Instance ==SDADC3){
		
		
		sdadc3_calibrated=1;
		
		
		
	
	}
	
	
	if(sdadc1_calibrated==1 && sdadc2_calibrated==1 && sdadc3_calibrated==1){
		
		calibration_completed=1;
		
		//cau: error routine req. for improper calibration sequence
	
	}
	
	

	
}



