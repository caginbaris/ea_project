#include "menu_definitions.h" 
#include "lcd_definitions.h"
#include "conversion.h"
#include "measurement_definitions.h"
#include "graphing_definitions.h"
#include <stdlib.h>



enum menu_list current_menu=Vpn_true  ;
enum menu_list previous_menu=Vpp_fund ;

enum main_menu_list    main_menu_entry=Active_Energy_main;
enum setting_menu_list setting_menu_entry=setting_output;

struct main_menu_rows     main_lines   ={NULL,NULL,NULL,NULL,NULL,NULL,NULL};
struct setting_menu_rows  setting_lines={NULL,NULL,NULL,NULL,NULL,NULL,NULL};

union display_menu_union MENU={0};
union flashDataUnion flash;
union flashDataUnion flashNew;

enum saveMenus saveMenu=save_option_menu;

/*for main menu listing*/
enum letter_codes_8pt main_menu_entries[][20]={
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},//0
{f,a,z,_,n,o,t,r,_,g,e,r,i,l,i,m,_,_,_,_},//1
{f,a,z,_,f,a,z,_,_,g,e,r,i,l,i,m,_,_,_,_},//2
{h,a,t,_,a,k,i,m,l,a,r,i,_,_,_,_,_,_,_,_},//3
{a,k,t,i,f,_,g,u,c,l,e,r,_,_,_,_,_,_,_,_},//4
{r,e,a,k,t,i,f,_,g,u,c,l,e,r,_,_,_,_,_,_},//5
{g,o,r,u,n,e,n,_,g,u,c,l,e,r,_,_,_,_,_,_},//6
{t,o,p,l,a,m,_,_,g,u,c,l,e,r,_,_,_,_,_,_},//7
{g,u,c,_,f,a,k,t,o,r,l,e,r,i,_,_,_,_,_,_},//8
{g,u,c,_,o,r,a,n,l,a,r,i,_,_,_,_,_,_,_,_},//9	
{a,k,t,i,f,_,e,n,e,r,j,i,_,_,_,_,_,_,_,_},//10
{r,e,a,k,t,i,f,_,e,n,e,r,j,i,_,_,_,_,_,_},//11	
{g,o,r,u,n,e,n,_,e,n,e,r,j,i,_,_,_,_,_,_},//12
{d,a,l,g,a,_,b,i,c,i,m,l,e,r,i,_,_,_,_,_},//13	
{h,a,r,m,o,n,i,k,_,b,a,r,_,g,r,a,f,i,k,_},//14
{h,a,r,m,o,n,i,k,_,b,o,z,u,n,u,m,_,_,_,_},//15
{s,i,m,e,t,r,i,k,_,b,i,l,e,s,e,n,l,e,r,_},//16
{d,e,n,g,e,s,i,z,l,i,k,_,o,r,a,n,l,a,r,i},//17
{a,y,a,r,l,a,r,_,_,_,_,_,_,_,_,_,_,_,_,_},//18	

};


struct display_menu_handles Main_Menu={

	/*null pointer*/NULL,
	/*no data for main*/{a},
	/*no data for main*/{A},
	/*no data for main*/{A},
	/*no data for main*/{A},
	/*symbols*/			{menu_enter,menu_blank,menu_blank,menu_down,menu_up},
	/*no data for main*/{m_},
	/*null pointer*/toMainDetect,
	/*null pointer*/atMainOperation,
};


enum letter_codes_8pt setting_menu_entries[][20]={
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},//0
{g,e,r,i,l,m,_,t,r,a,f,o,_,o,r,a,n,i,_,_},//1
{a,k,i,m,_,g,i,r,i,s,l,e,r,i,_,_,_,_,_,_},//2
{d,i,j,i,t,a,l,_,g,i,r,i,s,_,_,_,_,_,_,_},//3
{d,i,j,i,t,a,l,_,c,i,k,i,s,_,_,_,_,_,_,_},//4
{h,a,b,e,r,l,e,s,m,e,_,_,_,_,_,_,_,_,_,_},//5
{e,n,e,r,j,i,_,s,a,y,a,c,_,r,e,s,e,t,_,_},//6


};


struct display_menu_handles Setting_Menu={

	/*null pointer*/NULL,
	/*no data for main*/{a},
	/*no data for main*/{A},
	/*no data for main*/{A},
	/*no data for main*/{A},
	/*symbols*/			{menu_enter,menu_escape,menu_blank,menu_down,menu_up},
	/*no data for main*/{m_},
	/*null pointer*/toSettingsDetect,
	/*null pointer*/atSettingsOperation,
};




// measurement menus



struct display_menu_handles Vpn_true_Menu= {
	
	/*dynamic data*/ &(trueRMS_scaled.data.Van),
	
	/*title*/      	{v,_,f,a,z,_,n,o,t,r,_,g,e,r,c,e,k,_,_,_,_}, 
	
	/*fist line*/ 	{A,N,__},
	/*second line*/ {B,N,__},
	/*third line*/ 	{C,N,__},
	
	/*symbols*/			{menu_escape,menu_blank,menu_right,menu_down,menu_blank},
	/*menu units*/	{m_V,m_,m_,m_},

	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};


struct display_menu_handles Vpn_fund_Menu= {
	
	/*dynamic data*/ &(fundRMS_scaled.data.Van),
	
	/*title*/      	{v,_,f,a,z,_,n,o,t,r,_,a,n,a,_,_,_,_,_,_,_}, 
	
	/*fist line*/ 	{A,N,__},
	/*second line*/ {B,N,__},
	/*third line*/ 	{C,N,__},
	
	/*symbols*/			{menu_escape,menu_left,menu_blank,menu_down,menu_blank},
	/*menu units*/	{m_V,m_,m_,m_,},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};



struct display_menu_handles Vpp_true_Menu= {
	
	/*dynamic data*/ &(trueRMS_scaled.data.Vab),
	
