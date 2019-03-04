

#include "conversion.h"
#include "measurement_definitions.h"
#include <math.h>
#include "arm_math.h" 
#include "graphing_definitions.h"
#include "aux_functions.h"

#define eps 1.0f

union uAdcData true_RMS(union uAdcData input,uint8_t numberOfPeriod){

	static uint16_t counter=0;
	static union uAdcData rms={0};
	static union uAdcData rms_sum={0};
	float inverse_avg_sample=1.0f;
	uint8_t i;
	
	
	inverse_avg_sample=1/(float)(periodSampleNo*numberOfPeriod);
	
	
	
	for(i=0;i<9;i++){
	
		rms_sum.buffer[i]+=input.buffer[i]*input.buffer[i];
	
	}
	
	//cau TR added, harm angle !!!! @plot data formationg
	
	switch(counter){
	
		case 0:arm_sqrt_f32(rms_sum.buffer[0]*inverse_avg_sample,&rms.buffer[0]);rms_sum.buffer[0]=0.0f;break;
		case 1:arm_sqrt_f32(rms_sum.buffer[1]*inverse_avg_sample,&rms.buffer[1]);rms_sum.buffer[1]=0.0f;break;
		case 2:arm_sqrt_f32(rms_sum.buffer[2]*inverse_avg_sample,&rms.buffer[2]);rms_sum.buffer[2]=0.0f;break;
		
		case 3:arm_sqrt_f32(rms_sum.buffer[3]*inverse_avg_sample,&rms.buffer[3]);rms_sum.buffer[3]=0.0f;break;
		case 4:arm_sqrt_f32(rms_sum.buffer[4]*inverse_avg_sample,&rms.buffer[4]);rms_sum.buffer[4]=0.0f;break;
		case 5:arm_sqrt_f32(rms_sum.buffer[5]*inverse_avg_sample,&rms.buffer[5]);rms_sum.buffer[5]=0.0f;break;
		
		case 6:arm_sqrt_f32(rms_sum.buffer[6]*inverse_avg_sample,&rms.buffer[6]);rms_sum.buffer[6]=0.0f;break;
		case 7:arm_sqrt_f32(rms_sum.buffer[7]*inverse_avg_sample,&rms.buffer[7]);rms_sum.buffer[7]=0.0f;break;
		case 8:arm_sqrt_f32(rms_sum.buffer[8]*inverse_avg_sample,&rms.buffer[8]);;rms_sum.buffer[8]=0.0f;break;
		
		
		default: break;
	}
	
	
	if(counter++>=periodSampleNo*numberOfPeriod){counter=0;}

	return rms;
}

//def second order section filter implementations 
//1 	coeff is sequenced sos coefficents suxh --> b1,b2,b3,a2,a3 order
//2.0 function invocation shown below  
//2.1 "output=sos_implementation(input(real-time),output(lef-side),coeff_data(array_name),SOS2data(different for all parameters ));

float sos_implementation(float x ,float yBack, float *coeffs, struct SOS *back){

	float y;

	
	y=x*(*coeffs)	+	(back->xz1)	*(*(coeffs+1))		+	(back->xz2)*(*(coeffs+2))
								- (yBack)			*(*(coeffs+3))		-	(back->yz2)*(*(coeffs+4));

	
	back->yz2=yBack;
	back->xz2=back->xz1;
	back->xz1=x;
	
	return y;
	
}


//inphase and quadrature  parameters derivation part

void iq_generation( union uAdcData input,union uAdcData *iq,float *iq_coeffs,struct SOS *all){

	uint8_t i;
	
	
	for (i=0;i<6;i++){
	
		iq->buffer[i]		=sos_implementation(input.buffer[i],iq->buffer[i],iq_coeffs,&all[i]);
		
	}
	
	iq->data.Vab=iq->data.Van-iq->data.Vbn;
	iq->data.Vbc=iq->data.Vbn-iq->data.Vcn;
	iq->data.Vca=iq->data.Vcn-iq->data.Van;
	
}


