
#include "stm32f3xx_hal.h"
#include "sdadc.h"
#include "adc.h"
#include "stm32f3xx_hal_adc_ex.h"
#include "tim.h"
#include "conversion.h"
#include "prefilter.h"
#include "menu_definitions.h"
#include "phaseCompensation.h"
#include "ios.h"
#include "record.h"

struct calibrationFlags calFlags	={0};
union  uConversionFlags 	convFlags	={0};
union  uAdcData rawAdc	={0};
union  uAdcData AN			={0};
union  uAdcData AN_pc		={0};
union  uAdcData scale		={0};
enum adcChannel ch=Van;

uint32_t  uBuffer[6];

void measurement_routines();
enum input  pushButtonHandling(void);
extern enum input pressed_button;
extern uint16_t refresh_counter;

float pc_b1,pc_b2;
float pc_x1,pc_x2,pc_x3;

float pc_b12,pc_b22;
float pc_x4,pc_x5,pc_x6;

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
	
	scale.data.Van=0.1874084919472913616398243045388;//0.09660669;
	scale.data.Vbn=0.1874084919472913616398243045388;//0.09660669;
	scale.data.Vcn=0.187999994;//0.09660669;
	
	scale.data.Ia=0.000198143;
	scale.data.Ib=0.000198143;
	scale.data.Ic=0.000201500006f;
	
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
	
	uBuffer[0]=HAL_SDADC_InjectedGetValue( &hsdadc1,(uint32_t *)&sd_channel);
	convFlags.bit.sd_adc1_completed=1;}
	
	
	if(hsdadc->Instance==SDADC2){ 
	
	uBuffer[1]=HAL_SDADC_InjectedGetValue(&hsdadc2,(uint32_t *)&sd_channel);
	convFlags.bit.sd_adc2_completed=1;}

	if(hsdadc->Instance==SDADC3){ 
	
	uBuffer[2]=HAL_SDADC_InjectedGetValue(&hsdadc3,(uint32_t *) &sd_channel);
	convFlags.bit.sd_adc3_completed=1;
	}
	
	
	
	
}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	
	convFlags.bit.sar_adc_completed=1;
	
	
	if(convFlags.all==0x0F){
	
	
	convFlags.all =0;	
		
	HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
		
		
	AN.data.Van=offset_cancellation((uBuffer[3]),&oc_buff[0])*scale.data.Van;
	AN.data.Vbn=offset_cancellation((uBuffer[5]),&oc_buff[1])*scale.data.Vbn;	
	AN.data.Vcn=offset_cancellation((uBuffer[4]),&oc_buff[2])*scale.data.Vcn;

	AN.data.Ic=	offset_cancellation((int16_t)uBuffer[0]+ 32768,&oc_buff[3])	*scale.data.Ic*100.0f;//cau
	AN.data.Ia=	offset_cancellation((int16_t)uBuffer[1]+ 32768,&oc_buff[4])	*scale.data.Ia;
	AN.data.Ib=	offset_cancellation((int16_t)uBuffer[2]+ 32768,&oc_buff[5])	*scale.data.Ib;
		
		
	AN_pc.data.Van=pDiffer( AN.data.Van,pc_b1,pc_b2,&pc_x1);
	AN_pc.data.Vbn=pDiffer( AN.data.Vbn,pc_b1,pc_b2,&pc_x2);	
	AN_pc.data.Vcn=pDiffer( AN.data.Vcn,pc_b1,pc_b2,&pc_x3);

	AN_pc.data.Ic=	pDiffer( AN.data.Ic,pc_b1,pc_b2,&pc_x4)*100.0f;
	AN_pc.data.Ia=	pDiffer( AN.data.Ia,pc_b1,pc_b2,&pc_x5)*100.0f;
	AN_pc.data.Ib=	pDiffer( AN.data.Ib,pc_b1,pc_b2,&pc_x6)*100.0f;
	
			
	measurement_routines();
	ios();
	recordEmAll();
	
		
	refresh_counter++;	
	
	}
	
}