	/*title*/      	{v,_,_,f,a,z,_,f,a,z,_,g,e,r,c,e,k,_,_,_,_}, 
	
	/*fist line*/ 	{A,B,__},
	/*second line*/ {B,C,__},
	/*third line*/ 	{C,A,__},
	
	/*symbols*/			{menu_escape,menu_blank,menu_right,menu_down,menu_up},
	/*menu units*/	{m_V,m_,m_,m_,},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};


struct display_menu_handles Vpp_fund_Menu= {
	
	/*dynamic data*/ &(fundRMS_scaled.data.Vab),
	
	/*title*/      	{v,_,_,f,a,z,_,f,a,z,_,a,n,a,_,_,_,_,_,_,_}, 
	
	/*fist line*/ 	{A,B,__},
	/*second line*/ {B,C,__},
	/*third line*/ 	{C,A,__},
	
	/*symbols*/			{menu_escape,menu_left,menu_blank,menu_down,menu_up},
	/*menu units*/	{m_V,m_,m_,m_},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};



struct display_menu_handles Ip_true_Menu= {
	
	/*dynamic data*/ &(trueRMS_scaled.data.Ia),
	
	/*title*/      	{a,k,i,m,_,g,e,r,c,e,k,_,r,m,s,_,_,_,_,_,_}, 
	
	/*fist line*/ 	{I,A,__},
	/*second line*/ {I,B,__},
	/*third line*/ 	{I,C,__},
	
	/*symbols*/			{menu_escape,menu_blank,menu_right,menu_down,menu_up},
	/*menu units*/	{m_A,m_,m_,m_,},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};


struct display_menu_handles Ip_fund_Menu= {
	
	/*dynamic data*/ &(fundRMS_scaled.data.Ia),
	
	/*title*/      	{a,k,i,m,_,_,a,n,a,_,_,r,m,s,_,_,_,_,_,_,_} ,
	
	/*fist line*/ 	{I,A,__},
	/*second line*/ {I,B,__},
	/*third line*/ 	{I,C,__},
	
	/*symbols*/			{menu_escape,menu_left,menu_blank,menu_down,menu_up},
	/*menu units*/	{m_A,m_,m_,m_},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};


struct display_menu_handles Active_Power_Menu= {
	
	/*dynamic data*/ &(power_scaled.Power.Pa),
	
	/*title*/      	{a,k,t,i,f,_,g,u,c,l,e,r,_,_,_,_,_,_,_,_,_} ,
	
	/*fist line*/ 	{P,A,__},
	/*second line*/ {P,B,__},
	/*third line*/ 	{P,C,__},
	
	/*symbols*/			{menu_escape,menu_blank,menu_blank,menu_down,menu_up},
	/*menu units*/	{m_W,m_,m_,m_},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};


struct display_menu_handles Reactive_Power_Menu= {
	
	/*dynamic data*/ &(power_scaled.Power.Qa),
	
	/*title*/      	{r,e,a,k,t,i,f,_,g,u,c,l,e,r,_,_,_,_,_,_,_} ,
	
	/*fist line*/ 	{Q,A,__},
	/*second line*/ {Q,B,__},
	/*third line*/ 	{Q,C,__},
	
	/*symbols*/			{menu_escape,menu_blank,menu_blank,menu_down,menu_up},
	/*menu units*/	{m_V,m_A,m_R,m_},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};


struct display_menu_handles Apparent_Power_Menu= {
	
	/*dynamic data*/ &(power_scaled.Power.Sa),
	
	/*title*/      	{g,o,r,u,n,e,n,_,g,u,c,l,e,r,_,_,_,_,_,_,_} ,
	
	/*fist line*/ 	{S,A,__},
	/*second line*/ {S,B,__},
	/*third line*/ 	{S,C,__},
	
	/*symbols*/			{menu_escape,menu_blank,menu_blank,menu_down,menu_up},
	/*menu units*/	{m_V,m_A,m_,m_},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};

struct display_menu_handles Total_Power_Menu= {
	
	/*dynamic data*/ &(power_scaled.Power.Sa),
	
	/*title*/      	{t,o,p,l,a,m,_,_,g,u,c,l,e,r,_,_,_,_,_,_,_} ,
	
	/*fist line*/ 	{P,__,__},
	/*second line*/ {Q,__,__},
	/*third line*/ 	{S,__,__},
	
	/*symbols*/			{menu_escape,menu_blank,menu_blank,menu_down,menu_up},
	/*menu units*/	{m_V,m_A,m_,m_},
	/*static data*/  staticDataTrippleTotalPower,
	/*dynamic data*/ dynamicDataTrippleTotalPower
	

};




struct display_menu_handles Power_Factors_fund_Menu= {
	
	/*dynamic data*/ &(power_iq.Power.PFa),
	
	/*title*/      	{g,u,c,_,f,a,k,t,o,r,l,e,r,i,_,_,_,_,_,_,_} ,
	
	/*fist line*/ 	{A,N,__},
	/*second line*/ {B,N,__},
	/*third line*/ 	{C,N,__},
	
	/*symbols*/			{menu_escape,menu_blank,menu_right,menu_down,menu_up},
	/*menu units*/	{m_percent,m_,m_,m_},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};




struct display_menu_handles Total_Power_Factor_fund_Menu= {
	
	/*dynamic data*/ &(power_iq.Power.PFtotal),
	
	/*title*/      	{t,o,p,l,a,m,_,g,u,c,_,f,a,k,t,o,r,u,_,_,_} ,
	
	/*fist line*/ 	{__,__,__},
	/*second line*/ {__,__,__},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_escape,menu_left,menu_blank,menu_down,menu_up},
	/*menu units*/	{m_percent,m_,m_,m_},
	/*static data*/  staticDataSingle,
	/*dynamic data*/ dynamicDataSingle
	

};


struct display_menu_handles Power_Ratios_Menu= {
	
	/*dynamic data*/ &(power_iq.Power.ratioA),
	
