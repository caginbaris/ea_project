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
		
		
		readHoldingMap.data.Pa=(unsigned char*)&(power_iq.Power.Pa);
		readHoldingMap.data.Pb=(unsigned char*)&(power_iq.Power.Pb);	
		readHoldingMap.data.Pc=(unsigned char*)&(power_iq.Power.Pc);
		
		readHoldingMap.data.Qa=(unsigned char*)&(power_iq.Power.Qa);
		readHoldingMap.data.Qb=(unsigned char*)&(power_iq.Power.Qb);	
		readHoldingMap.data.Qc=(unsigned char*)&(power_iq.Power.Qc);
		
		readHoldingMap.data.Sa=(unsigned char*)&(power_iq.Power.Sa);
		readHoldingMap.data.Sb=(unsigned char*)&(power_iq.Power.Sb);	
		readHoldingMap.data.Sc=(unsigned char*)&(power_iq.Power.Sc);
		
		readHoldingMap.data.Ptotal=(unsigned char*)&(power_iq.Power.Ptotal);
		readHoldingMap.data.Qtotal=(unsigned char*)&(power_iq.Power.Qtotal);	
		readHoldingMap.data.Stotal=(unsigned char*)&(power_iq.Power.Stotal);
		
		readHoldingMap.data.PFa=(unsigned char*)&(power_iq.Power.PFa);
		readHoldingMap.data.PFb=(unsigned char*)&(power_iq.Power.PFb);	
		readHoldingMap.data.PFc=(unsigned char*)&(power_iq.Power.PFc);
		readHoldingMap.data.PFtotal=(unsigned char*)&(power_iq.Power.PFtotal);
		
		readHoldingMap.data.ratioA=(unsigned char*)&(power_iq.Power.ratioA);
		readHoldingMap.data.ratioA=(unsigned char*)&(power_iq.Power.ratioB);	
		readHoldingMap.data.ratioA=(unsigned char*)&(power_iq.Power.ratioC);
		readHoldingMap.data.ratioTotal=(unsigned char*)&(power_iq.Power.ratioTotal);
		
		readHoldingMap.data.active_import_a_scaled=(unsigned char*)&(energy.active_import_a_scaled);
		readHoldingMap.data.active_import_b_scaled=(unsigned char*)&(energy.active_import_b_scaled);	
		readHoldingMap.data.active_import_c_scaled=(unsigned char*)&(energy.active_import_c_scaled);
		readHoldingMap.data.active_import_total_scaled=(unsigned char*)&(energy.active_import_total_scaled);
		
		readHoldingMap.data.active_export_a_scaled=(unsigned char*)&(energy.active_import_a_scaled);
		readHoldingMap.data.active_export_b_scaled=(unsigned char*)&(energy.active_import_b_scaled);	
		readHoldingMap.data.active_export_c_scaled=(unsigned char*)&(energy.active_import_c_scaled);
		readHoldingMap.data.active_export_total_scaled=(unsigned char*)&(energy.active_import_total_scaled);
		
		readHoldingMap.data.reactive_import_a_scaled=(unsigned char*)&(energy.reactive_import_a_scaled);
		readHoldingMap.data.reactive_import_b_scaled=(unsigned char*)&(energy.reactive_import_b_scaled);	
		readHoldingMap.data.reactive_import_c_scaled=(unsigned char*)&(energy.reactive_import_c_scaled);
		readHoldingMap.data.reactive_import_total_scaled=(unsigned char*)&(energy.reactive_import_total_scaled);
		
		readHoldingMap.data.reactive_export_a_scaled=(unsigned char*)&(energy.reactive_export_a_scaled);
		readHoldingMap.data.reactive_export_b_scaled=(unsigned char*)&(energy.reactive_export_b_scaled);	
		readHoldingMap.data.reactive_export_c_scaled=(unsigned char*)&(energy.reactive_export_c_scaled);
		readHoldingMap.data.reactive_export_total_scaled=(unsigned char*)&(energy.reactive_export_total_scaled);
		
		readHoldingMap.data.apparent_energy_a_scaled=(unsigned char*)&(energy.apparent_energy_a_scaled);
		readHoldingMap.data.apparent_energy_b_scaled=(unsigned char*)&(energy.apparent_energy_b_scaled);	
		readHoldingMap.data.apparent_energy_c_scaled=(unsigned char*)&(energy.apparent_energy_c_scaled);
		readHoldingMap.data.apparent_energy_total_scaled=(unsigned char*)&(energy.apparent_energy_total_scaled);
		
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

	


}