void fund_RMS(union uAdcData inphase,union uAdcData quad,union uAdcData *rms){
	
	
	static uint8_t i=0;
	static uint16_t j=0;
	
	union uAdcData sqrtBuffer; 
	static union uAdcData sumBuffer={0}; 
	
	arm_sqrt_f32((inphase.buffer[i]*inphase.buffer[i]+quad.buffer[i]*quad.buffer[i])*iq_rms_scale,&(sqrtBuffer.buffer[i]));
	sumBuffer.buffer[i]+=sqrtBuffer.buffer[i];
	
	i++;if(i==9){i=0;}
	j++;if(j==fundSample*9){j=0;}
	
		switch(j){
	
		case 0:rms->buffer[0]=sumBuffer.buffer[0]*inverse_fundSample;sumBuffer.buffer[0]=0.0f;break;
		case 1:rms->buffer[1]=sumBuffer.buffer[1]*inverse_fundSample;sumBuffer.buffer[1]=0.0f;break;
		case 2:rms->buffer[2]=sumBuffer.buffer[2]*inverse_fundSample;sumBuffer.buffer[2]=0.0f;break;	
		case 3:rms->buffer[3]=sumBuffer.buffer[3]*inverse_fundSample;sumBuffer.buffer[3]=0.0f;break;
		case 4:rms->buffer[4]=sumBuffer.buffer[4]*inverse_fundSample;sumBuffer.buffer[4]=0.0f;break;
		case 5:rms->buffer[5]=sumBuffer.buffer[5]*inverse_fundSample;sumBuffer.buffer[5]=0.0f;break;
		case 6:rms->buffer[6]=sumBuffer.buffer[6]*inverse_fundSample;sumBuffer.buffer[6]=0.0f;break;
		case 7:rms->buffer[7]=sumBuffer.buffer[7]*inverse_fundSample;sumBuffer.buffer[7]=0.0f;break;	
		case 8:rms->buffer[8]=sumBuffer.buffer[8]*inverse_fundSample;sumBuffer.buffer[8]=0.0f;break;
			
		default: break;
	}
	


}



float back_y=0,back_x=0;


void power_calculations_iq(union uAdcData inphase,union uAdcData quad, union powerParameters *x, union uAdcData tRMS){
	
		
	 static uint8_t counter=20;


		x->Power.Pa=(inphase.data.Van*inphase.data.Ia + quad.data.Van*quad.data.Ia)*i2;
		x->Power.Pb=(inphase.data.Vbn*inphase.data.Ib + quad.data.Vbn*quad.data.Ib)*i2;
		x->Power.Pc=pfilter((inphase.data.Vcn*inphase.data.Ic + quad.data.Vcn*quad.data.Ic)*i2,x->Power.Pc,&back_y);

		x->Power.Qa=(quad.data.Van*inphase.data.Ia - inphase.data.Van*quad.data.Ia)*i2;
		x->Power.Qb=(quad.data.Vbn*inphase.data.Ib - inphase.data.Vbn*quad.data.Ib)*i2;
		x->Power.Qc=(quad.data.Vcn*inphase.data.Ic - inphase.data.Vcn*quad.data.Ic)*i2;
	
		x->Power.Sa=tRMS.data.Van*tRMS.data.Ia;
		x->Power.Sb=tRMS.data.Vbn*tRMS.data.Ib;
		x->Power.Sc=tRMS.data.Vcn*tRMS.data.Ic;
	
	
		x->Power.Ptotal=x->Power.Pa + x->Power.Pb + x->Power.Pc;
		x->Power.Qtotal=x->Power.Qa + x->Power.Qb + x->Power.Qc;
		x->Power.Stotal=x->Power.Sa + x->Power.Sb + x->Power.Sc;

		
		counter++;
		switch(counter){
		
		case 1:x->Power.PFa 			= x->Power.Sa==0 			?  indefinite : 100.0f*x->Power.Pa/x->Power.Sa;break;
		case 2:x->Power.PFb 			= x->Power.Sb==0 			?  indefinite : 100.0f*x->Power.Pb/x->Power.Sb;break;
		case 3:x->Power.PFc 			= x->Power.Sc==0 			?  indefinite : 100.0f*x->Power.Pc/x->Power.Sc;break;
		case 4:x->Power.PFtotal 	= x->Power.Stotal==0 	?  indefinite : 100.0f*x->Power.Ptotal/x->Power.Stotal;break;
		
		
		case 5:x->Power.ratioA 			= x->Power.Pa==0 			?  indefinite : 100.0f*x->Power.Qa/x->Power.Pa;break;
		case 6:x->Power.ratioB 			= x->Power.Pb==0 			?  indefinite : 100.0f*x->Power.Qb/x->Power.Pb;break;
		case 7:x->Power.ratioC 			= x->Power.Pc==0 			?  indefinite : 100.0f*x->Power.Qc/x->Power.Pc;break;
		case 8:x->Power.ratioTotal 	= x->Power.Ptotal==0 	?  indefinite : 100.0f*x->Power.Qtotal/x->Power.Ptotal;break;
		
		case 9:counter=0;	
		
		}
		
		
}