	/*title*/      	{g,u,c,_,o,r,a,n,l,a,r,i,_,q,i,i,p,_,_,_,_} , 
	
	/*fist line*/ 	{A,N,__},
	/*second line*/ {B,N,__},
	/*third line*/ 	{C,N,__},
	
	/*symbols*/			{menu_escape,menu_blank,menu_right,menu_down,menu_up},
	/*menu units*/	{m_percent,m_,m_,m_}, // percent can be added
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};


struct display_menu_handles Total_Power_Ratios_Menu= {
	
	/*dynamic data*/ &(power_iq.Power.ratioTotal),
	
	/*title*/      	{t,o,p,l,a,m,_,q,i,i,p,_,o,r,a,n,i,_,_,_,_},
	
	/*fist line*/ 	{__,__,__},
	/*second line*/ {__,__,__},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_escape,menu_left,menu_blank,menu_down,menu_up},
	/*menu units*/	{m_percent,m_,m_,m_},
	/*static data*/  staticDataSingle,
	/*dynamic data*/ dynamicDataSingle
	

};


struct display_menu_handles Active_Energy_Import_Menu= {
	
	/*dynamic data*/ &(energy_scaled.active_import_a),
	
	/*title*/      	{t,u,k,e,t,i,l,e,n,_,a,k,t,i,f,_,_,_,_,_,_} ,
	
	/*fist line*/ 	{A,N,__},
	/*second line*/ {B,N,__},
	/*third line*/ 	{C,N,__},
	
	/*symbols*/			{menu_escape,menu_blank,menu_right,menu_down,menu_up},
	/*menu units*/	{m_W,m_h,m_,m_},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};


struct display_menu_handles Active_Total_Energy_Import_Menu= {
	
	/*dynamic data*/ &(energy_scaled.active_import_total),
	
	/*title*/      	{t,o,p,l,a,m,_,a,k,t,i,f,_,t,u,k,e,t,i,m,_} ,
	
	/*fist line*/ 	{__,__,__},
	/*second line*/ {__,__,__},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_escape,menu_left,menu_right,menu_down,menu_up},
	/*menu units*/	{m_W,m_h,m_,m_},
	/*static data*/  staticDataSingle,
	/*dynamic data*/ dynamicDataSingle
	

};


struct display_menu_handles Active_Energy_Export_Menu= {
	
	/*dynamic data*/ &(energy_scaled.active_export_a),
	
	/*title*/      	{u,r,e,t,i,l,e,n,_,a,k,t,i,f,_,_,_,_,_,_,_} ,
	
	/*fist line*/ 	{A,N,__},
	/*second line*/ {B,N,__},
	/*third line*/ 	{C,N,__},
	
	/*symbols*/			{menu_escape,menu_left,menu_right,menu_down,menu_up},
	/*menu units*/	{m_W,m_h,m_,m_},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};


struct display_menu_handles Active_Total_Energy_Export_Menu= {
	
	/*dynamic data*/ &(energy_scaled.active_export_total),
	
	/*title*/      	{t,o,p,l,a,m,_,a,k,t,i,f,_,u,r,e,t,i,m,_,_} ,
	
	/*fist line*/ 	{__,__,__},
	/*second line*/ {__,__,__},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_escape,menu_left,menu_blank,menu_down,menu_up},
	/*menu units*/	{m_W,m_h,m_,m_},
	/*static data*/  staticDataSingle,
	/*dynamic data*/ dynamicDataSingle
	

};







struct display_menu_handles Reactive_Energy_Import_Menu= {
	
	/*dynamic data*/ &(energy_scaled.reactive_import_a),
	
	/*title*/      	{t,u,k,e,t,i,l,e,n,_,r,e,a,k,t,i,f,_,_,_,_} ,
	
	/*fist line*/ 	{A,N,__},
	/*second line*/ {B,N,__},
	/*third line*/ 	{C,N,__},
	
	/*symbols*/			{menu_escape,menu_blank,menu_right,menu_down,menu_up},
	/*menu units*/	{m_V,m_A,m_R,m_h},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};


struct display_menu_handles Reactive_Total_Energy_Import_Menu= {
	
	/*dynamic data*/ &(energy_scaled.reactive_import_total),
	
	/*title*/      	{t,o,t,a,l,_,r,e,a,k,t,i,f,_,t,u,k,e,t,i,m} ,
	
	/*fist line*/ 	{__,__,__},
	/*second line*/ {__,__,__},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_escape,menu_left,menu_right,menu_down,menu_up},
	/*menu units*/	{m_V,m_A,m_R,m_h},
	/*static data*/  staticDataSingle,
	/*dynamic data*/ dynamicDataSingle
	

};


struct display_menu_handles Reactive_Energy_Export_Menu= {
	
	/*dynamic data*/ &(energy_scaled.reactive_export_a),
	
	/*title*/      	{u,r,e,t,i,l,e,n,_,r,e,a,k,t,i,f,_,_,_,_,_} ,
	
	/*fist line*/ 	{A,N,__},
	/*second line*/ {B,N,__},
	/*third line*/ 	{C,N,__},
	
	/*symbols*/			{menu_escape,menu_left,menu_right,menu_down,menu_up},
	/*menu units*/	{m_V,m_A,m_R,m_h},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};

struct display_menu_handles Reactive_Total_Energy_Export_Menu= {
	
	/*dynamic data*/ &(energy_scaled.reactive_export_total),
	
	/*title*/      	{t,o,t,a,l,_,r,e,a,k,t,i,f,_,u,r,e,t,i,m,_} ,
	
	/*fist line*/ 	{__,__,__},
	/*second line*/ {__,__,__},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_escape,menu_left,menu_blank,menu_down,menu_up},
	/*menu units*/	{m_V,m_A,m_R,m_h},
	/*static data*/  staticDataSingle,
	/*dynamic data*/ dynamicDataSingle
	

};

struct display_menu_handles Apparent_Energy_Menu= {
	
