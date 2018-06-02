

#include "conversion.h"
#include "measurement_definitions.h"
#include <math.h>
#include "arm_math.h" //cau should transferred



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
	
	switch(counter){
	
		case 0:arm_sqrt_f32(rms_sum.buffer[0]*inverse_avg_sample,&rms.buffer[0]);rms_sum.buffer[0]=0.0f;break;
		case 1:arm_sqrt_f32(rms_sum.buffer[1]*inverse_avg_sample,&rms.buffer[1]);rms_sum.buffer[1]=0.0f;break;
		case 2:arm_sqrt_f32(rms_sum.buffer[2]*inverse_avg_sample,&rms.buffer[2]);rms_sum.buffer[2]=0.0f;break;
		
		case 3:arm_sqrt_f32(rms_sum.buffer[3]*inverse_avg_sample,&rms.buffer[3]);rms_sum.buffer[3]=0.0f;break;
		case 4:arm_sqrt_f32(rms_sum.buffer[4]*inverse_avg_sample,&rms.buffer[4]);rms_sum.buffer[4]=0.0f;break;
		case 5:arm_sqrt_f32(rms_sum.buffer[5]*inverse_avg_sample,&rms.buffer[5]);rms_sum.buffer[5]=0.0f;break;
		
		case 6:arm_sqrt_f32(rms_sum.buffer[6]*inverse_avg_sample,&rms.buffer[6]);rms_sum.buffer[6]=0.0f;break;
		case 7:arm_sqrt_f32(rms_sum.buffer[7]*inverse_avg_sample,&rms.buffer[7]);rms_sum.buffer[7]=0.0f;break;
		case 8:arm_sqrt_f32(rms_sum.buffer[8]*inverse_avg_sample,&rms.buffer[8]);rms_sum.buffer[8]=0.0f;break;
		
		#if 0
		case 0:rms.buffer[0]=sqrtf(rms_sum.buffer[0]*inverse_avg_sample);rms_sum.buffer[0]=0.0f;break;
		case 1:rms.buffer[1]=sqrtf(rms_sum.buffer[1]*inverse_avg_sample);rms_sum.buffer[1]=0.0f;break;
		case 2:rms.buffer[2]=sqrtf(rms_sum.buffer[2]*inverse_avg_sample);rms_sum.buffer[2]=0.0f;break;
		
		case 3:rms.buffer[3]=sqrtf(rms_sum.buffer[3]*inverse_avg_sample);rms_sum.buffer[3]=0.0f;break;
		case 4:rms.buffer[4]=sqrtf(rms_sum.buffer[4]*inverse_avg_sample);rms_sum.buffer[4]=0.0f;break;
		case 5:rms.buffer[5]=sqrtf(rms_sum.buffer[5]*inverse_avg_sample);rms_sum.buffer[5]=0.0f;break;
		
		case 6:rms.buffer[6]=sqrtf(rms_sum.buffer[6]*inverse_avg_sample);rms_sum.buffer[6]=0.0f;break;
		case 7:rms.buffer[7]=sqrtf(rms_sum.buffer[7]*inverse_avg_sample);rms_sum.buffer[7]=0.0f;break;
		case 8:rms.buffer[8]=sqrtf(rms_sum.buffer[8]*inverse_avg_sample);rms_sum.buffer[8]=0.0f;break;
		#endif
		
		
		default: break;
	}
	
	
	
	if(counter++>=periodSampleNo*numberOfPeriod){counter=0;}

	return rms;
}

//def second order section filter implementations 
//1 	coeff is sequenced sos coefficents suxh --> b1,b2,b3,a2,a3 order
//2.0 function invocation shown below  
//2.1 "output=sos_implementation(input(real-time),output(lef-side),coeff_data(array_name),SOS2data(different for all parameters ));

float sos_implementation(float x ,float yBack, const float *coeffs, struct SOS *back){

	float y;

	
	y=x*(*coeffs)	+	(back->xz1)	*(*(coeffs+1))		+	(back->xz2)*(*(coeffs+2))
								- (yBack)			*(*(coeffs+3))		-	(back->yz2)*(*(coeffs+4));

	
	back->yz2=yBack;
	back->xz2=back->xz1;
	back->xz1=x;
	
	return y;
	
}