//energy calculations

void energy_accumulator(float* acc, uint32_t* counter ){

	float increment;
	uint32_t tick;

	
	increment=(*acc)>0.0f ? (*acc):-(*acc);
	if(increment>=inc_resolution){	

	tick=(increment*inverse_inc_resolution);

	(*counter)+=tick;
		
	if(*acc>0.0f){	(*acc)    -=(tick)*inc_resolution;}else{
								(*acc)    +=(tick)*inc_resolution;
	}
	
		}
	}


void energy_calculations(union powerParameters x,struct energyParameters *y ){
	
	

	
	if(x.Power.Pa>=0.0f && x.Power.Qa>=0.0f){y->active_import_a+=x.Power.Pa*energy_constant; y->reactive_import_a+=x.Power.Qa*energy_constant;}
	if(x.Power.Pa>=0.0f && x.Power.Qa<=0.0f){y->active_import_a+=x.Power.Pa*energy_constant; y->reactive_export_a+=x.Power.Qa*energy_constant;}
	if(x.Power.Pa<=0.0f && x.Power.Qa>=0.0f){y->active_export_a+=x.Power.Pa*energy_constant; y->reactive_import_a+=x.Power.Qa*energy_constant;}
	if(x.Power.Pa<=0.0f && x.Power.Qa<=0.0f){y->active_export_a+=x.Power.Pa*energy_constant; y->reactive_export_a+=x.Power.Qa*energy_constant;}
		
		
	if(x.Power.Pb>=0.0f && x.Power.Qb>=0.0f){y->active_import_b+=x.Power.Pb*energy_constant; y->reactive_import_b+=x.Power.Qb*energy_constant;}
	if(x.Power.Pb>=0.0f && x.Power.Qb<=0.0f){y->active_import_b+=x.Power.Pb*energy_constant; y->reactive_export_b+=x.Power.Qb*energy_constant;}
	if(x.Power.Pb<=0.0f && x.Power.Qb>=0.0f){y->active_export_b+=x.Power.Pb*energy_constant; y->reactive_import_b+=x.Power.Qb*energy_constant;}
	if(x.Power.Pb<=0.0f && x.Power.Qb<=0.0f){y->active_export_b+=x.Power.Pb*energy_constant; y->reactive_export_b+=x.Power.Qb*energy_constant;}	
	
	if(x.Power.Pc>=0.0f && x.Power.Qc>=0.0f){y->active_import_c+=x.Power.Pc*energy_constant; y->reactive_import_c+=x.Power.Qc*energy_constant;}
	if(x.Power.Pc>=0.0f && x.Power.Qc<=0.0f){y->active_import_c+=x.Power.Pc*energy_constant; y->reactive_export_c+=x.Power.Qc*energy_constant;}
	if(x.Power.Pc<=0.0f && x.Power.Qc>=0.0f){y->active_export_c+=x.Power.Pc*energy_constant; y->reactive_import_c+=x.Power.Qc*energy_constant;}
	if(x.Power.Pc<=0.0f && x.Power.Qc<=0.0f){y->active_export_c+=x.Power.Pc*energy_constant; y->reactive_export_c+=x.Power.Qc*energy_constant;}	
	
	if(x.Power.Ptotal>=0.0f && x.Power.Qtotal>=0.0f){y->active_import_total+=x.Power.Ptotal*energy_constant; y->reactive_import_total+=x.Power.Qtotal*energy_constant;}
	if(x.Power.Ptotal>=0.0f && x.Power.Qtotal<=0.0f){y->active_import_total+=x.Power.Ptotal*energy_constant; y->reactive_export_total+=x.Power.Qtotal*energy_constant;}
	if(x.Power.Ptotal<=0.0f && x.Power.Qtotal>=0.0f){y->active_export_total+=x.Power.Ptotal*energy_constant; y->reactive_import_total+=x.Power.Qtotal*energy_constant;}
	if(x.Power.Ptotal<=0.0f && x.Power.Qtotal<=0.0f){y->active_export_total+=x.Power.Ptotal*energy_constant; y->reactive_export_total+=x.Power.Qtotal*energy_constant;}

		
	y->apparent_energy_a		+=x.Power.Sa*energy_constant; 
	y->apparent_energy_b		+=x.Power.Sb*energy_constant;
	y->apparent_energy_c		+=x.Power.Sc*energy_constant;
	y->apparent_energy_total+=x.Power.Stotal*energy_constant;
		
	
	energy_accumulator(&(y->active_import_a)			,&(y->active_import_counter_a));	
	energy_accumulator(&(y->active_import_b)			,&(y->active_import_counter_b));	
	energy_accumulator(&(y->active_import_c)			,&(y->active_import_counter_c));														
	energy_accumulator(&(y->active_import_total)	,&(y->active_import_counter_total));
		
	energy_accumulator(&(y->active_export_a)			,&(y->active_export_counter_a));	
	energy_accumulator(&(y->active_export_b)			,&(y->active_export_counter_b));	
	energy_accumulator(&(y->active_export_c)			,&(y->active_export_counter_c));														
	energy_accumulator(&(y->active_export_total)	,&(y->active_export_counter_total));	
	
			
	energy_accumulator(&(y->reactive_import_a)		,&(y->reactive_import_counter_a));	
	energy_accumulator(&(y->reactive_import_b)		,&(y->reactive_import_counter_b));	
	energy_accumulator(&(y->reactive_import_c)		,&(y->reactive_import_counter_c));														
	energy_accumulator(&(y->reactive_import_total),&(y->reactive_import_counter_total));
		
	energy_accumulator(&(y->reactive_export_a)		,&(y->reactive_export_counter_a));	
	energy_accumulator(&(y->reactive_export_b)		,&(y->reactive_export_counter_b));	
	energy_accumulator(&(y->reactive_export_c)		,&(y->reactive_export_counter_c));														
	energy_accumulator(&(y->reactive_export_total),&(y->reactive_export_counter_total));		

	
	
	energy_accumulator(&(y->apparent_energy_a)		,&(y->apparent_counter_a));	
	energy_accumulator(&(y->apparent_energy_b)		,&(y->apparent_counter_b));	
	energy_accumulator(&(y->apparent_energy_c)		,&(y->apparent_counter_c));	
	energy_accumulator(&(y->apparent_energy_total),&(y->apparent_counter_total));	
	
	
	
	y->active_import_a_scaled			=(y->active_import_counter_a)		*inc_resolution;
	y->active_import_b_scaled			=(y->active_import_counter_b)		*inc_resolution;
	y->active_import_c_scaled			=(y->active_import_counter_c)		*inc_resolution;
	y->active_import_total_scaled	=(y->active_import_counter_total )*inc_resolution;
	
	y->active_export_a_scaled			=(y->active_export_counter_a)		*inc_resolution;
	y->active_export_b_scaled			=(y->active_export_counter_b)		*inc_resolution;
	y->active_export_c_scaled			=(y->active_export_counter_c)		*inc_resolution;
	y->active_export_total_scaled	=(y->active_export_counter_total)*inc_resolution;
	
	y->reactive_import_a_scaled			=(y->reactive_import_counter_a)		*inc_resolution;
	y->reactive_import_b_scaled			=(y->reactive_import_counter_b)		*inc_resolution;
	y->reactive_import_c_scaled			=(y->reactive_import_counter_c)		*inc_resolution;
	y->reactive_import_total_scaled	=(y->reactive_import_counter_total)*inc_resolution;
	
	y->reactive_export_a_scaled			=(y->reactive_export_counter_a)		*inc_resolution;
	y->reactive_export_b_scaled			=(y->reactive_export_counter_b)		*inc_resolution;
	y->reactive_export_c_scaled			=(y->reactive_export_counter_c)		*inc_resolution;
	y->reactive_export_total_scaled	=(y->reactive_export_counter_total)*inc_resolution;
	
	y->apparent_energy_a_scaled			=(y->apparent_counter_a)		*inc_resolution;
	y->apparent_energy_b_scaled			=(y->apparent_counter_b)		*inc_resolution;
	y->apparent_energy_c_scaled			=(y->apparent_counter_c)		*inc_resolution;
	y->apparent_energy_total_scaled	=(y->apparent_counter_total)*inc_resolution;
	
}