	/*dynamic data*/ &(energy_scaled.apparent_energy_a),
	
	/*title*/      	{g,o,r,u,n,e,n,_,e,n,e,r,j,i,_,_,_,_,_,_,_} ,
	
	/*fist line*/ 	{A,N,__},
	/*second line*/ {B,N,__},
	/*third line*/ 	{C,N,__},
	
	/*symbols*/			{menu_escape,menu_blank,menu_right,menu_down,menu_up},
	/*menu units*/	{m_V,m_A,m_h,m_},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};


struct display_menu_handles Apparent_Total_Energy_Menu= {
	
	/*dynamic data*/ &(energy_scaled.reactive_export_total),
	
	/*title*/      	{t,o,t,a,l,_,g,o,r,u,n,e,n,_,e,n,e,r,j,i,_} ,
	
	/*fist line*/ 	{__,__,__},
	/*second line*/ {__,__,__},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_escape,menu_left,menu_blank,menu_down,menu_up},
	/*menu units*/	{m_V,m_A,m_h,m_},
	/*static data*/  staticDataSingle,
	/*dynamic data*/ dynamicDataSingle
	

};


struct display_menu_handles Scope_Van_Menu= {
	
	/*dynamic data*/ &(AN.data.Van),
	
	/*title*/      	{v,a,n} ,
	
	/*fist line*/ 	{A,__,__},
	/*second line*/ {__,__,__},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_escape,menu_blank,menu_right,menu_blank,menu_blank},
	/*menu units*/	{m_,m_,m_,m_},
	/*static data*/  graphBaseLining,
	/*dynamic data*/ graphDataTransfer
	

};


struct display_menu_handles Scope_Vbn_Menu= {
	
	/*dynamic data*/ &(AN.data.Vbn),
	
	/*title*/      	{v,b,n} ,
	
	/*fist line*/ 	{B,__,__},
	/*second line*/ {__,__,__},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_escape,menu_left,menu_right,menu_blank,menu_blank},
	/*menu units*/	{m_,m_,m_,m_},
	/*static data*/  graphBaseLining,
	/*dynamic data*/ graphDataTransfer
	

};


struct display_menu_handles Scope_Vcn_Menu= {
	
	/*dynamic data*/ &(AN.data.Vcn),
	
	/*title*/      	{v,c,n} ,
	
	/*fist line*/ 	{C,__,__},
	/*second line*/ {__,__,__},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_escape,menu_left,menu_right,menu_blank,menu_blank},
	/*menu units*/	{m_,m_,m_,m_},
	/*static data*/  graphBaseLining,
	/*dynamic data*/ graphDataTransfer
	

};


struct display_menu_handles Scope_Ia_Menu= {
	
	/*dynamic data*/ &(AN.data.Ia),
	
	/*title*/      	{i,a,_} ,
	
	/*fist line*/ 	{D,__,__},
	/*second line*/ {__,__,__},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_escape,menu_left,menu_right,menu_blank,menu_blank},
	/*menu units*/	{m_,m_,m_,m_},
	/*static data*/  graphBaseLining,
	/*dynamic data*/ graphDataTransfer
	

};


struct display_menu_handles Scope_Ib_Menu= {
	
	/*dynamic data*/ &(AN.data.Ib),
	
	/*title*/      	{i,b,_} ,
	
	/*fist line*/ 	{E,__,__},
	/*second line*/ {__,__,__},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_escape,menu_left,menu_right,menu_blank,menu_blank},
	/*menu units*/	{m_,m_,m_,m_},
	/*static data*/  graphBaseLining,
	/*dynamic data*/ graphDataTransfer
	

};


struct display_menu_handles Scope_Ic_Menu= {
	
	/*dynamic data*/ &(AN.data.Ic),
	
	/*title*/      	{i,c,_} ,
	
	/*fist line*/ 	{F,__,__},
	/*second line*/ {__,__,__},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_escape,menu_left,menu_blank,menu_blank,menu_blank},
	/*menu units*/	{m_,m_,m_,m_},
	/*static data*/  graphBaseLining,
	/*dynamic data*/ graphDataTransfer
	

};

struct display_menu_handles Harmonics_Van_Menu= {
	
	/*dynamic data*/ &bin_array[Van][0],
	
	/*title*/      	{v,a,n,_,h,a,r,m,o,n,i,k,l,e,r,_,_,_,_,_,_} ,
	
	/*fist line*/ 	{__,__,__},
	/*second line*/ {__,__,__},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_escape,menu_left,menu_right,menu_down,menu_blank},
	/*menu units*/	{m_percent,m_,m_,m_},
	/*static data*/  harmonicBaseLine,
	/*dynamic data*/ harmonicDataTransfer
	

};


struct display_menu_handles Harmonics_Vbn_Menu= {
	
	/*dynamic data*/ &bin_array[Vbn][0],
	
	/*title*/      	{v,b,n,_,h,a,r,m,o,n,i,k,l,e,r,_,_,_,_,_,_} ,
	
	/*fist line*/ 	{__,__,__},
	/*second line*/ {__,__,__},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_escape,menu_left,menu_right,menu_down,menu_up},
	/*menu units*/	{m_percent,m_,m_,m_},
	/*static data*/  harmonicBaseLine,
	/*dynamic data*/ harmonicDataTransfer
	

};


struct display_menu_handles Harmonics_Vcn_Menu= {
	
	/*dynamic data*/ &bin_array[Vcn][0],
	
	/*title*/      	{v,c,n,_,h,a,r,m,o,n,i,k,l,e,r,_,_,_,_,_,_} ,
	
	/*fist line*/ 	{__,__,__},
	/*second line*/ {__,__,__},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_escape,menu_left,menu_right,menu_down,menu_up},
	/*menu units*/	{m_percent,m_,m_,m_},
	/*static data*/  harmonicBaseLine,
	/*dynamic data*/ harmonicDataTransfer
	

};



struct display_menu_handles Harmonics_Ia_Menu= {
	
