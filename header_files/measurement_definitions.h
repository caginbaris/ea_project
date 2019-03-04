#ifndef __measurement_definitions_H
#define __measurement_definitions_H

#include <stdint.h>

#define fs 					10000
#define period 			fs/50
#define _10period 	period*10
#define _i10period 	1/_10period

#define sqrt2 1.4142135623730950488016887242097f
#define i2 0.5f
#define indefinite 0
#define iq_rms_scale 0.5f
#define sym_r  			-0.5f
#define sym_i  			0.8660254037844386f
#define sym_i3 			0.333333333333333f

#define fftLength 50

#define energy_constant 0.00000002777777f
#define inc_resolution 0.1f
#define inverse_inc_resolution (1.0f/inc_resolution)

#define fundSample 200.0f
#define inverse_fundSample (1.0f/fundSample)




struct SOS{
	
	float xz2;
	float xz1;
	//float yz1;
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
		
		float ratioA;
		float ratioB;
		float ratioC;
		float ratioTotal;
		
		
	
	}Power;
	
	
	float buffer[20];
	


};


struct energyParameters{



		
		float active_import_a;
		float active_import_b;
		float active_import_c;
		float active_import_total;

		float active_export_a;
		float active_export_b;
		float active_export_c;
		float active_export_total;
		
		float reactive_import_a;
		float reactive_import_b;
		float reactive_import_c;
		float reactive_import_total;
		
		float reactive_export_a;
		float reactive_export_b;
		float reactive_export_c;
		float reactive_export_total;
		
		float apparent_energy_a;
		float apparent_energy_b;
		float apparent_energy_c;
		float apparent_energy_total;
		
		//scaled values
		
		float active_import_a_scaled;
		float active_import_b_scaled;
		float active_import_c_scaled;
		float active_import_total_scaled;

		float active_export_a_scaled;
		float active_export_b_scaled;
		float active_export_c_scaled;
		float active_export_total_scaled;
		
		float reactive_import_a_scaled;
		float reactive_import_b_scaled;
		float reactive_import_c_scaled;
		float reactive_import_total_scaled;
		
		float reactive_export_a_scaled;
		float reactive_export_b_scaled;
		float reactive_export_c_scaled;
		float reactive_export_total_scaled;
		
		float apparent_energy_a_scaled;
		float apparent_energy_b_scaled;
		float apparent_energy_c_scaled;
		float apparent_energy_total_scaled;
		
		
		uint32_t active_import_counter_a;
		uint32_t active_export_counter_a;
		uint32_t reactive_import_counter_a;
		uint32_t reactive_export_counter_a;
		uint32_t apparent_counter_a;
		
		uint32_t active_import_counter_b;
		uint32_t active_export_counter_b;
		uint32_t reactive_import_counter_b;
		uint32_t reactive_export_counter_b;
		uint32_t apparent_counter_b;
		
		uint32_t active_import_counter_c;
		uint32_t active_export_counter_c;
		uint32_t reactive_import_counter_c;
		uint32_t reactive_export_counter_c;
		uint32_t apparent_counter_c;
		
		uint32_t active_import_counter_total;
		uint32_t active_export_counter_total;
		uint32_t reactive_import_counter_total;
		uint32_t reactive_export_counter_total;
		uint32_t apparent_counter_total;
		
		



};

struct scaled_energy_parameters{

		
		float active_import_a;
		float active_import_b;
		float active_import_c;
		float active_import_total;

		float active_export_a;
		float active_export_b;
		float active_export_c;
		float active_export_total;
		
		float reactive_import_a;
		float reactive_import_b;
		float reactive_import_c;
		float reactive_import_total;
		
		float reactive_export_a;
		float reactive_export_b;
		float reactive_export_c;
		float reactive_export_total;
		
		float apparent_energy_a;
		float apparent_energy_b;
		float apparent_energy_c;
		float apparent_energy_total;
	

};

extern struct scaled_energy_parameters energy_scaled;






union symmetricalComponents{

	struct{
		
	float Vpn_1;
	float Vpn_2;
	float Vpn_0;	
	
	float I_1;
	float I_2;
	float I_0;
		
	float UNB_V;
	float UNB_I;			
	
}data;
	
	
	float buffer[8];
		
	
};




struct spectra {

	float qBuffer[50];
	float foutReal[20];
	float foutImag[20];
	float foutMag[20];

};

union thdData{

	struct{
		
	float Van;
	float Vbn;
	float Vcn;	
	
	float Ia;
	float Ib;
	float Ic;
	
}data;
	
	
	float buffer[6];
		
	
};


struct sensorRatios{

	float VT;
	float CT;
	float PT;

};

extern struct sensorRatios TR;



// functions prototypes

union uAdcData true_RMS(union uAdcData input,uint8_t numberOfPeriod);
void iq_generation( union uAdcData input,union uAdcData *iq,float *iq_coeffs,struct SOS *all);
void power_calculations_iq(union uAdcData inphase,union uAdcData quad, union powerParameters *x,union uAdcData tRMS);
void energy_calculations(union powerParameters x,struct energyParameters *y );
void energy_scaling(struct energyParameters x,struct scaled_energy_parameters *y );
void fund_RMS(union uAdcData inphase,union uAdcData quad,union uAdcData *rms);
void symmetrical_components(union uAdcData inphase,union uAdcData quad, union symmetricalComponents *x);
void phaseDetect(union uAdcData inphase,union uAdcData quad,union uAdcData *phase);
void harmonics_routine(void);
float pfilter(float rtInput, float yback,float* xback);
void  waveformSnap(void);


// extern data
extern float inphase_coeffs[];
extern float quad_coeffs[];
extern union uAdcData  fundRMS,fundRMS_scaled;
extern union uAdcData  trueRMS,trueRMS_scaled;
extern union powerParameters  power_iq;
extern union powerParameters  power_scaled;
extern struct energyParameters  energy;
extern union symmetricalComponents sym;
extern union uAdcData  phase;
extern const float coeffs_real[];
extern const float coeffs_imag[];
extern struct spectra  harm[6]; 					// spectral analysis
extern union thdData thd;

#endif




