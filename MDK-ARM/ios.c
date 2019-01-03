
#include "stm32f3xx_hal.h"
#include "main.h"
#include "aux_functions.h"
#include "ios.h"
#include "menu_definitions.h"
#include "measurement_definitions.h"

#define holdTime 50 // 5ms in uberloop 

	volatile int dmy=0;

static uint32_t counter[5]={0};
static uint8_t  inputBack[2]={0};
static uint8_t  meta[2]={0};

union boardInput input={0};
uint8_t output=0;



void inputHandling(){
	

	
	input.bit.raw										=HAL_GPIO_ReadPin(RELAY_INPUT_GPIO_Port,RELAY_INPUT_Pin);
	
	input.bit.onDelayed							=on_delay(input.bit.raw,input.bit.onDelayed,holdTime,&counter[0]);
	input.bit.offDelayed						=off_delay(input.bit.raw,input.bit.offDelayed,holdTime,&counter[1]);
	input.bit.on_offDelayed					=on_off_delay(input.bit.raw,input.bit.on_offDelayed,holdTime,&counter[2]);
	
	input.bit.risingEdgeDetected		=risingEdgeDetectionWithOnDelay		(input.bit.raw,&inputBack[0],&meta[0],holdTime,&counter[3]);
	input.bit.fallingEdgeDetected		=fallingEdgeDetectionWithOffDelay	(input.bit.raw,&inputBack[1],&meta[1],holdTime,&counter[4]);
	
	


	
}


void outputHandling(){
	
	float energySource=0;
	static float energySourceBack=0;
	static uint32_t counter=0;
	static uint32_t increment=0;
	
	if(flash.data.configBit.output_option==0){
		
		
		switch(flash.data.configBit.output_energy_pulse_source){
		
			case 1:	 energySource=energy.active_import_total_scaled;		break;
			case 2:	 energySource=energy.active_export_total_scaled;		break;
			case 3:	 energySource=energy.reactive_import_total_scaled;	break;
			case 4:	 energySource=energy.reactive_export_total_scaled;	break;
			case 5:	 energySource=energy.apparent_energy_total_scaled;	break;
			default: energySource=0;																		break;
		
		}
		
		increment+=(energySource-energySourceBack)*flash.data.outputPulseIncFactor;
		
		output=pulseGeneration(5000,2500,&increment,&counter);
		
		energySourceBack=energySource;
	
	
	}
	
	
	
	
	HAL_GPIO_WritePin(RELAY_OUTPUT_GPIO_Port,RELAY_OUTPUT_Pin,(GPIO_PinState)output);



}


void ios(){

	inputHandling();
	outputHandling();


}