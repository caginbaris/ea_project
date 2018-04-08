#ifndef __measurement_definitions_H
#define __measurement_definitions_H


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





#endif