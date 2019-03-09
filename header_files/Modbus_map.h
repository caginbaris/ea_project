#ifndef __Modbus_Map_H__
#define __Modbus_Map_H__

#include "measurement_definitions.h"

union modbusMappingReadData{
	
	
	struct {

	unsigned char* tRMS_Van;//1
	unsigned char* tRMS_Vbn;//2
	unsigned char* tRMS_Vcn;//3

	unsigned char* fRMS_Van;//4
	unsigned char* fRMS_Vbn;//5
	unsigned char* fRMS_Vcn;//6

	unsigned char* tRMS_Vab;//7
	unsigned char* tRMS_Vbc;//8
	unsigned char* tRMS_Vca;//9

	unsigned char* fRMS_Vab;//10
	unsigned char* fRMS_Vbc;//11
	unsigned char* fRMS_Vca;//12
	
	unsigned char* tRMS_Ia;//13
	unsigned char* tRMS_Ib;//14
	unsigned char* tRMS_Ic;//15

	unsigned char* fRMS_Ia;//16
	unsigned char* fRMS_Ib;//17
	unsigned char* fRMS_Ic;//18
	
	unsigned char* Pa;//19
	unsigned char* Pb;//20
	unsigned char* Pc;//21
			
	unsigned char* Qa;//22
	unsigned char* Qb;//23		
	unsigned char* Qc;//24
		
	unsigned char* Sa;//25
	unsigned char* Sb;//26
	unsigned char* Sc;//27
		
	unsigned char* Ptotal;//28
	unsigned char* Qtotal;//29
	unsigned char* Stotal;//30
		
	unsigned char* PFa;//31
	unsigned char* PFb;//32
	unsigned char* PFc;//33
	unsigned char* PFtotal;//34
		
	unsigned char* ratioA;//35
	unsigned char* ratioB;//36
	unsigned char* ratioC;//37
	unsigned char* ratioTotal;//38
	
	unsigned char* active_import_a_scaled;//39
	unsigned char* active_import_b_scaled;//40
	unsigned char* active_import_c_scaled;//41
	unsigned char* active_import_total_scaled;//42

	unsigned char* active_export_a_scaled;//43
	unsigned char* active_export_b_scaled;//44
	unsigned char* active_export_c_scaled;//45
	unsigned char* active_export_total_scaled;//46
		
	unsigned char* reactive_import_a_scaled;//47
	unsigned char* reactive_import_b_scaled;//48
	unsigned char* reactive_import_c_scaled;//49
	unsigned char* reactive_import_total_scaled;//50
		
	unsigned char* reactive_export_a_scaled;//51
	unsigned char* reactive_export_b_scaled;//52
	unsigned char* reactive_export_c_scaled;//53
	unsigned char* reactive_export_total_scaled;//54
		
	unsigned char* apparent_energy_a_scaled;//55
	unsigned char* apparent_energy_b_scaled;//56
	unsigned char* apparent_energy_c_scaled;//57
	unsigned char* apparent_energy_total_scaled;//58
	
	unsigned char* thd_Van;//59
	unsigned char* thd_Vbn;//60
	unsigned char* thd_Vcn;//61
	
	unsigned char* thd_Ia;//62
	unsigned char* thd_Ib;//63
	unsigned char* thd_Ic;//64
	
	unsigned char* Vpn_1;//65
	unsigned char* Vpn_2;//66
	unsigned char* Vpn_0;//67
	
	unsigned char* I_1;//68
	unsigned char* I_2;//69
	unsigned char* I_0;//70
	
	unsigned char* UNB_V;//71
	unsigned char* UNB_I;//72
	
	
	unsigned char* hVan[20];//73
	unsigned char* hVbn[20];//93
	unsigned char* hVcn[20];//113
	
	unsigned char* hIa[20];//133
	unsigned char* hIb[20];//153
	unsigned char* hIc[20];//173
	
	unsigned char* record[46];//193
	
	unsigned char* sVan[20];//193+46
	unsigned char* sVbn[20];//213+46
	unsigned char* sVcn[20];//233+46
	
	unsigned char* sIa[20];//253+46
	unsigned char* sIb[20];//273+46
	unsigned char* sIc[20];//293+46
	
	}data;
	
	unsigned char*   buffer[358];	

};


extern union modbusMappingReadData readHoldingMap;

void init_Map(void);

#endif