	/*dynamic data*/ &bin_array[Ia][0],
	
	/*title*/      	{i,a,_,_,h,a,r,m,o,n,i,k,l,e,r,_,_,_,_,_,_} ,
	
	/*fist line*/ 	{__,__,__},
	/*second line*/ {__,__,__},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_escape,menu_left,menu_right,menu_down,menu_up},
	/*menu units*/	{m_percent,m_,m_,m_},
	/*static data*/  harmonicBaseLine,
	/*dynamic data*/ harmonicDataTransfer
	

};


struct display_menu_handles Harmonics_Ib_Menu= {
	
	/*dynamic data*/ &bin_array[Ib][0],
	
	/*title*/      	{i,b,_,_,h,a,r,m,o,n,i,k,l,e,r,_,_,_,_,_,_} ,
	
	/*fist line*/ 	{__,__,__},
	/*second line*/ {__,__,__},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_escape,menu_left,menu_right,menu_down,menu_up},
	/*menu units*/	{m_percent,m_,m_,m_},
	/*static data*/  harmonicBaseLine,
	/*dynamic data*/ harmonicDataTransfer
	

};


struct display_menu_handles Harmonics_Ic_Menu= {
	
	/*dynamic data*/ &bin_array[Ic][0],
	
	/*title*/      	{i,c,_,_,h,a,r,m,o,n,i,k,l,e,r,_,_,_,_,_,_} ,
	
	/*fist line*/ 	{__,__,__},
	/*second line*/ {__,__,__},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_escape,menu_left,menu_right,menu_blank,menu_up},
	/*menu units*/	{m_percent,m_,m_,m_},
	/*static data*/  harmonicBaseLine,
	/*dynamic data*/ harmonicDataTransfer
	

};


struct display_menu_handles thd_Vpn_Menu= {
	
	/*dynamic data*/ &(thd.data.Van),
	
	/*title*/      	{v,_,h,a,r,m,o,n,i,k,_,b,o,z,u,n,u,m,_,_,_} ,
	
	/*fist line*/ 	{A,N,__},
	/*second line*/ {B,N,__},
	/*third line*/ 	{C,N,__},
	
	/*symbols*/			{menu_escape,menu_blank,menu_right,menu_down,menu_up},
	/*menu units*/	{m_percent,m_,m_,m_},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};


struct display_menu_handles thd_I_Menu= {
	
	/*dynamic data*/ &(thd.data.Ia),
	
	/*title*/      	{i,p,_,_,h,a,r,m,o,n,i,k,_,b,o,z,u,n,u,m,_} ,
	
	/*fist line*/ 	{I,A,__},
	/*second line*/ {I,B,__},
	/*third line*/ 	{I,C,__},
	
	/*symbols*/			{menu_escape,menu_left,menu_blank,menu_down,menu_up},
	/*menu units*/	{m_percent,m_,m_,m_},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};

struct display_menu_handles sym_Vpn_Menu= {
	
	/*dynamic data*/ &(sym_scaled.data.Vpn_1),
	
	/*title*/      	{v,p,n,_,s,i,m,e,t,r,i,k,_,b,i,l,e,s,e,n,_} ,
	
	/*fist line*/ 	{P,__,__},
	/*second line*/ {N,__,__},
	/*third line*/ 	{O,__,__},
	
	/*symbols*/			{menu_escape,menu_blank,menu_right,menu_down,menu_up},
	/*menu units*/	{m_A,m_,m_,m_},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};


struct display_menu_handles sym_I_Menu= {
	
	/*dynamic data*/ &(sym_scaled.data.I_1),
	
	/*title*/      	{a,k,i,m,_,s,i,m,e,t,r,i,k,_,b,i,l,e,s,e,n} ,
	
	/*fist line*/ 	{P,__,__},
	/*second line*/ {N,__,__},
	/*third line*/ 	{O,__,__},
	
	/*symbols*/			{menu_escape,menu_left,menu_blank,menu_down,menu_up},
	/*menu units*/	{m_A,m_,m_,m_},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};

struct display_menu_handles UNB_V_Menu= {
	
	/*dynamic data*/ &(sym.data.UNB_V),
	
	/*title*/      	{v,p,n,_,d,e,n,g,e,s,i,z,l,i,k,_,_,_,_,_,_} ,
	
	/*fist line*/ 	{__,__,__},
	/*second line*/ {__,__,__},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_escape,menu_blank,menu_right,menu_blank,menu_up},
	/*menu units*/	{m_percent,m_,m_,m_},
	/*static data*/  staticDataSingle,
	/*dynamic data*/ dynamicDataSingle
	

};


struct display_menu_handles UNB_I_Menu= {
	
	/*dynamic data*/ &(sym.data.UNB_I),
	
	/*title*/      	{a,k,i,m,_,d,e,n,g,e,s,i,z,l,i,k,_,_,_,_,_} ,
	
	/*fist line*/ 	{__,__,__},
	/*second line*/ {__,__,__},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_escape,menu_left,menu_blank,menu_blank,menu_up},
	/*menu units*/	{m_percent,m_,m_,m_},
	/*static data*/  staticDataSingle,
	/*dynamic data*/ dynamicDataSingle
	

};


struct display_menu_handles set_VT_Menu= {
	
	/*dynamic data*/ NULL,
	
	/*title*/      	{g,e,r,i,l,i,m,_,t,u,r,_,o,r,a,n,l,a,r,i,_} ,
	
	/*fist line*/ 	{__,__,__},
	/*second line*/ {__,__,__},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_enter,menu_plus,menu_minus,menu_right,menu_escape},
	/*menu units*/	{m_,m_,m_,m_},
	/*static data*/  staticData_VT,
	/*dynamic data*/ dynamicData_VT
	

};


struct display_menu_handles set_CT_Menu= {
	
	/*dynamic data*/ NULL,
	
	/*title*/      	{a,k,i,m,_,g,i,r,i,s,_,a,y,a,r,l,a,r,i,_,_} ,
	
