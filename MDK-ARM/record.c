#include "record.h"
#include "ios.h"
#include "menu_definitions.h"

extern uint8_t save_lock;
extern uint8_t currentSaveMenu;
union recorded_data rec={0};



void recordEmAll(){

if(
	
	flash.data.configBit.input_record_start_EN==1 &&
	flash.data.configBit.input_record_start_edge==0 &&
	input.bit.risingEdgeDetected==1){
	
	rec.data.fRMS=fundRMS;
	rec.data.tRMS=trueRMS;
	
	//save_lock=1;
	//currentSaveMenu=saving_menu;
	

}


if(
	
	flash.data.configBit.input_record_start_EN==1 &&
	flash.data.configBit.input_record_start_edge==1 && 
	input.bit.fallingEdgeDetected==1){
	
	rec.data.fRMS=fundRMS;
	rec.data.tRMS=trueRMS;
	
	//save_lock=1;
	//currentSaveMenu=saving_menu;

}

}