void energy_scaling(struct energyParameters x,struct scaled_energy_parameters *y ){

	y->active_import_a	=	x.active_import_a_scaled*TR.PT;
	y->active_import_b	=	x.active_import_b_scaled*TR.PT;
	y->active_import_c	=	x.active_import_c_scaled*TR.PT;
	y->active_import_c	=	x.active_import_total_scaled*TR.PT;
	
	y->active_export_a	=	x.active_export_a_scaled*TR.PT;
	y->active_export_b	=	x.active_export_b_scaled*TR.PT;
	y->active_export_c	=	x.active_export_c_scaled*TR.PT;
	y->active_export_c	=	x.active_export_total_scaled*TR.PT;

	y->reactive_import_a	=	x.reactive_import_a_scaled*TR.PT;
	y->reactive_import_b	=	x.reactive_import_b_scaled*TR.PT;
	y->reactive_import_c	=	x.reactive_import_c_scaled*TR.PT;
	y->reactive_import_c	=	x.reactive_import_total_scaled*TR.PT;
	
	y->reactive_export_a	=	x.reactive_export_a_scaled*TR.PT;
	y->reactive_export_b	=	x.reactive_export_b_scaled*TR.PT;
	y->reactive_export_c	=	x.reactive_export_c_scaled*TR.PT;
	y->reactive_export_c	=	x.reactive_export_total_scaled*TR.PT;
	
	y->apparent_energy_a			=	x.apparent_energy_a_scaled*TR.PT;
	y->apparent_energy_b			=	x.apparent_energy_b_scaled*TR.PT;
	y->apparent_energy_c			=	x.apparent_energy_c_scaled*TR.PT;
	y->apparent_energy_total	=	x.apparent_energy_total_scaled*TR.PT;

}


