#include "record.h"
#include "ios.h"
#include "menu_definitions.h"

extern uint8_t save_lock;
extern uint8_t currentSaveMenu;
uint8_t record_start=0;


union recorded_data rec={0};

uint8_t recordFlag=0;


void recordEmAll(){

if(
	
	flash.data.configBit.input_record_start_EN==1 &&
	flash.data.configBit.input_record_start_edge==0 &&
	input.bit.risingEdgeDetected==1){
	
	rec.data.fRMS=fundRMS;
	rec.data.tRMS=trueRMS;
	rec.data.power_iq=power_iq;
	rec.data.sym=sym;	
	
	recordFlag=1;
	

}


if(
	
	flash.data.configBit.input_record_start_EN==1 &&
	flash.data.configBit.input_record_start_edge==1 && 
	input.bit.fallingEdgeDetected==1){
	
	rec.data.fRMS=fundRMS;
	rec.data.tRMS=trueRMS;
	rec.data.power_iq=power_iq;
	rec.data.sym=sym;	
		
	recordFlag=1;	
	

}
	


	





if(record_start){
	
	record_start=0;
	
	rec.data.fRMS=fundRMS;
	rec.data.tRMS=trueRMS;
	rec.data.power_iq=power_iq;
	rec.data.sym=sym;	
		
	

}






}




