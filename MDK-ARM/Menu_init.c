#include "menu_definitions.h" 
#include "lcd_definitions.h"
#include "conversion.h"
#include "measurement_definitions.h"
#include "graphing_definitions.h"
#include <stdlib.h>







enum menu_list current_menu=Scope;
enum menu_list previous_menu=Vpp_true;//cau should be different at startup wrt current menu
enum main_menu_list main_menu_entry=Vpp_main;
//volatile enum main_menu_list cursor=Vpp_main;
struct main_menu_rows main_lines={NULL,NULL,NULL,NULL,NULL,NULL,NULL};
union display_menu_union MENU={0};

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
{t,o,p,l,a,m,_,g,u,c,_,f,a,k,t,o,r,u,_,_},//9
{g,u,c,_,o,r,a,n,l,a,r,i,_,_,_,_,_,_,_,_},//10	
{t,o,p,l,a,m,_,g,u,c,_,o,r,a,n,l,a,r,i,_},//11
{a,k,t,i,f,_,e,n,e,r,j,i,_,_,_,_,_,_,_,_},//12
{r,e,a,k,t,i,f,_,e,n,e,r,j,i,_,_,_,_,_,_},//13	
{g,o,r,u,n,e,n,_,e,n,e,r,j,i,_,_,_,_,_,_},//14
{e,n,e,r,j,i,_,o,r,a,n,l,a,r,i,_,_,_,_,_},//15
{d,a,l,g,a,_,b,i,c,i,m,l,e,r,i,_,_,_,_,_},//15	

};



 

struct display_menu_handles Main_Menu={

	/*null pointer*/NULL,
	/*no data for main*/{0},
	/*no data for main*/{0},
	/*no data for main*/{0},
	/*no data for main*/{0},
	/*symbols*/			{menu_enter,0,0,menu_down,menu_up},
	/*no data for main*/{0},
	/*null pointer*/toMainDetect,
	/*null pointer*/atMainOperation,
};

struct display_menu_handles Vpn_true_Menu= {
	
	/*dynamic data*/ &(trueRMS.data.Van),
	
	/*title*/      	{v,_,f,a,z,_,n,o,t,r,_,g,e,r,c,e,k}, 
	
	/*fist line*/ 	{A,N,__},
	/*second line*/ {B,N,__},
	/*third line*/ 	{C,N,__},
	
	/*symbols*/			{menu_escape,0,menu_right,menu_down,0},
	/*menu units*/	{m_V,m_,m_,m_},

	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};


struct display_menu_handles Vpn_fund_Menu= {
	
	/*dynamic data*/ &(fundRMS.data.Van),
	
	/*title*/      	{v,_,f,a,z,_,n,o,t,r,_,a,n,a,_,_,_}, 
	
	/*fist line*/ 	{A,N,__},
	/*second line*/ {B,N,__},
	/*third line*/ 	{C,N,__},
	
	/*symbols*/			{menu_escape,menu_left,0,menu_down,0},
	/*menu units*/	{m_V,m_,m_,m_,},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};



struct display_menu_handles Vpp_true_Menu= {
	
	/*dynamic data*/ &(trueRMS.data.Vab),
	
	/*title*/      	{v,_,_,f,a,z,_,f,a,z,_,g,e,r,c,e,k}, 
	
	/*fist line*/ 	{A,B,__},
	/*second line*/ {B,C,__},
	/*third line*/ 	{C,A,__},
	
	/*symbols*/			{menu_escape,0,menu_right,menu_down,menu_up},
	/*menu units*/	{m_V,m_,m_,m_,},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};


struct display_menu_handles Vpp_fund_Menu= {
	
	/*dynamic data*/ &(fundRMS.data.Vab),
	
	/*title*/      	{v,_,_,f,a,z,_,f,a,z,_,a,n,a,_,_,_}, 
	
	/*fist line*/ 	{A,B,__},
	/*second line*/ {B,C,__},
	/*third line*/ 	{C,A,__},
	
	/*symbols*/			{menu_escape,menu_left,0,menu_down,menu_up},
	/*menu units*/	{m_V,m_,m_,m_},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};



struct display_menu_handles Ip_true_Menu= {
	
	/*dynamic data*/ &(trueRMS.data.Ia),
	
	/*title*/      	{a,k,i,m,_,g,e,r,c,e,k,_,r,m,s,_,_}, 
	
	/*fist line*/ 	{I,A,__},
	/*second line*/ {I,B,__},
	/*third line*/ 	{I,C,__},
	
	/*symbols*/			{menu_escape,0,menu_right,menu_down,menu_up},
	/*menu units*/	{m_A,m_,m_,m_,},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};


struct display_menu_handles Ip_fund_Menu= {
	
	/*dynamic data*/ &(fundRMS.data.Ia),
	
