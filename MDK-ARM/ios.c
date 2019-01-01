
#include "stm32f3xx_hal.h"
#include "main.h"
#include "aux_functions.h"
#include "ios.h"

#define holdTime 50 // 5ms in uberloop 

	volatile int dmy=0;

static uint32_t counter[5]={0};
static uint8_t  inputBack[2]={0};
static uint8_t  meta[2]={0};

union boardInput input={0};

void inputHandling(){
	

	
	input.bit.raw										=HAL_GPIO_ReadPin(RELAY_INPUT_GPIO_Port,RELAY_INPUT_Pin);
	
	input.bit.onDelayed							=on_delay(input.bit.raw,input.bit.onDelayed,holdTime,&counter[0]);
	input.bit.offDelayed						=off_delay(input.bit.raw,input.bit.offDelayed,holdTime,&counter[1]);
	input.bit.on_offDelayed					=on_off_delay(input.bit.raw,input.bit.on_offDelayed,holdTime,&counter[2]);
	
	input.bit.risingEdgeDetected		=risingEdgeDetectionWithOnDelay		(input.bit.raw,&inputBack[0],&meta[0],holdTime,&counter[3]);
	input.bit.fallingEdgeDetected		=fallingEdgeDetectionWithOffDelay	(input.bit.raw,&inputBack[1],&meta[1],holdTime,&counter[4]);
	
	


	
}


void outputHandling(){



}


void ios(){

	inputHandling();
	outputHandling();


}