
#include "menu_definitions.h"
#include "configDataHandling.h"

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
		
		configDataError=(flashNew.data.vt_primer>0 && flashNew.data.vt_primer<VT_limit_primer_limit)					?0:1;
		configDataError=(flashNew.data.vt_primer>0 && flashNew.data.vt_seconder<VT_limit_primer_limit)				?0:1;
		
		configDataError=(flashNew.data.ct_primer>0 &&flashNew.data.ct_primer<CT_limit_primer_limit)						?0:1;
		configDataError=(flashNew.data.ct_seconder>0 && flashNew.data.ct_seconder<CT_limit_seconder_limit)		?0:1;
	
		configDataError=(flashNew.data.ct_phase_shift<phase_shift_limit)																			?0:1;
		
		configDataError=(flashNew.data.outputPulsePeriod>0 && flashNew.data.outputPulsePeriod<pulse_period_limit)		?0:1;
		configDataError=(flashNew.data.outputPulseIncFactor>0 && flashNew.data.outputPulseIncFactor>0 && flashNew.data.outputPulseIncFactor<inc_factor_limit)?0:1;
		
		configDataError=(flashNew.data.outputPulseIncFactor>0 && flashNew.data.modbusAddress<adress_limit)							?0:1;
		
		configDataError=(flashNew.data.configBit.output_option!=0)							?0:1;
		configDataError=(flashNew.data.configBit.output_energy_pulse_source<output_energy_pulse_source_limit)							?0:1;
		
		configDataError=(flashNew.data.configBit.commBaudRate<comm_baud_rate_limit)																				?0:1;
		configDataError=(flashNew.data.configBit.commMode<commMode_limit)																									?0:1;
		
	}
	
	
	if(configDataError){
		
	configDataCheck=0;
		
	flash=flashNew;
	save_lock=1;	
	currentSaveMenu=saving_menu;	

		
	//comm initialization req
		
		
	if(	flashNew.data.configBit.commBaudRate!=flash.data.configBit.commBaudRate ||
			flashNew.data.configBit.commMode!=flash.data.configBit.commMode )	{
				
			__disable_irq();	
		
			MX_USART3_UART_Init();
				
			__enable_irq();		
	}
	
	}
	
	
}