	/*fist line*/ 	{__,__,__},
	/*second line*/ {__,__,__},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_enter,menu_plus,menu_minus,menu_right,menu_escape},
	/*menu units*/	{m_,m_,m_,m_},
	/*static data*/  staticData_CT,
	/*dynamic data*/ dynamicData_CT
	

};


struct display_menu_handles set_input_Menu= {
	
	/*dynamic data*/ NULL,
	
	/*title*/      	{d,i,j,i,t,a,l,_,g,i,r,i,s,_,i,s,l,e,v,i,_} ,
	
	/*fist line*/ 	{__,__,__},
	/*second line*/ {__,__,__},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_enter,menu_alter,menu_right,menu_blank,menu_escape},
	/*menu units*/	{m_,m_,m_,m_},
	/*static data*/  staticData_input,
	/*dynamic data*/ dynamicData_input
	

};



struct display_menu_handles set_output_Menu= {
	
	/*dynamic data*/ NULL,
	
	/*title*/      	{d,i,j,i,t,a,l,_,c,i,k,i,s,_,i,s,l,e,v,i,_} ,
	
	/*fist line*/ 	{__,__,__},
	/*second line*/ {__,__,__},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_enter,menu_alter,menu_plus,menu_right,menu_escape},
	/*menu units*/	{m_,m_,m_,m_},
	/*static data*/  staticData_output,
	/*dynamic data*/ dynamicData_output
	

};



struct display_menu_handles set_comm_Menu= {
	
	/*dynamic data*/ NULL,
	
	/*title*/      	{m,o,d,b,u,s,_,d,e,g,i,s,k,e,n,l,e,r,i,_,_} ,
	
	/*fist line*/ 	{__,__,__},
	/*second line*/ {__,__,__},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_enter,menu_plus,menu_minus,menu_right,menu_escape},
	/*menu units*/	{m_,m_,m_,m_},
	/*static data*/  staticData_comm,
	/*dynamic data*/ dynamicData_comm
	

};


struct display_menu_handles set_energy_reset_Menu= {
	
	/*dynamic data*/ NULL,
	
	/*title*/      	{e,n,e,r,j,i,_,s,a,y,a,c,_,r,e,s,e,t,_,_,_} ,
	
	/*fist line*/ 	{__,__,__},
	/*second line*/ {__,__,__},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_blank,menu_blank,menu_tick,menu_cross,menu_blank},
	/*menu units*/	{m_,m_,m_,m_},
	/*static data*/  staticData_reset,
	/*dynamic data*/ dynamicData_reset
	

};