	/*title*/      	{a,k,i,m,_,_,a,n,a,_,_,r,m,s,_,_,_} ,
	
	/*fist line*/ 	{I,A,__},
	/*second line*/ {I,B,__},
	/*third line*/ 	{I,C,__},
	
	/*symbols*/			{menu_escape,menu_left,0,menu_down,menu_up},
	/*menu units*/	{m_A,m_,m_,m_},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};


struct display_menu_handles Active_Power_Menu= {
	
	/*dynamic data*/ &(power_iq.Power.Pa),
	
	/*title*/      	{a,k,t,i,f,_,g,u,c,_,_,_,_,_,_,_,_,_} ,
	
	/*fist line*/ 	{P,A,__},
	/*second line*/ {P,B,__},
	/*third line*/ 	{P,C,__},
	
	/*symbols*/			{menu_escape,menu_left,0,menu_down,menu_up},
	/*menu units*/	{m_W,m_,m_,m_},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};


struct display_menu_handles Reactive_Power_Menu= {
	
	/*dynamic data*/ &(power_iq.Power.Qa),
	
	/*title*/      	{r,e,a,k,t,i,f,_,g,u,c,_,_,_,_,_,_,_} ,
	
	/*fist line*/ 	{Q,A,__},
	/*second line*/ {Q,B,__},
	/*third line*/ 	{Q,C,__},
	
	/*symbols*/			{menu_escape,menu_left,0,menu_down,menu_up},
	/*menu units*/	{m_V,m_A,m_R,m_},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};


struct display_menu_handles Apparent_Power_Menu= {
	
	/*dynamic data*/ &(power_iq.Power.Sa),
	
	/*title*/      	{g,o,r,u,n,e,n,_,g,u,c,_,_,_,_,_,_,_} ,
	
	/*fist line*/ 	{S,A,__},
	/*second line*/ {S,B,__},
	/*third line*/ 	{S,C,__},
	
	/*symbols*/			{menu_escape,menu_left,0,menu_down,menu_up},
	/*menu units*/	{m_V,m_A,m_,m_},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};

struct display_menu_handles Total_Power_Menu= {
	
	/*dynamic data*/ &(power_iq.Power.Sa),//cau
	
	/*title*/      	{g,o,r,u,n,e,n,_,g,u,c,_,_,_,_,_,_,_} ,
	
	/*fist line*/ 	{P,T,__}, //cau different units needed
	/*second line*/ {Q,T,__},
	/*third line*/ 	{S,T,__},
	
	/*symbols*/			{menu_escape,menu_left,0,menu_down,menu_up},
	/*menu units*/	{m_A,m_,m_,m_},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};


struct display_menu_handles Power_Factors_true_Menu= {
	
	/*dynamic data*/ &(power_iq.Power.PFa),
	
	/*title*/      	{g,u,c,_,f,a,k,t,o,r,_,g,e,r,c,e,k,_,_,_} ,
	
	/*fist line*/ 	{A,N,__},
	/*second line*/ {B,N,__},
	/*third line*/ 	{C,N,__},
	
	/*symbols*/			{menu_escape,menu_left,0,menu_down,menu_up},
	/*menu units*/	{m_percent,m_,m_,m_},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};

struct display_menu_handles Power_Factors_fund_Menu= {
	
	/*dynamic data*/ &(power_iq.Power.PFa),
	
	/*title*/      	{g,u,c,_,f,a,k,t,o,r,_,a,n,a,_,_,_,_} ,
	
	/*fist line*/ 	{A,N,__},
	/*second line*/ {B,N,__},
	/*third line*/ 	{C,N,__},
	
	/*symbols*/			{menu_escape,menu_left,0,menu_down,menu_up},
	/*menu units*/	{m_percent,m_,m_,m_},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};


struct display_menu_handles Total_Power_Factor_true_Menu= {
	
	/*dynamic data*/ &(power_true.Power.PFtotal),
	
	/*title*/      	{t,o,p,l,a,m,_,g,f,_,g,e,r,c,e,k,_,_,_,_} ,
	
	/*fist line*/ 	{__,__,__},
	/*second line*/ {P,F,T},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_escape,0,menu_right,menu_down,menu_up},
	/*menu units*/	{m_percent,m_,m_,m_},
	/*static data*/  staticDataSingle,
	/*dynamic data*/ dynamicDataSingle
	

};


struct display_menu_handles Total_Power_Factor_fund_Menu= {
	
	/*dynamic data*/ &(power_iq.Power.PFtotal),
	
	/*title*/      	{t,o,p,l,a,m,_,g,f,_,a,n,a,_,_,_,_,_} ,
	