float sumI0=0,sumI1=0,sumI2=0;	



void scaled_parameters(union uAdcData tRMS,union uAdcData fRMS,union powerParameters power,union uAdcData *tRMS_scaled,union uAdcData *fRMS_scaled,union powerParameters *power_scaled){
	
//true-----------------------------	
tRMS_scaled->data.Van=tRMS.data.Van*TR.VT;
tRMS_scaled->data.Vbn=tRMS.data.Vbn*TR.VT;
tRMS_scaled->data.Vcn=tRMS.data.Vcn*TR.VT;
	
tRMS_scaled->data.Vab=tRMS.data.Vab*TR.VT;
tRMS_scaled->data.Vbc=tRMS.data.Vbc*TR.VT;
tRMS_scaled->data.Vca=tRMS.data.Vca*TR.VT;	

tRMS_scaled->data.Ia=tRMS.data.Ia*TR.CT;
tRMS_scaled->data.Ib=tRMS.data.Ib*TR.CT;
tRMS_scaled->data.Ic=tRMS.data.Ic*TR.CT;

//fund-----------------------------
fRMS_scaled->data.Van=fRMS.data.Van*TR.VT;
fRMS_scaled->data.Vbn=fRMS.data.Vbn*TR.VT;
fRMS_scaled->data.Vcn=fRMS.data.Vcn*TR.VT;
	
fRMS_scaled->data.Vab=fRMS.data.Vab*TR.VT;
fRMS_scaled->data.Vbc=fRMS.data.Vbc*TR.VT;
fRMS_scaled->data.Vca=fRMS.data.Vca*TR.VT;	

fRMS_scaled->data.Ia=fRMS.data.Ia*TR.CT;
fRMS_scaled->data.Ib=fRMS.data.Ib*TR.CT;
fRMS_scaled->data.Ic=fRMS.data.Ic*TR.CT;		

//power-----------------------------

power_scaled->Power.Pa=power.Power.Pa*TR.PT;
power_scaled->Power.Pb=power.Power.Pb*TR.PT;
power_scaled->Power.Pc=power.Power.Pc*TR.PT;

power_scaled->Power.Qa=power.Power.Qa*TR.PT;
power_scaled->Power.Qb=power.Power.Qb*TR.PT;
power_scaled->Power.Qc=power.Power.Qc*TR.PT;

power_scaled->Power.Sa=power.Power.Sa*TR.PT;
power_scaled->Power.Sb=power.Power.Sb*TR.PT;
power_scaled->Power.Sc=power.Power.Sc*TR.PT;

power_scaled->Power.Ptotal=power.Power.Ptotal*TR.PT;
power_scaled->Power.Qtotal=power.Power.Qtotal*TR.PT;
power_scaled->Power.Stotal=power.Power.Stotal*TR.PT;


energy_scaling(energy,&energy_scaled);


}


