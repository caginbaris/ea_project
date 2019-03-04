#include "menu_definitions.h"
#include "measurement_definitions.h"
#include "flashUpdate.h"
#include "phaseCompensation.h"



uint16_t baud=19200;



void flashUpdate(void){
	
	TR.VT=(flash.data.vt_seconder!=0)?(flash.data.vt_primer/flash.data.vt_seconder):(TR.VT);
	TR.CT=(flash.data.ct_seconder!=0)?(flash.data.ct_primer/flash.data.ct_seconder):(TR.CT);
	TR.PT=TR.VT*TR.CT;
	
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


