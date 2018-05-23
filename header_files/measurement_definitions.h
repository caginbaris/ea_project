#ifndef __measurement_definitions_H
#define __measurement_definitions_H

#include <stdint.h>

#define fs 					10000
#define period 			fs/50
#define _10period 	period*10
#define _i10period 	1/_10period

#define i2 0.5f
#define indefinite 0
#define iq_rms_scale 0.5f

union RMS{
	
	struct{

	float Vpn_true_a,Vpn_true_b,Vpn_true_c;
	float Vpn_fund_a,Vpn_fund_b,Vpn_fund_c;

	float Vpp_true_a,Vpp_true_b,Vpp_true_c;
	float Vpp_fund_a,Vpp_fund_b,Vpp_fund_c;

	float Ip_true_a,Ip_true_b,Ip_true_c;
	float Ip_fund_a,Ip_fund_b,Ip_fund_c;

	}AN;
	
	float all[18];
	
};

extern union RMS rms;


struct SOS{
	
	float xz2;
	float xz1;
	float yz1;
	float yz2;		
	
	
};




union powerParameters{
	
	struct{
	
		float Pa;
		float Pb;
		float Pc;
			
		float Qa;
		float Qb;		
		float Qc;
		
		float Sa;
		float Sb;
		float Sc;
		
		float Ptotal;
		float Qtotal;
		float Stotal;
		
		float PFa;
		float PFb;
		float PFc;
		float PFtotal;
		

	
	}Power;
	
	
	float buffer[16];
	


};






// functions prototypes

union uAdcData true_RMS(union uAdcData input,uint8_t numberOfPeriod);
void iq_generation( union uAdcData input,union uAdcData *iq,const float *iq_coeffs,struct SOS *all);
void power_calculations_iq(union uAdcData inphase,union uAdcData quad, 	union powerParameters *x );
void power_calculations_true(union uAdcData AN,		union uAdcData rms, 	union powerParameters *x);
void fund_RMS(union uAdcData inphase,union uAdcData quad,union uAdcData *rms);


// extern data
extern const float inphase_coeffs[];
extern const float quad_coeffs[];
extern union uAdcData  fundRMS;
extern union uAdcData  trueRMS;
extern union powerParameters  power_iq;
extern union powerParameters  power_true;
#endif