void symmetrical_components(union uAdcData inphase,union uAdcData quad, union symmetricalComponents *x){


float temp_r,temp_i,temp_t;
	
static float sumV0=0,sumV1=0,sumV2=0;

	
	
static uint16_t counter=0;	
	
//********	
temp_r=	inphase.data.Van + inphase.data.Vbn*sym_r + inphase.data.Vcn*sym_r;
temp_i=	sym_i*(quad.data.Vbn-quad.data.Vcn);
temp_t=	(inphase.data.Van + inphase.data.Vbn + 	inphase.data.Vcn)*sym_i3;
	
sumV0  +=temp_t*temp_t;
sumV1  +=(temp_r - temp_i)*sym_i3*(temp_r - temp_i)*sym_i3;
sumV2  +=(temp_r + temp_i)*sym_i3*(temp_r + temp_i)*sym_i3;
	
//********
	
temp_r=	inphase.data.Ia + inphase.data.Ib*sym_r + inphase.data.Ic*sym_r;
temp_i=	sym_i*(quad.data.Ib-quad.data.Ic);
temp_t=	(inphase.data.Ia + inphase.data.Ib + 	inphase.data.Ic)*sym_i3;
	
sumI0  +=temp_t*temp_t;
sumI1  +=(temp_r - temp_i)*sym_i3*(temp_r - temp_i)*sym_i3;
sumI2  +=(temp_r + temp_i)*sym_i3*(temp_r + temp_i)*sym_i3;

//rms calc

switch(counter++){

	case 1: arm_sqrt_f32((sumV0*0.0005f),&(x->data.Vpn_0));sumV0=0.0f;break;
	case 2: arm_sqrt_f32((sumV1*0.0005f),&(x->data.Vpn_1));sumV1=0.0f;break;
	case 3: arm_sqrt_f32((sumV2*0.0005f),&(x->data.Vpn_2));sumV2=0.0f;break;
	
	case 4: arm_sqrt_f32((sumI0*0.0005f),&(x->data.I_0));sumI0=0.0f;break;
	case 5: arm_sqrt_f32((sumI1*0.0005f),&(x->data.I_1));sumI1=0.0f;break;
	case 6: arm_sqrt_f32((sumI2*0.0005f),&(x->data.I_2));sumI2=0.0f;break;
	
	default:if(counter==2000){counter=0;}break;

}





x->data.UNB_V=(x->data.Vpn_1>eps)?(100.0f*x->data.Vpn_2/x->data.Vpn_1):(0.0f);
x->data.UNB_I=(x->data.Vpn_1>eps)?(100.0f*x->data.I_2  /x->data.I_1)  :(0.0f);	
	

}