	/*fist line*/ 	{__,__,__},
	/*second line*/ {P,F,T},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_escape,menu_left,0,menu_down,menu_up},
	/*menu units*/	{m_percent,m_,m_,m_},
	/*static data*/  staticDataSingle,
	/*dynamic data*/ dynamicDataSingle
	

};


struct display_menu_handles Power_Ratios_Menu= {
	
	/*dynamic data*/ &(power_iq.Power.PFa),
	
	/*title*/      	{g,u,c,_,o,r,a,n,l,a,r,i,_,q,_,p} , //cau divide can be added
	
	/*fist line*/ 	{Q,P,A},
	/*second line*/ {Q,P,B},
	/*third line*/ 	{Q,P,C},
	
	/*symbols*/			{menu_escape,menu_left,0,menu_down,menu_up},
	/*menu units*/	{m_,m_,m_,m_}, // percent can be added
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};


struct display_menu_handles Total_Power_Ratios_Menu= {
	
	/*dynamic data*/ &(power_iq.Power.PFa),
	
	/*title*/      	{t,o,p,l,a,m,_,g,u,c,_,o,r,a,n,i,_,q,_,p},
	
	/*fist line*/ 	{__,__,__},
	/*second line*/ {P,F,T},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_escape,menu_left,0,menu_down,menu_up},
	/*menu units*/	{m_,m_,m_,m_},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};


struct display_menu_handles Active_Energy_Import_Menu= {
	
	/*dynamic data*/ &(power_iq.Power.PFa),
	
	/*title*/      	{t,o,p,l,a,m,_,g,u,c,_,f,a,k,t,o,r,u} ,
	
	/*fist line*/ 	{__,__,__},
	/*second line*/ {P,F,T},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_escape,menu_left,0,menu_down,menu_up},
	/*menu units*/	{m_A,m_,m_,m_},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};


struct display_menu_handles Active_Energy_Export_Menu= {
	
	/*dynamic data*/ &(power_iq.Power.PFa),
	
	/*title*/      	{t,o,p,l,a,m,_,g,u,c,_,f,a,k,t,o,r,u} ,
	
	/*fist line*/ 	{__,__,__},
	/*second line*/ {P,F,T},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_escape,menu_left,0,menu_down,menu_up},
	/*menu units*/	{m_A,m_,m_,m_},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};

struct display_menu_handles Reactive_Energy_Import_Menu= {
	
	/*dynamic data*/ &(power_iq.Power.PFa),
	
	/*title*/      	{t,o,p,l,a,m,_,g,u,c,_,f,a,k,t,o,r,u} ,
	
	/*fist line*/ 	{__,__,__},
	/*second line*/ {P,F,T},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_escape,menu_left,0,menu_down,menu_up},
	/*menu units*/	{m_A,m_,m_,m_},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};


struct display_menu_handles Reactive_Energy_Export_Menu= {
	
	/*dynamic data*/ &(power_iq.Power.PFa),
	
	/*title*/      	{t,o,p,l,a,m,_,g,u,c,_,f,a,k,t,o,r,u} ,
	
	/*fist line*/ 	{__,__,__},
	/*second line*/ {P,F,T},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_escape,menu_left,0,menu_down,menu_up},
	/*menu units*/	{m_A,m_,m_,m_},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};

struct display_menu_handles Apparent_Energy_Menu= {
	
	/*dynamic data*/ &(power_iq.Power.PFa),
	
	/*title*/      	{t,o,p,l,a,m,_,g,u,c,_,f,a,k,t,o,r,u} ,
	
	/*fist line*/ 	{__,__,__},
	/*second line*/ {P,F,T},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_escape,menu_left,0,menu_down,menu_up},
	/*menu units*/	{m_A,m_,m_,m_},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};

struct display_menu_handles Energy_Ratios_Menu= {
	
	/*dynamic data*/ &(power_iq.Power.PFa),
	
	/*title*/      	{t,o,p,l,a,m,_,g,u,c,_,f,a,k,t,o,r,u} ,
	
	/*fist line*/ 	{__,__,__},
	/*second line*/ {P,F,T},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_escape,menu_left,0,menu_down,menu_up},
	/*menu units*/	{m_A,m_,m_,m_},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};

struct display_menu_handles Scope_Menu= {
	
	/*dynamic data*/ &(power_iq.Power.PFa),
	
	/*title*/      	{t,o,p,l,a,m,_,g,u,c,_,f,a,k,t,o,r,u} ,
	
	/*fist line*/ 	{__,__,__},
	/*second line*/ {P,F,T},
	/*third line*/ 	{__,__,__},
	
	/*symbols*/			{menu_escape,menu_left,0,menu_down,menu_up},
	/*menu units*/	{m_A,m_,m_,m_},
	/*static data*/  graphBaseLining,
	/*dynamic data*/ graphDataTransfer
	

};










// menu transition









