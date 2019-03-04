#include "Modbus_Map.h"
#include "conversion.h"
#include "measurement_definitions.h"
#include "record.h"


extern float bin_array[6][20];
extern float snap[6][20];


union modbusMappingReadData readHoldingMap;

void init_Map(void){
	
		uint8_t i;
	
		readHoldingMap.data.tRMS_Van=(unsigned char*)&(trueRMS_scaled.data.Van);
		readHoldingMap.data.tRMS_Vbn=(unsigned char*)&(trueRMS_scaled.data.Vbn);	
		readHoldingMap.data.tRMS_Vcn=(unsigned char*)&(trueRMS_scaled.data.Vcn);
	
		readHoldingMap.data.fRMS_Van=(unsigned char*)&(fundRMS_scaled.data.Van);
		readHoldingMap.data.fRMS_Vbn=(unsigned char*)&(fundRMS_scaled.data.Vbn);	
		readHoldingMap.data.fRMS_Vcn=(unsigned char*)&(fundRMS_scaled.data.Vcn);
	

		readHoldingMap.data.tRMS_Vab=(unsigned char*)&(trueRMS_scaled.data.Vab);
		readHoldingMap.data.tRMS_Vbc=(unsigned char*)&(trueRMS_scaled.data.Vbc);	
		readHoldingMap.data.tRMS_Vca=(unsigned char*)&(trueRMS_scaled.data.Vca);
	
		readHoldingMap.data.fRMS_Vab=(unsigned char*)&(fundRMS_scaled.data.Vab);
		readHoldingMap.data.fRMS_Vbc=(unsigned char*)&(fundRMS_scaled.data.Vbc);	
		readHoldingMap.data.fRMS_Vca=(unsigned char*)&(fundRMS_scaled.data.Vca);
	
	
		readHoldingMap.data.tRMS_Ia=(unsigned char*)&(trueRMS_scaled.data.Ia);
		readHoldingMap.data.tRMS_Ib=(unsigned char*)&(trueRMS_scaled.data.Ib);	
		readHoldingMap.data.tRMS_Ic=(unsigned char*)&(trueRMS_scaled.data.Ic);
	
		readHoldingMap.data.fRMS_Ia=(unsigned char*)&(fundRMS_scaled.data.Ia);
		readHoldingMap.data.fRMS_Ib=(unsigned char*)&(fundRMS_scaled.data.Ib);	
		readHoldingMap.data.fRMS_Ic=(unsigned char*)&(fundRMS_scaled.data.Ic);
		
		
		readHoldingMap.data.Pa=(unsigned char*)&(power_scaled.Power.Pa);
		readHoldingMap.data.Pb=(unsigned char*)&(power_scaled.Power.Pb);	
		readHoldingMap.data.Pc=(unsigned char*)&(power_scaled.Power.Pc);
		
		readHoldingMap.data.Qa=(unsigned char*)&(power_scaled.Power.Qa);
		readHoldingMap.data.Qb=(unsigned char*)&(power_scaled.Power.Qb);	
		readHoldingMap.data.Qc=(unsigned char*)&(power_scaled.Power.Qc);
		
		readHoldingMap.data.Sa=(unsigned char*)&(power_scaled.Power.Sa);
		readHoldingMap.data.Sb=(unsigned char*)&(power_scaled.Power.Sb);	
		readHoldingMap.data.Sc=(unsigned char*)&(power_scaled.Power.Sc);
		
		readHoldingMap.data.Ptotal=(unsigned char*)&(power_scaled.Power.Ptotal);
		readHoldingMap.data.Qtotal=(unsigned char*)&(power_scaled.Power.Qtotal);	
		readHoldingMap.data.Stotal=(unsigned char*)&(power_scaled.Power.Stotal);
		
		readHoldingMap.data.PFa=(unsigned char*)&(power_scaled.Power.PFa);
		readHoldingMap.data.PFb=(unsigned char*)&(power_scaled.Power.PFb);	
		readHoldingMap.data.PFc=(unsigned char*)&(power_scaled.Power.PFc);
		readHoldingMap.data.PFtotal=(unsigned char*)&(power_scaled.Power.PFtotal);
		
		readHoldingMap.data.ratioA=(unsigned char*)&(power_iq.Power.ratioA);
		readHoldingMap.data.ratioA=(unsigned char*)&(power_iq.Power.ratioB);	
		readHoldingMap.data.ratioA=(unsigned char*)&(power_iq.Power.ratioC);
		readHoldingMap.data.ratioTotal=(unsigned char*)&(power_iq.Power.ratioTotal);
		
		readHoldingMap.data.active_import_a_scaled=(unsigned char*)&(energy_scaled.active_import_a);
		readHoldingMap.data.active_import_b_scaled=(unsigned char*)&(energy_scaled.active_import_b);	
		readHoldingMap.data.active_import_c_scaled=(unsigned char*)&(energy_scaled.active_import_c);
		readHoldingMap.data.active_import_total_scaled=(unsigned char*)&(energy_scaled.active_import_total);
		
		readHoldingMap.data.active_export_a_scaled=(unsigned char*)&(energy_scaled.active_import_a);
		readHoldingMap.data.active_export_b_scaled=(unsigned char*)&(energy_scaled.active_import_b);	
		readHoldingMap.data.active_export_c_scaled=(unsigned char*)&(energy_scaled.active_import_c);
		readHoldingMap.data.active_export_total_scaled=(unsigned char*)&(energy_scaled.active_import_total);
		
		readHoldingMap.data.reactive_import_a_scaled=(unsigned char*)&(energy_scaled.reactive_import_a);
		readHoldingMap.data.reactive_import_b_scaled=(unsigned char*)&(energy_scaled.reactive_import_b);	
		readHoldingMap.data.reactive_import_c_scaled=(unsigned char*)&(energy_scaled.reactive_import_c);
		readHoldingMap.data.reactive_import_total_scaled=(unsigned char*)&(energy_scaled.reactive_import_total);
		
		readHoldingMap.data.reactive_export_a_scaled=(unsigned char*)&(energy_scaled.reactive_export_a);
		readHoldingMap.data.reactive_export_b_scaled=(unsigned char*)&(energy_scaled.reactive_export_b);	
		readHoldingMap.data.reactive_export_c_scaled=(unsigned char*)&(energy_scaled.reactive_export_c);
		readHoldingMap.data.reactive_export_total_scaled=(unsigned char*)&(energy_scaled.reactive_export_total);
		
		readHoldingMap.data.apparent_energy_a_scaled=(unsigned char*)&(energy_scaled.apparent_energy_a);
		readHoldingMap.data.apparent_energy_b_scaled=(unsigned char*)&(energy_scaled.apparent_energy_b);	
		readHoldingMap.data.apparent_energy_c_scaled=(unsigned char*)&(energy_scaled.apparent_energy_c);
		readHoldingMap.data.apparent_energy_total_scaled=(unsigned char*)&(energy_scaled.apparent_energy_total);
		
		readHoldingMap.data.thd_Van=(unsigned char*)&(thd.data.Van);
		readHoldingMap.data.thd_Vbn=(unsigned char*)&(thd.data.Vbn);	
		readHoldingMap.data.thd_Vcn=(unsigned char*)&(thd.data.Vcn);
		
		readHoldingMap.data.thd_Ia=(unsigned char*)&(thd.data.Ia);
		readHoldingMap.data.thd_Ib=(unsigned char*)&(thd.data.Ib);	
		readHoldingMap.data.thd_Ic=(unsigned char*)&(thd.data.Ic);
		
		readHoldingMap.data.Vpn_1=(unsigned char*)&(sym.data.Vpn_1);
		readHoldingMap.data.Vpn_2=(unsigned char*)&(sym.data.Vpn_2);	
		readHoldingMap.data.Vpn_0=(unsigned char*)&(sym.data.Vpn_0);
	
		readHoldingMap.data.I_1=(unsigned char*)&(sym.data.I_1);
		readHoldingMap.data.I_2=(unsigned char*)&(sym.data.I_2);	
		readHoldingMap.data.I_0=(unsigned char*)&(sym.data.I_0);
		
		readHoldingMap.data.UNB_V=(unsigned char*)&(sym.data.UNB_V);
		readHoldingMap.data.UNB_I=(unsigned char*)&(sym.data.UNB_I);	
		
		for(i=0;i<20;i++){
			
		readHoldingMap.data.hVan[i]=(unsigned char*)(&(bin_array[Van][i]));
		readHoldingMap.data.hVbn[i]=(unsigned char*)(&(bin_array[Vbn][i]));
		readHoldingMap.data.hVcn[i]=(unsigned char*)(&(bin_array[Vcn][i]));		

		readHoldingMap.data.hIa[i]=(unsigned char*)(&(bin_array[Ia][i]));
		readHoldingMap.data.hIb[i]=(unsigned char*)(&(bin_array[Ib][i]));
		readHoldingMap.data.hIc[i]=(unsigned char*)(&(bin_array[Ic][i]));
			
		}
		
		
		for(i=0;i<46;i++){
			
		readHoldingMap.data.record[i]=(unsigned char*)(&(rec.word[i]));

		}
	
		
		for(i=0;i<20;i++){
			
		readHoldingMap.data.sVan[i]=(unsigned char*)(&(snap[0][i]));
		readHoldingMap.data.sIa[i]=(unsigned char*)(&(snap[1][i]));
		
		readHoldingMap.data.sVbn[i]=(unsigned char*)(&(snap[2][i]));		
		readHoldingMap.data.sIb[i] =(unsigned char*)(&(snap[3][i]));
		
		readHoldingMap.data.sVcn[i]=(unsigned char*)(&(snap[4][i]));
		readHoldingMap.data.sIc[i]=(unsigned char*)(&(snap[5][i]));
			
		}

	


}