//Scope Menus

void phaseDetect(union uAdcData inphase,union uAdcData quad,float *phase){


	(*phase)=atan2f(-inphase.data.Van,-quad.data.Van);
	

}



//harmonic side
//spectral analysis
//caution: input structure has to be initialized and used only once
//external pCounter is needed
//twfactors truncated to 13th
 


void signal_spectra(
	
	float rtInput, 
	struct spectra *h,
	unsigned int qBufferLength,	//updated buffer length
	const float *twBufferReal,				//twiddle factor Real coeffs
	const float *twBufferImag,				//twiddle factor Imag coeffs    
	unsigned int pCounter)

{

	float x_error;
	float temp_real,temp_imag;

	unsigned int i;

	//out_scale=sqrt2/(float)qBufferLength;


	x_error=h->qBuffer[pCounter]-rtInput;
	h->qBuffer[pCounter]=rtInput;

	for(i=0;i<20;i++){

	temp_real =twBufferReal[i+1]* (h->foutReal[i]+x_error)-twBufferImag[i+1]*h->foutImag[i];
	temp_imag= twBufferImag[i+1]* (h->foutReal[i]+x_error)+twBufferReal[i+1]*h->foutImag[i];



	h->foutReal[i]=temp_real;
	h->foutImag[i]=temp_imag;
	
	}


}


void thd_calc(union thdData* thd ){

	static uint8_t index=0;;
	uint8_t i;
	float sum=0;


	for(i=1;i<20;i++){
		
	sum+=bin_array[index][i]*bin_array[index][i];
		
	}
	
	arm_sqrt_f32(sum,&(thd->buffer[index]));
	
	if(++index==6){index=0;}
	
	


}



void harmonics_routine(){
	
	static uint8_t index=0,count=0;
	static uint8_t out=0,latch=0;
	static uint32_t prdCount=0;	
	
	
	pulseGen(400,200,1,&out,&latch,&prdCount);

	switch (index){
		
		
		case 0: if(out){signal_spectra(AN.data.Van,&harm[Van],fftLength,coeffs_real,coeffs_imag,count);}			
						else{signal_spectra(AN.data.Ia,&harm[Ia],  fftLength,coeffs_real,coeffs_imag,count);}  break;	
		
		case 1: if(out){signal_spectra(AN.data.Vbn,&harm[Vbn],fftLength,coeffs_real,coeffs_imag,count);}			
						else{signal_spectra(AN.data.Ib,&harm[Ib],  fftLength,coeffs_real,coeffs_imag,count);}  break;

		case 2: if(out){signal_spectra(AN.data.Vcn,&harm[Vcn],fftLength,coeffs_real,coeffs_imag,count);}			
						else{signal_spectra(AN.data.Ic,&harm[Ic],  fftLength,coeffs_real,coeffs_imag,count);}  break;			
		
		case 3:	if(++count==fftLength){count=0;}	break;	
		

	}
	
	if(++index==4){index=0;}
	
}


void bin_magnitudes(){
	
	float first_mag=2.0f,first_imag=1.0f;
		
	
	uint8_t i,j;
	
for(i=0;i<6;i++){
	
	first_mag=sqrtf(harm[i].foutReal[0]*harm[i].foutReal[0]+harm[i].foutImag[0]*harm[i].foutImag[0]);
	
	if(first_mag>1.0f){
	
	first_imag=100.0f/(first_mag);	
	bin_array[i][0]=100.0;
	
	for(j=1;j<21;j++){
	
	bin_array[i][j]=
		
	sqrtf(harm[i].foutReal[j]*harm[i].foutReal[j]+harm[i].foutImag[j]*harm[i].foutImag[j])*first_imag;
		
	 }
  }else{
		
		for(j=1;j<21;j++){
		bin_array[i][j]=0;
		
	 }
	}
 }
}

void offline_calculations(){
	
uint8_t i;

bin_magnitudes();
thd_calc(&thd);	

//scaled parameters
	
scaled_parameters(trueRMS,fundRMS,power_iq,	&trueRMS_scaled,&fundRMS_scaled,&power_scaled);


}