const struct MENU_TRANSITION menu_transition[]={
	
	//	current menu------------input-----------next menu
	
		{	Vpn_true,								right_pressed,	Vpn_fund},//1
		{	Vpn_true,								down_pressed,		Vpp_true},
		{	Vpn_true,								enter_pressed,	main_menu},
		
		{	Vpn_fund,								left_pressed,		Vpn_true},//4
		{	Vpn_fund,								down_pressed,		Vpp_fund},
		{	Vpn_fund,								enter_pressed,	main_menu},
		
		{	Vpp_true,								right_pressed,	Vpp_fund},//7
		{	Vpp_true,								down_pressed,		Ip_true},
		{	Vpp_true,								up_pressed,			Vpn_true},
		{	Vpp_true,								enter_pressed,	main_menu},
		
		{	Vpp_fund,								left_pressed,		Vpp_true},//11
		{	Vpp_fund,								down_pressed,		Ip_fund},
		{	Vpp_fund,								up_pressed,		  Vpn_fund},
		{	Vpp_fund,								enter_pressed,	main_menu},
		
		{	Ip_true,								right_pressed,	Ip_fund},//15
		{	Ip_true,								up_pressed,			Vpp_true},
		{	Ip_true,								down_pressed,		Active_Power},
		{	Ip_true,								enter_pressed,	main_menu},
		
		{	Ip_fund,								left_pressed,		Ip_true},//19
		{	Ip_fund,								up_pressed,			Vpp_fund},
		{	Ip_fund,								down_pressed,		Active_Power},
		{	Ip_fund,								enter_pressed,	main_menu},
		
		{	Active_Power,						up_pressed,			Ip_true},//22
		{	Active_Power,						down_pressed,		Reactive_Power},
		{	Active_Power,						enter_pressed,	main_menu},
		
		{	Reactive_Power,					up_pressed,			Active_Power},//25
		{	Reactive_Power,					down_pressed,		Apparent_Power},
		{	Reactive_Power,					enter_pressed,	main_menu},
		
		{	Apparent_Power,					up_pressed,			Reactive_Power},//28
		{	Apparent_Power,					down_pressed,		Total_Power},
		{	Apparent_Power,					enter_pressed,	main_menu},
		
		{	Total_Power,						up_pressed,			Apparent_Power},//31
		{	Total_Power,						down_pressed,		Power_Factors_fund},
		{	Total_Power,						enter_pressed,	main_menu},
		
		{	Power_Factors_fund,			right_pressed,	Total_Power_Factor_fund},//34
		{	Power_Factors_fund,			up_pressed,			Total_Power},
		{	Power_Factors_fund,			down_pressed,		Power_Ratios},
		{	Power_Factors_fund,			enter_pressed,	main_menu},
		
		{	Total_Power_Factor_fund,up_pressed,			Total_Power},//38
		{	Total_Power_Factor_fund,down_pressed,		Power_Ratios},
		{	Total_Power_Factor_fund,left_pressed,		Power_Factors_fund},
		{	Total_Power_Factor_fund,enter_pressed,	main_menu},
		
		{	Power_Ratios,up_pressed,		Power_Factors_fund},//42
		{	Power_Ratios,down_pressed,	Active_Energy_import },
		{	Power_Ratios,right_pressed,	Total_Power_Ratios },
		{	Power_Ratios,enter_pressed,	main_menu},
		
		{	Total_Power_Ratios,up_pressed,		Power_Factors_fund},//46
		{	Total_Power_Ratios,down_pressed,	Active_Energy_import },
		{	Total_Power_Ratios,left_pressed,	Power_Ratios },
		{	Total_Power_Ratios,enter_pressed,	main_menu},
		
		{	Active_Energy_import,up_pressed,		Power_Ratios},//50
		{	Active_Energy_import,down_pressed,	Reactive_Energy_import },
		{	Active_Energy_import,right_pressed,	Active_Energy_Total_import },
		{	Active_Energy_import,enter_pressed,	main_menu},
		
		{	Active_Energy_Total_import,up_pressed,		Power_Ratios},//54
		{	Active_Energy_Total_import,down_pressed,	Reactive_Energy_import },
		{	Active_Energy_Total_import,right_pressed,	Active_Energy_export },
		{	Active_Energy_Total_import,left_pressed,	Active_Energy_import },
		{	Active_Energy_Total_import,enter_pressed,	main_menu},
		
		{	Active_Energy_export,up_pressed,		Power_Ratios},//59
		{	Active_Energy_export,down_pressed,	Reactive_Energy_export },
		{	Active_Energy_export,left_pressed,	Active_Energy_Total_import },
		{	Active_Energy_export,right_pressed,	Active_Energy_Total_export },
		{	Active_Energy_export,enter_pressed,	main_menu},
		
		{	Active_Energy_Total_export,up_pressed,		Power_Ratios},//64
		{	Active_Energy_Total_export,down_pressed,	Reactive_Energy_import },
		{	Active_Energy_Total_export,left_pressed,	Active_Energy_export },
		{	Active_Energy_Total_export,enter_pressed,	main_menu},
		
		
		
		{	Reactive_Energy_import,up_pressed,	  Active_Energy_import},//68
		{	Reactive_Energy_import,down_pressed,  Apparent_Energy },
		{	Reactive_Energy_import,right_pressed,	Reactive_Energy_Total_import },
		{	Reactive_Energy_import,enter_pressed,	main_menu},
		
		{	Reactive_Energy_Total_import,up_pressed,	  Active_Energy_import},//72
		{	Reactive_Energy_Total_import,down_pressed,  Apparent_Energy },
		{	Reactive_Energy_Total_import,right_pressed,	Reactive_Energy_export },
		{	Reactive_Energy_Total_import,left_pressed,	Reactive_Energy_import },
		{	Reactive_Energy_Total_import,enter_pressed,	main_menu},
		
		{	Reactive_Energy_export,up_pressed,	  Active_Energy_import},//77
		{	Reactive_Energy_export,down_pressed,  Apparent_Energy },
		{	Reactive_Energy_export,right_pressed,	Reactive_Energy_Total_export },
		{	Reactive_Energy_export,left_pressed,	Reactive_Energy_Total_import },
		{	Reactive_Energy_export,enter_pressed,	main_menu},
		
		{	Reactive_Energy_Total_export,up_pressed,	  Active_Energy_import},//82
		{	Reactive_Energy_Total_export,down_pressed,  Apparent_Energy },
		{	Reactive_Energy_Total_export,left_pressed,	Reactive_Energy_export },
		{	Reactive_Energy_Total_export,enter_pressed,	main_menu},
		
	
		{	Apparent_Energy,	up_pressed,			Reactive_Energy_import},//86
		{	Apparent_Energy,	down_pressed,		Scope_Van},
		{	Apparent_Energy,	right_pressed,	Apparent_Energy_Total},
		{	Apparent_Energy,	enter_pressed,	main_menu},
		
		{	Apparent_Energy_Total,	up_pressed,			Reactive_Energy_import},//90
		{	Apparent_Energy_Total,	down_pressed,		Scope_Van},
		{	Apparent_Energy_Total,	left_pressed,		Apparent_Energy},
		{	Apparent_Energy_Total,	enter_pressed,	main_menu},
		
		
		
		
		//{	Scope_Van,up_pressed,Apparent_Energy},
		{	Scope_Van,right_pressed,Scope_Vbn},//94
		{	Scope_Van,enter_pressed,main_menu},
		
		
		//{	Scope_Vbn,up_pressed,Apparent_Energy},
		{	Scope_Vbn,right_pressed,Scope_Vcn},//96
		{	Scope_Vbn,left_pressed,Scope_Van},
		{	Scope_Vbn,enter_pressed,main_menu},
		
		
		//{	Scope_Vcn,up_pressed,Apparent_Energy},
		{	Scope_Vcn,right_pressed,Scope_Ia},//99
		{	Scope_Vcn,left_pressed,Scope_Vbn},
		{	Scope_Vcn,enter_pressed,main_menu},
		
		
		//{	Scope_Ia,up_pressed,Apparent_Energy},
		{	Scope_Ia,right_pressed,Scope_Ib},//102
		{	Scope_Ia,left_pressed,Scope_Vcn},
		{	Scope_Ia,enter_pressed,main_menu},
		
		
		//{	Scope_Ib,up_pressed,Apparent_Energy},
		{	Scope_Ib,right_pressed,Scope_Ic},//105
		{	Scope_Ib,left_pressed,Scope_Ia},
		{	Scope_Ib,enter_pressed,main_menu},
		
		
		//{	Scope_Ic,up_pressed,Apparent_Energy},
		{	Scope_Ic,left_pressed,Scope_Ib},//109
		{	Scope_Ic,enter_pressed,main_menu},
		
		
		/*HARMONIC START*/
		
		{Harmonics_Van,down_pressed,Harmonics_Vbn},//111
		{Harmonics_Vbn,down_pressed,Harmonics_Vcn},
		{Harmonics_Vcn,down_pressed,Harmonics_Ia},
		{Harmonics_Ia, down_pressed,Harmonics_Ib},
		{Harmonics_Ib, down_pressed,Harmonics_Ic},
		
		{Harmonics_Vbn,up_pressed,Harmonics_Van},
		{Harmonics_Vcn,up_pressed,Harmonics_Vbn},
		{Harmonics_Ia, up_pressed,Harmonics_Vcn},
		{Harmonics_Ib, up_pressed,Harmonics_Ia},
		{Harmonics_Ic, up_pressed,Harmonics_Ib},
		
		{Harmonics_Van,enter_pressed,main_menu},
		{Harmonics_Vbn,enter_pressed,main_menu},
		{Harmonics_Vcn,enter_pressed,main_menu},
		{Harmonics_Ia,enter_pressed,main_menu},
		{Harmonics_Ib,enter_pressed,main_menu},
		{Harmonics_Ic,enter_pressed,main_menu},
		
		/*HARMONICS END*/
		
		{thd_Vpn,up_pressed,Harmonics_Van},//127
		{thd_Vpn,right_pressed,thd_I},
		{thd_Vpn,down_pressed,sym_Vpn},
		{thd_Vpn,enter_pressed,main_menu},
		
		{thd_I,up_pressed,Harmonics_Van},//131
		{thd_I,left_pressed,thd_Vpn},
		{thd_I,down_pressed,sym_Vpn},
		{thd_I,enter_pressed,main_menu},
		
		{sym_Vpn,up_pressed,thd_Vpn},//135
		{sym_Vpn,right_pressed,sym_I},
		{sym_Vpn,down_pressed,unb_Vpn},
		{sym_Vpn,enter_pressed,main_menu},
		
		{sym_I,up_pressed,thd_Vpn},//139
		{sym_I,left_pressed,sym_Vpn},
		{sym_I,down_pressed,unb_Vpn},
		{sym_I,enter_pressed,main_menu},
		
		{unb_Vpn,up_pressed,sym_Vpn},//143
		{unb_Vpn,right_pressed,unb_I},
		{unb_Vpn,enter_pressed,main_menu},
	
		{unb_I,up_pressed,sym_Vpn},//146
		{unb_I,left_pressed,unb_Vpn},
		{unb_I,enter_pressed,main_menu},
		
		
		
		
		
		
		
		

};






