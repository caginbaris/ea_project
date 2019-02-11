#ifndef __Modbus_Map_H__
#define __Modbus_Map_H__

#include "measurement_definitions.h"

union modbusMappingReadData{
	
	
	struct {

	unsigned char* tRMS_Van;//1
	unsigned char* tRMS_Vbn;
	unsigned char* tRMS_Vcn;

	unsigned char* fRMS_Van;
	unsigned char* fRMS_Vbn;
	unsigned char* fRMS_Vcn;

	unsigned char* tRMS_Vab;
	unsigned char* tRMS_Vbc;
	unsigned char* tRMS_Vca;

	unsigned char* fRMS_Vab;
	unsigned char* fRMS_Vbc;
	unsigned char* fRMS_Vca;
	
	unsigned char* tRMS_Ia;
	unsigned char* tRMS_Ib;
	unsigned char* tRMS_Ic;

	unsigned char* fRMS_Ia;
	unsigned char* fRMS_Ib;
	unsigned char* fRMS_Ic;
	
	unsigned char* Pa;
	unsigned char* Pb;
	unsigned char* Pc;
			
	unsigned char* Qa;
	unsigned char* Qb;		
	unsigned char* Qc;
		
	unsigned char* Sa;
	unsigned char* Sb;
	unsigned char* Sc;
		
	unsigned char* Ptotal;
	unsigned char* Qtotal;
	unsigned char* Stotal;
		
	unsigned char* PFa;//31
	unsigned char* PFb;
	unsigned char* PFc;
	unsigned char* PFtotal;
		
	unsigned char* ratioA;//35
	unsigned char* ratioB;
	unsigned char* ratioC;
	unsigned char* ratioTotal;
	
	unsigned char* active_import_a_scaled;//39
	unsigned char* active_import_b_scaled;
	unsigned char* active_import_c_scaled;
	unsigned char* active_import_total_scaled;

	unsigned char* active_export_a_scaled;//43
	unsigned char* active_export_b_scaled;
	unsigned char* active_export_c_scaled;
	unsigned char* active_export_total_scaled;
		
	unsigned char* reactive_import_a_scaled;//47
	unsigned char* reactive_import_b_scaled;
	unsigned char* reactive_import_c_scaled;
	unsigned char* reactive_import_total_scaled;
		
	unsigned char* reactive_export_a_scaled;//51
	unsigned char* reactive_export_b_scaled;
	unsigned char* reactive_export_c_scaled;
	unsigned char* reactive_export_total_scaled;
		
	unsigned char* apparent_energy_a_scaled;//55
	unsigned char* apparent_energy_b_scaled;
	unsigned char* apparent_energy_c_scaled;
	unsigned char* apparent_energy_total_scaled;
	
	unsigned char* thd_Van;//59
	unsigned char* thd_Vbn;
	unsigned char* thd_Vcn;
	
	unsigned char* thd_Ia;//62
	unsigned char* thd_Ib;
	unsigned char* thd_Ic;
	
	unsigned char* unb_Vpn;//65
	unsigned char* unb_I;//66
	
	}data;
	
	unsigned char*   buffer[66];	

};


extern union modbusMappingReadData readHoldingMap;

void init_Map(void);

#endif