//inphase and quadrature  parameters derivation part

void iq_generation( union uAdcData input,union uAdcData *iq,const float *iq_coeffs,struct SOS *all){

	uint8_t i;
	
	
	for (i=0;i<6;i++){
	
		iq->buffer[i]		=sos_implementation(input.buffer[i],iq->buffer[i],iq_coeffs,&all[i]);
		
	}
	
	iq->data.Vab=iq->data.Van-iq->data.Vbn;
	iq->data.Vbc=iq->data.Vbn-iq->data.Vcn;
	iq->data.Vca=iq->data.Vcn-iq->data.Van;
	
}


void fund_RMS(union uAdcData inphase,union uAdcData quad,union uAdcData *rms){
	
	uint8_t counter=0;
	uint8_t i;
	
	
	
	for (i=0;i<6;i++){arm_sqrt_f32((inphase.buffer[i]*inphase.buffer[i]+quad.buffer[i]*quad.buffer[i])*iq_rms_scale,&rms->buffer[i]);}
	
	
	#if 0
	switch(counter){
	
	case 0:for (i=0;i<3;i++){arm_sqrt_f32((inphase.buffer[i]*inphase.buffer[i]+quad.buffer[i]*quad.buffer[i])*iq_rms_scale,&rms->buffer[i]);}
	case 1:for (i=counter;i<6;i++){arm_sqrt_f32((inphase.buffer[i]*inphase.buffer[i]+quad.buffer[i]*quad.buffer[i])*iq_rms_scale,&rms->buffer[i]);}
	case 2:for (i=counter;i<9;i++){arm_sqrt_f32((inphase.buffer[i]*inphase.buffer[i]+quad.buffer[i]*quad.buffer[i])*iq_rms_scale,&rms->buffer[i]);}	
	}
	
	if(++counter==3){counter=0;}
		
	#endif
	
	

}


void power_calculations_iq(union uAdcData inphase,union uAdcData quad, union powerParameters *x ){

		x->Power.Pa=(inphase.data.Van*inphase.data.Ia + quad.data.Van*quad.data.Ia)*i2;
		x->Power.Pb=(inphase.data.Vbn*inphase.data.Ib + quad.data.Vbn*quad.data.Ib)*i2;
		x->Power.Pc=(inphase.data.Vcn*inphase.data.Ic + quad.data.Vcn*quad.data.Ic)*i2;
	
		x->Power.Qa=(quad.data.Van*inphase.data.Ia - inphase.data.Van*quad.data.Ia)*i2;
		x->Power.Qb=(quad.data.Vbn*inphase.data.Ib - inphase.data.Vbn*quad.data.Ib)*i2;
		x->Power.Qc=(quad.data.Vcn*inphase.data.Ic - inphase.data.Vcn*quad.data.Ic)*i2;
	
		x->Power.Sa=sqrtf(x->Power.Pa*x->Power.Pa + x->Power.Qa*x->Power.Qa);
		x->Power.Sb=sqrtf(x->Power.Pb*x->Power.Pb + x->Power.Qb*x->Power.Qb);
		x->Power.Sc=sqrtf(x->Power.Pb*x->Power.Pc + x->Power.Qc*x->Power.Qc);
	
		x->Power.Ptotal=x->Power.Pa + x->Power.Pb + x->Power.Pc;
		x->Power.Qtotal=x->Power.Qa + x->Power.Qb + x->Power.Qc;
		x->Power.Stotal=sqrtf(x->Power.Ptotal*x->Power.Ptotal+
										x->Power.Qtotal*x->Power.Qtotal);
	
		x->Power.PFa 			= x->Power.Sa==0 			?  indefinite : x->Power.Pa/x->Power.Sa;
		x->Power.PFb 			= x->Power.Sb==0 			?  indefinite : x->Power.Pb/x->Power.Sb;
		x->Power.PFc 			= x->Power.Sc==0 			?  indefinite : x->Power.Pc/x->Power.Sc;
		x->Power.PFtotal 	= x->Power.Stotal==0 	?  indefinite : x->Power.Ptotal/x->Power.Stotal;
		
}

