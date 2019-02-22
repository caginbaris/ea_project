#include "exceptions.h"
#include "aux_functions.h"
#include "conversion.h"
#include "measurement_definitions.h"

union exception_defs exception={0};
static uint32_t exception_counters[8]={0};


void exceptions(void){
	
	exception.bit.Va_highLevel=on_off_delay(trueRMS.data.Van>voltageHighLimit,exception.bit.Va_highLevel,fs,&exception_counters[0]);
	exception.bit.Vb_highLevel=on_off_delay(trueRMS.data.Vbn>voltageHighLimit,exception.bit.Vb_highLevel,fs,&exception_counters[1]);
	exception.bit.Vc_highLevel=on_off_delay(trueRMS.data.Vcn>voltageHighLimit,exception.bit.Vc_highLevel,fs,&exception_counters[2]);
	
	exception.bit.Ia_highLevel=on_off_delay(trueRMS.data.Van>currentHighLimit,exception.bit.Ia_highLevel,fs,&exception_counters[3]);
	exception.bit.Ib_highLevel=on_off_delay(trueRMS.data.Vbn>currentHighLimit,exception.bit.Ib_highLevel,fs,&exception_counters[4]);
	exception.bit.Ic_highLevel=on_off_delay(trueRMS.data.Vcn>currentHighLimit,exception.bit.Ic_highLevel,fs,&exception_counters[5]);
	
	if(exception.all!=0){
	
	
	}


}
