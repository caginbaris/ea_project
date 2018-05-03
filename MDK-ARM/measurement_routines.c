
#include "conversion.h"
#include "measurement_definitions.h"

/*measuremnt parameters declarations*/



struct SOS quad_sos[6]; 		// for inphase parameters
struct SOS inphase_sos[6]; 	// for inphase parameters


union uAdcData  inphaseData;
union uAdcData  quadData;
union uAdcData  fundRMS;
union uAdcData  trueRMS;

union powerParameters  power_iq;
union powerParameters  power_true;

void measurement_routines(){
	

	//true RMS
	
	trueRMS=true_RMS(AN,1);
	
	//fund rms
	
	fund_RMS(inphaseData,quadData,&fundRMS);
	
	//iq components fund calculations
	
	iq_generation(AN,&inphaseData	,inphase_coeffs,quad_sos);
	iq_generation(AN,&quadData		,inphase_coeffs,inphase_sos);
	power_calculations_iq(inphaseData,quadData,&power_iq);

	//power elements true calcualtions
	
	power_calculations_true(AN,trueRMS,&power_true);
	
}