#ifndef __Modbus_Map_H__
#define __Modbus_Map_H__

#include "measurement_definitions.h"

union modbusMappingReadData{
	
	
	struct {

	float* tRMS_Van;//1
	float* tRMS_Vbn;
	float* tRMS_Vcn;

	float* fRMS_Van;
	float* fRMS_Vbn;
	float* fRMS_Vcn;

	float* tRMS_Vab;
	float* tRMS_Vbc;
	float* tRMS_Vca;

	float* fRMS_Vab;
	float* fRMS_Vbc;
	float* fRMS_Vca;
	
	float* tRMS_Ia;
	float* tRMS_Ib;
	float* tRMS_Ic;

	float* fRMS_Ia;
	float* fRMS_Ib;
	float* fRMS_Ic;
	
	float* Pa;
	float* Pb;
	float* Pc;
			
	float* Qa;
	float* Qb;		
	float* Qc;
		
	float* Sa;
	float* Sb;
	float* Sc;
		
	float* Ptotal;
	float* Qtotal;
	float* Stotal;
		
	float* PFa;//31
	float* PFb;
	float* PFc;
	float* PFtotal;
		
	float* ratioA;//35
	float* ratioB;
	float* ratioC;
	float* ratioTotal;
	
	float* active_import_a_scaled;//39
	float* active_import_b_scaled;
	float* active_import_c_scaled;
	float* active_import_total_scaled;

	float* active_export_a_scaled;//43
	float* active_export_b_scaled;
	float* active_export_c_scaled;
	float* active_export_total_scaled;
		
	float* reactive_import_a_scaled;//47
	float* reactive_import_b_scaled;
	float* reactive_import_c_scaled;
	float* reactive_import_total_scaled;
		
	float* reactive_export_a_scaled;//51
	float* reactive_export_b_scaled;
	float* reactive_export_c_scaled;
	float* reactive_export_total_scaled;
		
	float* apparent_energy_a_scaled;//55
	float* apparent_energy_b_scaled;
	float* apparent_energy_c_scaled;
	float* apparent_energy_total_scaled;
	
	float* thd_Van;//59
	float* thd_Vbn;
	float* thd_Vcn;
	
	float* thd_Ia;//62
	float* thd_Ib;
	float* thd_Ic;
	
	float* unb_Vpn;//65
	float* unb_I;//66
	
	}data;
	
	float*   buffer[66];	

};


extern union modbusMappingReadData readHoldingMap;




#endif
