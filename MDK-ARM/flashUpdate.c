#include "menu_definitions.h"
#include "flashUpdate.h"
#include "phaseCompensation.h"

float VT=1.0f;
float CT=1.0f;

//cau ouput pulse interval

uint16_t baudRate=19200;



void flashUpdate(void){
	
	VT=(flash.data.vt_seconder!=0)?(flash.data.vt_primer/flash.data.vt_seconder):(VT);
	CT=(flash.data.ct_seconder!=0)?(flash.data.ct_primer/flash.data.ct_seconder):(CT);
	
	switch(flash.data.configBit.commBaudRate){
	
		case 0:baud=4800;break;
		case 1:baud=9600;break;
		case 2:baud=19200;break;
		case 3:baud=38400;break;
		case 4:baud=57600;break;
		
		default:baud=19200;break;
	}
	
	pLagDef(flash.data.ct_phase_shift*0.1,10000,&pc_b12,&pc_b22); // applied to voltage 		
	
}


