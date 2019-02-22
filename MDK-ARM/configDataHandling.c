
#include "menu_definitions.h"

extern uint8_t save_lock;
extern uint8_t currentSaveMenu;

uint8_t configDataReception=0;
uint8_t configDataCheck=0;

void configDataHandling(void){

	uint8_t i;
	uint8_t configDataError=0;

if(configDataReception){
	 
	configDataReception=0;
	
	for(i=0;i<9;i++){
		
		if(flash.uBuffer[i]!=flashNew.uBuffer[i]){
		
		configDataCheck=1;break;
		
			}
		}
	}

	
	if(configDataCheck){
	configDataCheck=0;
		
		configDataError=(flashNew.data.vt_primer>0   && flashNew.data.vt_primer<250000)									?0:1;
		configDataError=(flashNew.data.vt_seconder>0 && flashNew.data.vt_primer<500)										?0:1;
		
		configDataError=(flashNew.data.ct_primer>0   && flashNew.data.ct_primer<250000)									?0:1;
		configDataError=(flashNew.data.ct_seconder>0 && flashNew.data.ct_primer<6)											?0:1;
	
		configDataError=(flashNew.data.ct_phase_shift>0 	 && flashNew.data.ct_phase_shift<19)					?0:1;
		
		configDataError=(flashNew.data.outputPulsePeriod>0 && flashNew.data.outputPulsePeriod<19)				?0:1;
		configDataError=(flashNew.data.outputPulseIncFactor>0 && flashNew.data.outputPulseIncFactor<101)?0:1;
		
		configDataError=(flashNew.data.modbusAddress>0 && flashNew.data.modbusAddress<256)							?0:1;
		
		configDataError=(flashNew.data.configBit.output_option!=0)																			?0:1;
		configDataError=(flashNew.data.configBit.output_energy_pulse_source<7)													?0:1;
		
		configDataError=(flashNew.data.configBit.commBaudRate<7)																				?0:1;
		configDataError=(flashNew.data.configBit.commMode<4)																						?0:1;
		
	}
	
	
	if(configDataCheck){
		
	configDataCheck=0;
		
	flash=flashNew;
	currentSaveMenu=save_option_menu;	
	//cau menu redirect required	
	
	
	}
	
	
}