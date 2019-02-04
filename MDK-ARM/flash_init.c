#include "menu_definitions.h"
#include "phaseCompensation.h"
#include "conversion.h"
#include "flashUpdate.h"


struct flashUpdateParameters flashOption;

void flashUpdate(void){
	
	
	flashOption.TR_VT=(flash.data.vt_seconder>0)?(flash.data.vt_primer/flash.data.ct_seconder):1;
	flashOption.TR_CT=(flash.data.ct_seconder>0)?(flash.data.ct_primer/flash.data.ct_seconder):1;
	pLagDef(flash.data.ct_phase_shift,10000,&pc_b12,&pc_b22); // applied to voltage
		



}