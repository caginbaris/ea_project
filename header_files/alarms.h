#ifndef __alarms_H
#define __alarms_H


#include <stdint.h>

union alarmDefinitions{


struct{

	uint32_t Van:1;//1
	uint32_t Vbn:1;//2
	uint32_t Vcn:1;//3
	
	uint32_t Vab:1;//4
	uint32_t Vbc:1;//5
	uint32_t Vca:1;//6
	
	uint32_t Ia:1;//7
	uint32_t Ib:1;//8
	uint32_t Ic:1;//9
	
	uint32_t Pa:1;//10
	uint32_t Pb:1;//11
	uint32_t Pc:1;//12
	uint32_t Ptotal:1;//13
	
	uint32_t Qa:1;//14
	uint32_t Qb:1;//15
	uint32_t Qc:1;//16
	uint32_t Qtotal:1;//17
	
	uint32_t Sa:1;//18
	uint32_t Sb:1;//19
	uint32_t Sc:1;//20
	uint32_t Stotal:1;//21
	
	uint32_t QP_a:1;//22
	uint32_t QP_b:1;//23
	uint32_t QP_c:1;//24
	uint32_t QP_total:1;//25
	
	uint32_t VARHi_o_WHi:1;//26
	uint32_t VARHe_o_WHi:1;//27
	
	uint32_t V2:1;//28
	uint32_t I2:1;//29
	
	uint32_t unb_ratio_V:1;//30
	uint32_t unb_ratio_I:1;//31
	

}bit;


uint32_t all;

};


extern union alarmDefinitions alarmEnable;
extern union alarmDefinitions alarmOut;




#endif