const struct MENU_TRANSITION menu_transition[]={
	
	//	current menu----input-----------next menu
	
		{	Vpn_true,								right_pressed,	Vpn_fund},
		{	Vpn_true,								down_pressed,		Vpp_true},
		{	Vpn_true,								enter_pressed,	main_menu},
		
		{	Vpn_fund,								left_pressed,		Vpn_true},
		{	Vpn_fund,								down_pressed,		Vpp_fund},
		{	Vpn_true,								enter_pressed,	main_menu},
		
		{	Vpp_true,								right_pressed,	Vpp_fund},
		{	Vpp_true,								down_pressed,		Ip_true},
		{	Vpp_true,								up_pressed,			Vpn_true},
		{	Vpp_true,								enter_pressed,	main_menu},
		
		{	Vpp_fund,								left_pressed,		Vpp_true},
		{	Vpp_fund,								down_pressed,		Ip_fund},
		{	Vpp_fund,								up_pressed,		  Vpn_fund},
		{	Vpp_fund,								enter_pressed,	main_menu},
		
		{	Ip_true,								right_pressed,	Ip_fund},
		{	Ip_true,								up_pressed,			Vpp_true},
		{	Ip_true,								down_pressed,		Active_Power},
		{	Ip_true,								enter_pressed,	main_menu},
		
		{	Ip_fund,								left_pressed,		Ip_true},
		{	Ip_fund,								up_pressed,			Vpp_fund},
		{	Ip_fund,								down_pressed,		Active_Power},
		{	Ip_fund,								enter_pressed,	main_menu},
		
		{	Active_Power,						up_pressed,			Ip_true},
		{	Active_Power,						down_pressed,		Reactive_Power},
		{	Active_Power,						enter_pressed,	main_menu},
		
		{	Reactive_Power,					up_pressed,			Active_Power},
		{	Reactive_Power,					down_pressed,		Apparent_Power},
		{	Reactive_Power,					enter_pressed,	main_menu},
		
		{	Apparent_Power,					up_pressed,			Reactive_Power},
		{	Apparent_Power,					down_pressed,		Total_Power},
		{	Apparent_Power,					enter_pressed,	main_menu},
		
		{	Total_Power,						up_pressed,			Apparent_Power},
		{	Total_Power,						down_pressed,		Power_Factors_true},
		{	Total_Power,						enter_pressed,	main_menu},
		
		{	Power_Factors_true,			right_pressed,	Power_Factors_fund},
		{	Power_Factors_true,			up_pressed,			Total_Power},
		{	Power_Factors_true,			down_pressed,		Total_Power_Factor_true},
		{	Power_Factors_true,			enter_pressed,	main_menu},
		
		{	Power_Factors_fund,			left_pressed,		Power_Factors_true},
		{	Power_Factors_fund,			up_pressed,			Total_Power},
		{	Power_Factors_fund,			down_pressed,		Total_Power_Factor_fund},
		{	Power_Factors_fund,			enter_pressed,	main_menu},
		
		{	Total_Power_Factor_true,up_pressed,			Power_Factors_true},
		{	Total_Power_Factor_true,down_pressed,		Power_Ratios},
		{	Total_Power_Factor_true,right_pressed,	Total_Power_Factor_fund},
		{	Total_Power_Factor_true,enter_pressed,	main_menu},
		
		{	Total_Power_Factor_fund,up_pressed,			Power_Factors_fund},
		{	Total_Power_Factor_fund,down_pressed,		Power_Ratios},
		{	Total_Power_Factor_fund,right_pressed,	Total_Power_Factor_true},
		{	Total_Power_Factor_fund,enter_pressed,	main_menu},
		

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
	
	MENU.handle.Power_Factors_true=Power_Factors_true_Menu;
	MENU.handle.Power_Factors_fund=Power_Factors_fund_Menu;
	
	MENU.handle.Total_Power_Factor_true=Total_Power_Factor_true_Menu;
	MENU.handle.Total_Power_Factor_fund=Total_Power_Factor_fund_Menu;
	
	MENU.handle.Power_Ratios=Power_Ratios_Menu;
	MENU.handle.Total_Power_Ratios=Total_Power_Ratios_Menu;
	
	MENU.handle.Active_Energy_Import=Active_Energy_Import_Menu;
	MENU.handle.Active_Energy_Export=Active_Energy_Import_Menu;
	
	MENU.handle.Reactive_Energy_Import=Reactive_Energy_Import_Menu;
	MENU.handle.Reactive_Energy_Export=Reactive_Energy_Import_Menu;
	
	MENU.handle.Apparent_Energy=Apparent_Energy_Menu;
	MENU.handle.Energy_Ratios=Energy_Ratios_Menu;
	
	MENU.handle.Scope=Scope_Menu;
	
}






