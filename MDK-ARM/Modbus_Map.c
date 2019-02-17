#include "Modbus_Map.h"
#include "conversion.h"
#include "measurement_definitions.h"

union modbusMappingReadData readHoldingMap;

void init_Map(void){
	
	
		readHoldingMap.data.tRMS_Van=(unsigned char*)&(trueRMS.data.Van);
		readHoldingMap.data.tRMS_Vbn=(unsigned char*)&(trueRMS.data.Vbn);	
		readHoldingMap.data.tRMS_Vcn=(unsigned char*)&(trueRMS.data.Vcn);
	
		readHoldingMap.data.fRMS_Van=(unsigned char*)&(fundRMS.data.Van);
		readHoldingMap.data.fRMS_Vbn=(unsigned char*)&(fundRMS.data.Vbn);	
		readHoldingMap.data.fRMS_Vcn=(unsigned char*)&(fundRMS.data.Vcn);
	

		readHoldingMap.data.tRMS_Vab=(unsigned char*)&(trueRMS.data.Vab);
		readHoldingMap.data.tRMS_Vbc=(unsigned char*)&(trueRMS.data.Vbc);	
		readHoldingMap.data.tRMS_Vca=(unsigned char*)&(trueRMS.data.Vca);
	
		readHoldingMap.data.fRMS_Vab=(unsigned char*)&(fundRMS.data.Vab);
		readHoldingMap.data.fRMS_Vbc=(unsigned char*)&(fundRMS.data.Vbc);	
		readHoldingMap.data.fRMS_Vca=(unsigned char*)&(fundRMS.data.Vca);
	
	
		readHoldingMap.data.tRMS_Ia=(unsigned char*)&(trueRMS.data.Ia);
		readHoldingMap.data.tRMS_Ib=(unsigned char*)&(trueRMS.data.Ib);	
		readHoldingMap.data.tRMS_Ic=(unsigned char*)&(trueRMS.data.Ic);
	
		readHoldingMap.data.fRMS_Ia=(unsigned char*)&(fundRMS.data.Ia);
		readHoldingMap.data.fRMS_Ib=(unsigned char*)&(fundRMS.data.Ib);	
		readHoldingMap.data.fRMS_Ic=(unsigned char*)&(fundRMS.data.Ic);
	
	#if 0

	 fRMS_Van;
	 fRMS_Vbn;
	 fRMS_Vcn;

	 tRMS_Vab;
	 tRMS_Vbc;
	 tRMS_Vca;

	 fRMS_Vab;
	 fRMS_Vbc;
	 fRMS_Vca;
	
	 tRMS_Ia;
	 tRMS_Ib;
	 tRMS_Ic;

	 fRMS_Ia;
	 fRMS_Ib;
	 fRMS_Ic;
	
	 Pa;
	 Pb;
	 Pc;
			
	 Qa;
	 Qb;		
	 Qc;
		
	 Sa;
	 Sb;
	 Sc;
		
	 Ptotal;
	 Qtotal;
	 Stotal;
		
	 PFa;//31
	 PFb;
	 PFc;
	 PFtotal;
		
	 ratioA;//35
	 ratioB;
	 ratioC;
	 ratioTotal;
	
	 active_import_a_scaled;//39
	 active_import_b_scaled;
	 active_import_c_scaled;
	 active_import_total_scaled;

	 active_export_a_scaled;//43
	 active_export_b_scaled;
	 active_export_c_scaled;
	 active_export_total_scaled;
		
	 reactive_import_a_scaled;//47
	 reactive_import_b_scaled;
	 reactive_import_c_scaled;
	 reactive_import_total_scaled;
		
	 reactive_export_a_scaled;//51
	 reactive_export_b_scaled;
	 reactive_export_c_scaled;
	 reactive_export_total_scaled;
		
	 apparent_energy_a_scaled;//55
	 apparent_energy_b_scaled;
	 apparent_energy_c_scaled;
	 apparent_energy_total_scaled;
	
	 thd_Van;//59
	 thd_Vbn;
	 thd_Vcn;
	
	 thd_Ia;//62
	 thd_Ib;
	 thd_Ic;
	
	 unb_Vpn;//65
	 unb_I;//66
	
	
	#endif





}