void init_Menu(){
	
	MENU.handle.main_menu=Main_Menu;
	MENU.handle.Vpn_true=	Vpn_true_Menu;
	MENU.handle.Vpn_fund=	Vpn_fund_Menu;
	MENU.handle.Vpp_true=	Vpp_true_Menu;
	MENU.handle.Vpp_fund=	Vpp_fund_Menu;
	MENU.handle.Ip_true=	Ip_true_Menu;
	MENU.handle.Ip_fund=	Ip_fund_Menu;
	MENU.handle.Active_Power=Active_Power_Menu;
	MENU.handle.Reactive_Power=Reactive_Power_Menu;
	MENU.handle.Apparent_Power=Apparent_Power_Menu;
	MENU.handle.Total_Power=Total_Power_Menu;
	MENU.handle.Power_Factors_fund=Power_Factors_fund_Menu;
	MENU.handle.Total_Power_Factor_fund=Total_Power_Factor_fund_Menu;
	MENU.handle.Power_Ratios=Power_Ratios_Menu;
	MENU.handle.Total_Power_Ratios=Total_Power_Ratios_Menu;
	MENU.handle.Active_Energy_Import=Active_Energy_Import_Menu;
	MENU.handle.Active_Total_Energy_Import=Active_Total_Energy_Import_Menu;
	MENU.handle.Active_Energy_Export=Active_Energy_Export_Menu;
	MENU.handle.Active_Total_Energy_Export=Active_Total_Energy_Export_Menu;
	MENU.handle.Reactive_Energy_Import=Reactive_Energy_Import_Menu;
	MENU.handle.Reactive_Total_Energy_Import=Reactive_Total_Energy_Import_Menu;
	MENU.handle.Reactive_Energy_Export=Reactive_Energy_Export_Menu;
	MENU.handle.Reactive_Total_Energy_Export=Reactive_Total_Energy_Export_Menu;
	MENU.handle.Apparent_Energy=Apparent_Energy_Menu;
	MENU.handle.Apparent_Total_Energy=Apparent_Total_Energy_Menu;
	MENU.handle.Scope_Van=Scope_Van_Menu;
	MENU.handle.Scope_Vbn=Scope_Vbn_Menu;
	MENU.handle.Scope_Vcn=Scope_Vcn_Menu;
	MENU.handle.Scope_Ia=Scope_Ia_Menu;
	MENU.handle.Scope_Ib=Scope_Ib_Menu;
	MENU.handle.Scope_Ic=Scope_Ic_Menu;
	MENU.handle.Harmonics_Van=Harmonics_Van_Menu;
	MENU.handle.Harmonics_Vbn=Harmonics_Vbn_Menu;
	MENU.handle.Harmonics_Vcn=Harmonics_Vcn_Menu;
	MENU.handle.Harmonics_Ia=Harmonics_Ia_Menu;
	MENU.handle.Harmonics_Ib=Harmonics_Ib_Menu;
	MENU.handle.Harmonics_Ic=Harmonics_Ic_Menu;
	MENU.handle.thd_Vpn=thd_Vpn_Menu;
	MENU.handle.thd_I=thd_I_Menu;
	MENU.handle.sym_Vpn=sym_Vpn_Menu;
	MENU.handle.sym_I=sym_I_Menu;
	MENU.handle.UNB_V=UNB_V_Menu;
	MENU.handle.UNB_I=UNB_I_Menu;
	MENU.handle.settings=Setting_Menu;
	MENU.handle.settings_VT=set_VT_Menu;
	MENU.handle.settings_CT=set_CT_Menu;
	MENU.handle.settings_input=set_input_Menu;
	MENU.handle.settings_output=set_output_Menu;
	MENU.handle.settings_comm=set_comm_Menu;
	MENU.handle.settings_energy_reset=set_energy_reset_Menu;
	
}