void power_calculations_true(union uAdcData AN,union uAdcData rms, union powerParameters *x){
	
	
	static union powerParameters sum={0};
	static uint16_t counter=0;
	
	
	
	sum.Power.Pa+=AN.data.Ia*AN.data.Van;
	sum.Power.Pb+=AN.data.Ib*AN.data.Vbn;
	sum.Power.Pc+=AN.data.Ic*AN.data.Vcn;
	
	
	x->Power.Sa=rms.data.Van*rms.data.Ia;
	x->Power.Sb=rms.data.Vbn*rms.data.Ib;
	x->Power.Sc=rms.data.Vcn*rms.data.Ic;
	


	if(++counter==_10period){
	
	x->Power.Pa=sum.Power.Pa*_i10period;sum.Power.Pa=0.0f;
	x->Power.Pb=sum.Power.Pb*_i10period;sum.Power.Pb=0.0f;
	x->Power.Pc=sum.Power.Pc*_i10period;sum.Power.Pc=0.0f;
		

		
	counter=0;	
		
	}
	
	x->Power.Qa=sqrtf(x->Power.Sa*x->Power.Sa-x->Power.Pa*x->Power.Pa);
	x->Power.Qb=sqrtf(x->Power.Sb*x->Power.Sb-x->Power.Pb*x->Power.Pb);
	x->Power.Qc=sqrtf(x->Power.Sc*x->Power.Sc-x->Power.Pc*x->Power.Pc);
	
	x->Power.Ptotal=	x->Power.Pa + x->Power.Pb + x->Power.Pc;
	x->Power.Qtotal=	x->Power.Qa + x->Power.Qb + x->Power.Qc;
	x->Power.Stotal=	x->Power.Sa + x->Power.Sb + x->Power.Sc;
	
	
	x->Power.PFa 			= x->Power.Sa==0 			?  indefinite : x->Power.Pa/x->Power.Sa;
	x->Power.PFb 			= x->Power.Sb==0 			?  indefinite : x->Power.Pb/x->Power.Sb;
	x->Power.PFc 			= x->Power.Sc==0 			?  indefinite : x->Power.Pc/x->Power.Sc;
	x->Power.PFtotal 	= x->Power.Stotal==0 	?  indefinite : x->Power.Ptotal/x->Power.Stotal;
	
	
}


//88

void symmetrical_components(union uAdcData inphase,union uAdcData quad, union symmetricalComponents *x){

uint8_t i=0;	
float temp_r,temp_i;
	
	
//********	
temp_r=	inphase.data.Van + inphase.data.Vbn*sym_r + inphase.data.Vcn*sym_r;
temp_i=	sym_i*(quad.data.Vbn-quad.data.Vcn);
	
	
x->data.Vpn_0  =(inphase.data.Van + inphase.data.Vbn + 	inphase.data.Vcn)*sym_i3;
x->data.Vpn_1  =(temp_r - temp_i)*sym_i3;
x->data.Vpn_2 = (temp_r + temp_i)*sym_i3;	
	
//********
temp_r=	inphase.data.Ia + inphase.data.Ib*sym_r + inphase.data.Ic*sym_r;
temp_i=	sym_i*(quad.data.Ib-quad.data.Ic);
	
	
x->data.Vpn_0  =(inphase.data.Ia + inphase.data.Ib + 	inphase.data.Ic)*sym_i3;
x->data.Vpn_1  =(temp_r - temp_i)*sym_i3;
x->data.Vpn_2 = (temp_r + temp_i)*sym_i3;		
	
	
//********	
temp_r=	inphase.data.Vab + inphase.data.Vbc*sym_r + inphase.data.Vca*sym_r;
temp_i=	sym_i*(quad.data.Vbc-quad.data.Vca);
	
	
x->data.Vpp_0  =(inphase.data.Vab + inphase.data.Vbc + 	inphase.data.Vca)*sym_i3;
x->data.Vpp_1  =(temp_r - temp_i)*sym_i3;
x->data.Vpp_2 = (temp_r + temp_i)*sym_i3;		

}


void phaseDetect(union uAdcData inphase,union uAdcData quad,union uAdcData *phase){


	phase->data.Van=atan2f(-inphase.data.Van,-quad.data.Van);
	


}
