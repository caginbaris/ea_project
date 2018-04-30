
#include "conversion.h"
#include "measurement_definitions.h"

/*measuremnt parameters declarations*/



struct SOS quad_sos[6]; 		// for inphase parameters
struct SOS inphase_sos[6]; 	// for inphase parameters


union uAdcData  inphaseData;
union uAdcData  quadData;
union uAdcData  fundRMS;

union powerParameters  power;

void measurement_routines(){
	

	
	//cau true rms part skipped at first
	
	//iq components
	
	iq_generation(AN,&inphaseData	,inphase_coeffs,quad_sos);
	iq_generation(AN,&quadData		,inphase_coeffs,inphase_sos);
	
	//fund rms
	
	fund_RMS(inphaseData,quadData,&fundRMS);
	
	//power elements
	
	power_calculations(inphaseData,quadData,&power);
	
	
}