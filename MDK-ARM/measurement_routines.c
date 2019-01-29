
#include "conversion.h"
#include "measurement_definitions.h"
#include "graphing_definitions.h"

/*measuremnt parameters declarations*/



struct SOS quad_sos[6]={0}; 		// for inphase parameters
struct SOS inphase_sos[6]={0}; 	// for inphase parameters

union symmetricalComponents sym;

struct spectra harm[6]={0}; 				// spectral analysis
union thdData thd={0};


union uAdcData  inphaseData={0};
union uAdcData  quadData={0};
union uAdcData  fundRMS={0};
union uAdcData  trueRMS={0};
union uAdcData  phase={0};

union powerParameters  power_iq={0};
union powerParameters  power_true={0};



struct energyParameters energy={0};
struct energyParameters energyZero={0};

void measurement_routines(){
	

	//true RMS
	
	trueRMS=true_RMS(AN,10); //cau 1 can be externalized
	
	//iq components fund calculations
	
	iq_generation(AN_pc,&inphaseData	,inphase_coeffs,inphase_sos);
	iq_generation(AN_pc,&quadData		  ,quad_coeffs,quad_sos);
	
	//fund rms
	
	fund_RMS(inphaseData,quadData,&fundRMS);
	
	//fundamental power calculations
	
	power_calculations_iq(inphaseData,quadData,&power_iq);

	//power elements true calcualtions-----omitted
	
	//power_calculations_true(AN,trueRMS,&power_true);
	
	
	//energy calculations
	
	energy_calculations(power_iq,&energy );
	
	//symmetrical components
	
	symmetrical_components(inphaseData,quadData, &sym);
	
	//phase detection
	
	phaseDetect(inphaseData,quadData,&phase);
	
	//scope routines
	
	scope_routine();
	
	//harmonics rouutines
	
	harmonics_routine();
	

	
	
}


